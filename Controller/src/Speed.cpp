#include "Speed.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

Speed::Speed(QObject *parent) : QObject(parent), currentScrollValue(0)
{
    runtime = CommonAPI::Runtime::get();
    myProxy = runtime->buildProxy<ClusterProxy>("local", "cluster_service");

    while (!myProxy->isAvailable())
        usleep(10);

    moveToThread(&speedThread);
    connect(&speedThread, &QThread::started, this, &Speed::processSpeed);
    speedThread.start();
}

Speed::~Speed()
{
    speedThread.quit();
    speedThread.wait();
}

void Speed::adjustSpeed(int scrollValue)
{
    currentScrollValue = scrollValue;
    QMetaObject::invokeMethod(this, "processSpeed", Qt::QueuedConnection);
}

void Speed::processSpeed()
{
    int result;
    CommonAPI::CallStatus callStatus;

    std::cout << "Speed : " << currentScrollValue << std::endl;

    uint8_t tos3 = 0x0;
    std::mutex socket_speed;
    
    {
        std::lock_guard<std::mutex> lock(socket_speed);
        setsockopt(33, IPPROTO_IP, IP_TOS, &tos3, sizeof(tos3));
        myProxy->updateSpeed(currentScrollValue, callStatus, result);
    }

    std::cout << "Check error: '" << result << "'\n";
}