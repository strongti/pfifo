#include <fstream>
#include "Detect1.h"
#include <opencv2/dnn.hpp>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>



Detect1::Detect1(QObject *parent) : QObject(parent)
{
    runtime = CommonAPI::Runtime::get();
    myProxy = runtime->buildProxy<Cluster1Proxy>("local", "cluster_service1");

    while (!myProxy->isAvailable())
        usleep(10);
}



void Detect1::startCamera() {
    cv::VideoCapture cap(0);  // Open the default camera
    if (!cap.isOpened()) {
        std::cerr << "Could not open camera." << std::endl;
        return;
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(cv::CAP_PROP_FPS, 60);
    CommonAPI::CallStatus callStatus;
    int n;
    n = 0;
    uint8_t tos_value1 = 0x10;
    uint8_t tos_value2 = 0x00;
    while (true) {
        cv::Mat frame;
        cap >> frame;  // Get a new frame from the camera
        cv::imshow("Image", frame);
        cv::waitKey(1);
        if (frame.empty()) {
            std::cerr << "Failed to capture an image." << std::endl;
            return;
        }

        std::vector<uchar> encoded_frame;
        if (!cv::imencode(".jpg", frame, encoded_frame)) {
            std::cerr << "Failed to encode frame." << std::endl;
            return;
        }
        if(n == 1000){
            std::cerr << "Warning! Warning! Warning! Warning! Warning!" << std::endl;
            setsockopt(33, IPPROTO_IP, IP_TOS, &tos_value1, sizeof(tos_value1));
        }
        if(n == 2000){
            std::cerr << "endendendendendendendendendendend" << std::endl;
            setsockopt(33, IPPROTO_IP, IP_TOS, &tos_value2, sizeof(tos_value2));
        }
        myProxy->sendImage1Async(encoded_frame);
        n= n + 1;
    }
}


