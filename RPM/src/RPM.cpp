#include "RPM.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <opencv2/opencv.hpp>

RPM::RPM(QObject *parent) : QObject(parent)
{
    runtime = CommonAPI::Runtime::get();
    myProxy = runtime->buildProxy<ClusterProxy>("local", "cluster_service");

    while (!myProxy->isAvailable())
        usleep(10);
    uint8_t tos3 = 0x10;
    setsockopt(33, IPPROTO_IP, IP_TOS, &tos3, sizeof(tos3));
}

void RPM::adjustRPM(int scrollValue)
{
    int result;
    CommonAPI::CallStatus callStatus;
    std::cout << "RPM : " << scrollValue << std::endl;
    myProxy->updateRPM(scrollValue, callStatus, result);
    std::cout << "Rpmresult : " << result << std::endl;//
}
