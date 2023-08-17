#include "Buttons.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

Buttons::Buttons(QObject *parent) : QObject(parent)
{
   runtime = CommonAPI::Runtime::get();
    myProxy = runtime->buildProxy<ClusterProxy>("local", "cluster_service");

    while (!myProxy->isAvailable())
        usleep(10);
}

void Buttons::adjustButtons(QString clickedButton)
{
    int result;
    CommonAPI::CallStatus callStatus;
    std::string clickedButtonStdString = clickedButton.toStdString();

    std::cout << "Click : " << clickedButtonStdString << std::endl;

    uint8_t tos1 = 0x2;

    std::mutex socket_buttons;
    {
        std::lock_guard<std::mutex> lock(socket_buttons);

        setsockopt(33, IPPROTO_IP, IP_TOS, &tos1, sizeof(tos1));

        // Send detected label to other application through Some/IP
        myProxy->clickButtons(clickedButtonStdString, callStatus, result);
    }

    std::cout << "Check error: '" << result << "'\n";
}
