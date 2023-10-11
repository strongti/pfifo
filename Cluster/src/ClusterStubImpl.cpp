#include "ClusterStubImpl.hpp"
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include <chrono>
#include <thread> 
#include <opencv2/dnn.hpp>


std::chrono::high_resolution_clock::time_point ClusterStubImpl::lastTimestamp1 = std::chrono::high_resolution_clock::now();
std::chrono::high_resolution_clock::time_point ClusterStubImpl::lastTimestamp2 = std::chrono::high_resolution_clock::now();
std::chrono::high_resolution_clock::time_point ClusterStubImpl::lastTimestamp3 = std::chrono::high_resolution_clock::now();
std::chrono::high_resolution_clock::time_point ClusterStubImpl::lastTimestamp4 = std::chrono::high_resolution_clock::now();

ClusterStubImpl::ClusterStubImpl() { }
ClusterStubImpl::~ClusterStubImpl() { }

double ClusterStubImpl::totalFPS1 = 0.0;
double ClusterStubImpl::totalFPS2 = 0.0;
double ClusterStubImpl::totalFPS3 = 0.0;
double ClusterStubImpl::totalFPS4 = 0.0;

int ClusterStubImpl::frameCount1 = 0;
int ClusterStubImpl::frameCount2 = 0;
int ClusterStubImpl::frameCount3 = 0;
int ClusterStubImpl::frameCount4 = 0;

int result1;
int result2;


