#include <fstream>
#include "Detect.h"
#include <opencv2/dnn.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>




Detect::Detect(QObject *parent) : QObject(parent)
{
   runtime = CommonAPI::Runtime::get();
    myProxy = runtime->buildProxy<ClusterProxy>("local", "cluster_service");

    while (!myProxy->isAvailable())
        usleep(10);
}

void Detect::startCamera() {
    int result;
    CommonAPI::CallStatus callStatus;
    cv::Mat image = cv::imread("image.jpg");
    if (image.empty()) {
        std::cerr << "Failed to load image." << std::endl;
        return;
    }
    std::vector<uchar> encoded_image;
    if (!cv::imencode(".jpg", image, encoded_image)) {
        std::cerr << "Failed to encode image." << std::endl;
        return;
    }
    std::cout << "Send image" << std::endl;
    myProxy->sendDetects(encoded_image, callStatus, result);
    std::cout << "Arrive image? : " << result << std::endl;
}
