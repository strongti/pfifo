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
    cv::Mat image = cv::imread("image.jpg");
    if (image.empty()) {
        std::cerr << "Failed to load image." << std::endl;
        return;
    }
    std::vector<uchar> encoded_image;
    CommonAPI::CallStatus callStatus;
    int result;
    while (true) {
//        if (!cv::imencode(".jpg", image, encoded_image)) {
//            std::cerr << "Failed to encode frame." << std::endl;
//            return;
//        }
        myProxy->sendImage4(encoded_image, callStatus, result);c
//        usleep(3000);
    }
}


