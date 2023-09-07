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

//void Detect::startCamera() {
//    std::vector<uchar> encoded_image;
//    CommonAPI::CallStatus callStatus;
//    int result;
//    while (true) {
//        cv::Mat image = cv::imread("image.jpg");
//        if (image.empty()) {
//            std::cerr << "Failed to load image." << std::endl;
//            return;
//        }
//        if (!cv::imencode(".jpg", image, encoded_image)) {
//            std::cerr << "Failed to encode frame." << std::endl;
//            return;
//        }
//        myProxy->sendImage3Async(encoded_image);
//        usleep(8200);
//    }
//}
void Detect::startCamera() {
    cv::VideoCapture cap(4);  // Open the default camera
    if (!cap.isOpened()) {
        std::cerr << "Could not open camera." << std::endl;
        return;
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(cv::CAP_PROP_FPS, 30);
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
        myProxy->sendImage3Async(encoded_frame);
    }
}

