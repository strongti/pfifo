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
    cv::VideoCapture cap(0);  // Open the default camera
    if (!cap.isOpened()) {
        std::cerr << "Could not open camera." << std::endl;
        return;
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(cv::CAP_PROP_FPS, 10);

    while (true) {
        cv::Mat frame;
        cap >> frame;  // Get a new frame from the camera

        if (frame.empty()) {
            std::cerr << "Failed to capture an image." << std::endl;
            return;
        }

        std::vector<uchar> encoded_frame;
        if (!cv::imencode(".jpg", frame, encoded_frame)) {
            std::cerr << "Failed to encode frame." << std::endl;
            return;
        }
        CommonAPI::CallStatus callStatus;
        int result;
        std::cerr << "send frame." << std::endl;
        myProxy->sendDetects(encoded_frame, callStatus, result);
        std::cerr << "frame complete." << std::endl;
        // Optional: To break out of the loop, for example by pressing 'q'
        if (cv::waitKey(1) >= 0) break;
    }
}


//void Detect::sendChunks(const std::vector<uchar>& data) {
//    CommonAPI::CallStatus callStatus;
//    int result;
//    size_t chunk_size = 1338;  // Adjust this size as needed
//    std::cerr << "send frame." << std::endl;
//    for (size_t i = 0; i < data.size(); i += chunk_size) {
//        std::vector<uchar> chunk(data.begin() + i, data.begin() + std::min(i + chunk_size, data.size()));
//        myProxy->sendDetects(chunk, callStatus, result);
//    }
//    std::cerr << "frame complete." << std::endl;
//}
