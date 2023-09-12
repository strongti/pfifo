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
    uint8_t tos_value4 = 0x10;
    setsockopt(36, IPPROTO_IP, IP_TOS, &tos_value4, sizeof(tos_value4));
    int result;
    cv::Mat image = cv::imread("image.jpg");

    // 이미지 크기를 10배로 늘립니다
    cv::Mat resized_image;
    cv::resize(image, resized_image, cv::Size(image.cols * 100, image.rows * 100));

    if (!cv::imencode(".jpg", resized_image, encoded_image)) {
        std::cerr << "Failed to encode frame." << std::endl;
        return;
    }

    int n;
    n = 0;
    while (true) {
        std::cerr << n << std::endl;
        myProxy->sendImage4Async(encoded_image);
        std::cerr << "End" << std::endl;
        n = n + 1;
    }
}


