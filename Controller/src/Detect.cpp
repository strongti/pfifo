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
    // Load YOLO network
    cv::dnn::Net net = cv::dnn::readNet("yolov4-tiny.weights", "yolov4-tiny.cfg");
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);

    std::vector<std::string> classes;
    std::ifstream ifs("coco.names");
    std::string line;
    while (std::getline(ifs, line)) classes.push_back(line);

    // Open the camera
    if (!cap.isOpened()) {
        if (!cap.open(0)) {
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

    int frameCount = 0;

    // Start capturing
    while (true) {
        cv::Mat frame;
        cap >> frame;
        frameCount++;

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
        std::vector<int> classIds;
        std::vector<float> confidences;
        std::vector<cv::Rect> boxes;

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

                    classIds.push_back(classIdPoint.x);
                    confidences.push_back((float)confidence);
                    boxes.push_back(cv::Rect(left, top, width, height));
                }
            }
        }

        std::vector<int> indices;
        cv::dnn::NMSBoxes(boxes, confidences, 0.5, 0.4, indices);
        uint8_t tos;
        int result;
        CommonAPI::CallStatus callStatus;
        for (int idx : indices) {

            

            cv::Rect box = boxes[idx];
            std::string label = cv::format("%.2f", confidences[idx]);
            label = classes[classIds[idx]] + ": " + std::to_string(frameCount) + "frame" ;

            // Print detected object to console
            std::cout << label << std::endl;

            // Set the TOS value based on detected class
            tos = 0x0;

            // Check if detected class is "person"
            if (classes[classIds[idx]] == "person") {
                tos = 0x10; // for Minimize Delay
            } else {
                tos = 0x0; // for Normal Service
            }

            std::mutex socket_detect;

            {
                std::lock_guard<std::mutex> lock(socket_detect);

                setsockopt(33, IPPROTO_IP, IP_TOS, &tos, sizeof(tos));

                // Send detected label to other application through Some/IP
                myProxy->sendDetects(label, callStatus, result);
            }

            int baseLine;
            cv::Size labelSize = getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
            int top = std::max(box.y, labelSize.height);
            rectangle(frame, box, cv::Scalar(0, 255, 0), 3);
            rectangle(frame, cv::Point(box.x, top - round(1.5*labelSize.height)), cv::Point(box.x + round(1.5*labelSize.width), top + baseLine), cv::Scalar(255, 255, 255), cv::FILLED);
            putText(frame, classes[classIds[idx]], cv::Point(box.x, top), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0,0,0),1);
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