void ClusterStubImpl::sendImage1(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image1, sendImage1Reply_t _reply) {
    std::thread([this, _client, _image1, _reply]() {
        cv::Mat decoded_image1 = cv::imdecode(_image1, cv::IMREAD_COLOR); 
        cv::Mat blob;
        cv::dnn::blobFromImage(decoded_image1, blob, 1/255.0, cv::Size(416, 416), cv::Scalar(0,0,0), true, false);
        net1.setInput(blob);
        std::vector<cv::Mat> outs;
        net1.forward(outs, net1.getUnconnectedOutLayersNames());
        _reply(result1);
        // Postprocessing: draw detected objects and display the frame
        std::vector<int> classIds;
        std::vector<float> confidences;
        std::vector<cv::Rect> boxes;
        bool personDetected = false; // 추가된 코드


        for (size_t i = 0; i < outs.size(); ++i) {
            for (int j = 0; j < outs[i].rows; ++j) {
                cv::Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
                cv::Point classIdPoint;
                double confidence;
                minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
                if (confidence > 0.5) {
                    if(classIdPoint.x == 0) { // person 클래스의 ID가 0
                        personDetected = true; // 사람 감지
                    }
                    int centerX = (int)(outs[i].at<float>(j, 0) * decoded_image1.cols);
                    int centerY = (int)(outs[i].at<float>(j, 1) * decoded_image1.rows);
                    int width = (int)(outs[i].at<float>(j, 2) * decoded_image1.cols);
                    int height = (int)(outs[i].at<float>(j, 3) * decoded_image1.rows);
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
        for (int idx : indices) {
            cv::Rect box = boxes[idx];
            std::string label = cv::format("%.2f", confidences[idx]);
            label = classes1[classIds[idx]];
            int baseLine;
            cv::Size labelSize = getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
            int top = std::max(box.y, labelSize.height);
            rectangle(decoded_image1, box, cv::Scalar(0, 255, 0), 3);
            rectangle(decoded_image1, cv::Point(box.x, top - round(1.5*labelSize.height)), cv::Point(box.x + round(1.5*labelSize.width), top + baseLine), cv::Scalar(255, 255, 255), cv::FILLED);
            putText(decoded_image1, label, cv::Point(box.x, top), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0,0,0),1);
        }
        cv::imshow("Decoded Image1", decoded_image1);
        cv::waitKey(1);
        if(personDetected) {
            result1 = 1;
        } else {
            result1 = 0;
        }
       
    }).detach();
}

void ClusterStubImpl::sendImage2(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image2, sendImage2Reply_t _reply) {
    std::thread([this, _client, _image2, _reply]() {      
        cv::Mat decoded_image2 = cv::imdecode(_image2, cv::IMREAD_COLOR); 
        cv::Mat blob;
        cv::dnn::blobFromImage(decoded_image2, blob, 1/255.0, cv::Size(416, 416), cv::Scalar(0,0,0), true, false);
        net2.setInput(blob);
        std::vector<cv::Mat> outs;
        net2.forward(outs, net2.getUnconnectedOutLayersNames()); 
        _reply(result2);
        // Postprocessing: draw detected objects and display the frame
        std::vector<int> classIds;
        std::vector<float> confidences;
        std::vector<cv::Rect> boxes;
        bool personDetected = false;
        
        for (size_t i = 0; i < outs.size(); ++i) {
            for (int j = 0; j < outs[i].rows; ++j) {
                cv::Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
                cv::Point classIdPoint;
                double confidence;
                minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
                if (confidence > 0.5) {
                    if(classIdPoint.x == 0) { // person 클래스의 ID가 0
                        personDetected = true; // 사람 감지
                    }                    
                    int centerX = (int)(outs[i].at<float>(j, 0) * decoded_image2.cols);
                    int centerY = (int)(outs[i].at<float>(j, 1) * decoded_image2.rows);
                    int width = (int)(outs[i].at<float>(j, 2) * decoded_image2.cols);
                    int height = (int)(outs[i].at<float>(j, 3) * decoded_image2.rows);
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
        for (int idx : indices) {
            cv::Rect box = boxes[idx];
            std::string label = cv::format("%.2f", confidences[idx]);
            label = classes2[classIds[idx]];

            int baseLine;
            cv::Size labelSize = getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
            int top = std::max(box.y, labelSize.height);
            rectangle(decoded_image2, box, cv::Scalar(0, 255, 0), 3);
            rectangle(decoded_image2, cv::Point(box.x, top - round(1.5*labelSize.height)), cv::Point(box.x + round(1.5*labelSize.width), top + baseLine), cv::Scalar(255, 255, 255), cv::FILLED);
            putText(decoded_image2, label, cv::Point(box.x, top), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0,0,0),1);
        }
        cv::imshow("Decoded Image2", decoded_image2);
        cv::waitKey(1);
        if(personDetected) {
            result2 = 1;
        } else {
            result2 = 0;
        }

    }).detach();
}


// void ClusterStubImpl::sendImage2(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image2, sendImage2Reply_t _reply) {
//     std::thread([this, _client, _image2, _reply]() {   
//         std::cout << "=================3" <<  std::endl;      
//         cv::Mat decoded_image2 = cv::imdecode(_image2, cv::IMREAD_COLOR);
//         std::cout << "=================4" <<  std::endl;     
//         // 1. cv::Mat을 NCHW 형식의 4D tensor로 변환
//         // 예를 들어, 이미지 크기가 224x224라고 가정합니다.
//         float data[224 * 224 * 3];
//         for (int c = 0; c < 3; ++c) {
//             for (int i = 0; i < 224; ++i) {
//                 for (int j = 0; j < 224; ++j) {
//                     data[c * 224 * 224 + i * 224 + j] = decoded_image2.at<cv::Vec3b>(i, j)[c];
//                 }
//             }
//         }
//         std::cout << "=================5" <<  std::endl;     
//         // 2. TensorRT 추론 엔진으로 추론 수행
//         // 'engine'는 이미 생성되어 있고 준비된 TensorRT 엔진을 의미합니다.
//         auto context = engine->createExecutionContext();
//         std::cout << "=================6" <<  std::endl;   
//         void* buffers[2]; // 입력 및 출력 버퍼
//         buffers[0] = data;
//         float output[1000]; // 예를 들어 1000 클래스를 분류한다고 가정
//         std::cout << "=================7" <<  std::endl;   
//         buffers[1] = output;
//         context->execute(1, buffers);
//         // 3. 결과 해석 및 출력
//         int classId = std::distance(output, std::max_element(output, output + 1000));
//         cv::putText(decoded_image2, "Class ID: " + std::to_string(classId), cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 0, 255), 2);
//         cv::imshow("Inference Result", decoded_image2);
//         cv::waitKey(1);

//         context->destroy(); // 리소스 정리
//         _reply(0);
//     }).detach();
// }


void ClusterStubImpl::sendImage3(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image3, sendImage3Reply_t _reply) {
    std::thread([this, _client, _image3, _reply]() {     
        auto now3 = std::chrono::high_resolution_clock::now();
        cv::Mat decoded_image3 = cv::imdecode(_image3, cv::IMREAD_COLOR);
    }).detach();
}

void ClusterStubImpl::sendImage4(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image4, sendImage4Reply_t _reply) {
    std::thread([this, _client, _image4, _reply]() {    
        auto now = std::chrono::high_resolution_clock::now();
        cv::Mat decoded_image4 = cv::imdecode(_image4, cv::IMREAD_COLOR);
        // cv::imshow("Decoded Image4", decoded_image4);
        // cv::waitKey(1);   
        std::chrono::duration<double> elapsed = now - lastTimestamp4;
        lastTimestamp4 = now;
        double fps = 1.0 / elapsed.count();
        totalFPS4 += fps;
        frameCount4 += 1;
        double averageFPS = totalFPS4 / (frameCount4);
        std::cout << "period 4: " << 1/fps * 1000 << std::endl;
    }).detach();
}