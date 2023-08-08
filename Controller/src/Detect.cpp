#include <fstream>
#include "Detect.h"
#include <opencv2/dnn.hpp>

Detect::Detect(QObject *parent) : QObject(parent)
{
   runtime = CommonAPI::Runtime::get();
    myProxy = runtime->buildProxy<ClusterProxy>("local", "cluster_service");

    while (!myProxy->isAvailable())
        usleep(10);
}

void Detect::startCamera() {
    // Load YOLO network
    cv::dnn::Net net = cv::dnn::readNet("yolov3-tiny.weights", "yolov3-tiny.cfg");
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);

    std::vector<std::string> classes;
    std::ifstream ifs("coco.names");
    std::string line;
    while (std::getline(ifs, line)) classes.push_back(line);

    // Open the camera
    if (!cap.isOpened()) {
        if (!cap.open(1)) {
            std::cerr << "Could not open camera." << std::endl;
            return;
        }
    }
    // Set properties
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(cv::CAP_PROP_FPS, 30);

    // Create window
    cv::namedWindow("Webcam", cv::WINDOW_AUTOSIZE);
    cv::resizeWindow("Webcam", 640, 480);

    // Start capturing
    while (true) {
        cv::Mat frame;
        cap >> frame;

        if (frame.empty()) {
            std::cerr << "Could not capture frame." << std::endl;
            break;
        }

        cv::Mat blob;
        cv::dnn::blobFromImage(frame, blob, 1/255.0, cv::Size(416, 416), cv::Scalar(0,0,0), true, false);
        net.setInput(blob);

        std::vector<cv::Mat> outs;
        net.forward(outs, net.getUnconnectedOutLayersNames());

        // Postprocessing: draw detected objects and display the frame
        for (size_t i = 0; i < outs.size(); ++i) {
            for (int j = 0; j < outs[i].rows; ++j) {
                cv::Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
                cv::Point classIdPoint;
                double confidence;
                minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
                if (confidence > 0.5) {
                    int centerX = (int)(outs[i].at<float>(j, 0) * frame.cols);
                    int centerY = (int)(outs[i].at<float>(j, 1) * frame.rows);
                    int width = (int)(outs[i].at<float>(j, 2) * frame.cols);
                    int height = (int)(outs[i].at<float>(j, 3) * frame.rows);
                    int left = centerX - width / 2;
                    int top = centerY - height / 2;

                    std::string label = cv::format("%.2f", confidence);
                    label = classes[classIdPoint.x] + ":" + label;

                    int baseLine;
                    cv::Size labelSize = getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
                    top = std::max(top, labelSize.height);
                    rectangle(frame, cv::Point(left, top), cv::Point(left + width, top + height), cv::Scalar(0, 255, 0), 3);
                    rectangle(frame, cv::Point(left, top - round(1.5*labelSize.height)), cv::Point(left + round(1.5*labelSize.width), top + baseLine), cv::Scalar(255, 255, 255), cv::FILLED);
                    putText(frame, label, cv::Point(left, top), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0,0,0),1);
                }
            }
        }

        cv::imshow("Webcam", frame);
        char key = (char)cv::waitKey(30);
        if (key == 27) {
            break;
        }
    }
}

void Detect::stopCamera() {
    // Stop capturing and close the camera
    cap.release();
    // Destroy the window
    cv::destroyWindow("Webcam");
}
