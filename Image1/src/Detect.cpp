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
    cv::VideoCapture cap(0);  // Open the default camera
    if (!cap.isOpened()) {
        std::cerr << "Could not open camera." << std::endl;
        return;
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(cv::CAP_PROP_FPS, 60);
    CommonAPI::CallStatus callStatus;
    int result;
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
        myProxy->sendImage1(encoded_frame, callStatus, result);
    }
}


