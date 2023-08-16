#include "RPM.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

RPM::RPM(QObject *parent) : QObject(parent)
{
   runtime = CommonAPI::Runtime::get();
   myProxy = runtime->buildProxy<ClusterProxy>("local", "cluster_service");

    while (!myProxy->isAvailable())
        usleep(10);
}

void RPM::adjustRPM(int scrollValue)
{
    int result;
    CommonAPI::CallStatus callStatus;

    std::cout << "RPM : " << scrollValue << std::endl;
    
    uint8_t tos2 = 0x0;

    std::mutex socket_rpm;
    {
        std::lock_guard<std::mutex> lock(socket_rpm);

        int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
        setsockopt(socket_fd, IPPROTO_IP, IP_TOS, &tos2, sizeof(tos2));

        // Send detected label to other application through Some/IP
        myProxy->updateRPM(scrollValue, callStatus, result);
    }

    std::cout << "Check error: '" << result << "'\n";
}
