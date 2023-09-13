#include <fstream>
#include "Detect.h"
#include <opencv2/dnn.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <chrono>


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
    uint8_t tos_value4 = 0x00;
    setsockopt(36, IPPROTO_IP, IP_TOS, &tos_value4, sizeof(tos_value4));
    int result;
    cv::Mat image = cv::imread("image.jpg");
    if (!cv::imencode(".jpg", image, encoded_image)) {
        std::cerr << "Failed to encode frame." << std::endl;
        return;
    }

    while (true) {
        auto start = std::chrono::high_resolution_clock::now();

        myProxy->sendImage4Async(encoded_image);
        usleep(15855);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;

        std::printf("Function execution time: %.3f ms\n", elapsed.count());
    }
}

