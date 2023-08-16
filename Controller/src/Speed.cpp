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
}

void Speed::adjustSpeed(int scrollValue)
{
    int result;
    CommonAPI::CallStatus callStatus;

    std::cout << "Speed : " << scrollValue << std::endl;

    uint8_t tos3 = 0x0;

    std::mutex socket_speed;
    {
        std::lock_guard<std::mutex> lock(socket_speed);

        int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
        setsockopt(socket_fd, IPPROTO_IP, IP_TOS, &tos3, sizeof(tos3));

        // Send detected label to other application through Some/IP
        myProxy->updateSpeed(scrollValue, callStatus, result);
    }

    std::cout << "Check error: '" << result << "'\n";
}
