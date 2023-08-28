#include "Speed.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

Speed::Speed(QObject *parent) : QObject(parent)
{
    runtime = CommonAPI::Runtime::get();
    myProxy = runtime->buildProxy<ClusterProxy>("local", "cluster_service");

    while (!myProxy->isAvailable())
        usleep(10);
    uint8_t tos2 = 0x00;
    setsockopt(33, IPPROTO_IP, IP_TOS, &tos2, sizeof(tos2));
}

void Speed::adjustSpeed(int scrollValue)
{
    int result;
    CommonAPI::CallStatus callStatus;
    std::cout << "Speed : " << scrollValue << std::endl;
    myProxy->updateSpeed(scrollValue, callStatus, result);
}

