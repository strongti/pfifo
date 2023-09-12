#include <fstream>
#include "Detect.h"
#include <opencv2/dnn.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>



Detect::Detect(QObject *parent) : QObject(parent)
{
   runtime = CommonAPI::Runtime::get();
    myProxy = runtime->buildProxy<ClusterProxy>("local", "cluster_service");

    while (!myProxy->isAvailable())
        usleep(10);
}


void Detect::startCamera() {
    std::vector<uchar> encoded_image;
    CommonAPI::CallStatus callStatus;
    uint8_t tos_value3 = 0x10;
    setsockopt(36, IPPROTO_IP, IP_TOS, &tos_value3, sizeof(tos_value3));
    int result;
    cv::Mat image = cv::imread("image.jpg");
    if (!cv::imencode(".jpg", image, encoded_image)) {
        std::cerr << "Failed to encode frame." << std::endl;
        return;
    }
    while (true) {
//        if (image.empty()) {
//            std::cerr << "Failed to load image." << std::endl;
//            return;
//        }
        std::cerr << "Send" << std::endl;
        myProxy->sendImage3Async(encoded_image);
        std::cerr << "End" << std::endl;
    }
}

