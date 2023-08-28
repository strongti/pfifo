#include "Speed.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>


Speed::Speed(QObject *parent) : QObject(parent), currentSpeed(0)
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
    currentSpeed = scrollValue;
    QMetaObject::invokeMethod(this, "processSpeed", Qt::QueuedConnection);
}

void Speed::processSpeed()
{
    int result;
    CommonAPI::CallStatus callStatus;

    std::cout << "Speed : " << currentSpeed << std::endl;

    uint8_t tos2 = 0x02;
    
    {
        std::lock_guard<std::mutex> lock(socket_speed);
        setsockopt(33, IPPROTO_IP, IP_TOS, &tos2, sizeof(tos2));
        myProxy->updateSpeed(currentSpeed, callStatus, result);
    }

}
