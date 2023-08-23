#include "RPM.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include "GlobalMutex.h"

RPM::RPM(QObject *parent) : QObject(parent), currentRPM(0)
{
    runtime = CommonAPI::Runtime::get();
    myProxy = runtime->buildProxy<ClusterProxy>("local", "cluster_service");

    while (!myProxy->isAvailable())
        usleep(10);

    moveToThread(&RPMThread);
    connect(&RPMThread, &QThread::started, this, &RPM::processRPM);
    RPMThread.start();
}

RPM::~RPM()
{
    RPMThread.quit();
    RPMThread.wait();
}

void RPM::adjustRPM(int scrollValue)
{
    currentRPM = scrollValue;
    QMetaObject::invokeMethod(this, "processRPM", Qt::QueuedConnection);
}

void RPM::processRPM()
{
    int result;
    CommonAPI::CallStatus callStatus;

    std::cout << "RPM : " << currentRPM << std::endl;
    uint8_t tos3 = 0x10;

    {
        std::lock_guard<std::mutex> lock(global_socket_mutex);
        setsockopt(33, IPPROTO_IP, IP_TOS, &tos3, sizeof(tos3));
        myProxy->updateRPM(currentRPM, callStatus, result);
    }
}
