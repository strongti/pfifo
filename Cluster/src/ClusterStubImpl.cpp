#include "ClusterStubImpl.hpp"
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include <chrono>
#include <thread> 
#include <opencv2/dnn.hpp>
#include <fstream>
#include <NvInfer.h>

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


// void ClusterStubImpl::sendImage1(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image1, sendImage1Reply_t _reply) {
//     std::thread([this, _client, _image1, _reply]() {
//         cv::Mat decoded_image1 = cv::imdecode(_image1, cv::IMREAD_COLOR); 
//         cv::Mat blob;
//         cv::dnn::blobFromImage(decoded_image1, blob, 1/255.0, cv::Size(416, 416), cv::Scalar(0,0,0), true, false);
//         net1.setInput(blob);
//         std::vector<cv::Mat> outs;
//         net1.forward(outs, net1.getUnconnectedOutLayersNames());
//         _reply(result1);
//         // Postprocessing: draw detected objects and display the frame
//         std::vector<int> classIds;
//         std::vector<float> confidences;
//         std::vector<cv::Rect> boxes;

//         for (size_t i = 0; i < outs.size(); ++i) {
//             for (int j = 0; j < outs[i].rows; ++j) {
//                 cv::Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
//                 cv::Point classIdPoint;
//                 double confidence;
//                 minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
//                 if (confidence > 0.5) {
//                     int centerX = (int)(outs[i].at<float>(j, 0) * decoded_image1.cols);
//                     int centerY = (int)(outs[i].at<float>(j, 1) * decoded_image1.rows);
//                     int width = (int)(outs[i].at<float>(j, 2) * decoded_image1.cols);
//                     int height = (int)(outs[i].at<float>(j, 3) * decoded_image1.rows);
//                     int left = centerX - width / 2;
//                     int top = centerY - height / 2;

//                     classIds.push_back(classIdPoint.x);
//                     confidences.push_back((float)confidence);
//                     boxes.push_back(cv::Rect(left, top, width, height));
//                 }
//             }
//         }
//         std::vector<int> indices;
//         cv::dnn::NMSBoxes(boxes, confidences, 0.5, 0.4, indices);
//         for (int idx : indices) {
//             cv::Rect box = boxes[idx];
//             std::string label = cv::format("%.2f", confidences[idx]);
//             label = classes1[classIds[idx]];
//             int baseLine;
//             cv::Size labelSize = getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
//             int top = std::max(box.y, labelSize.height);
//             rectangle(decoded_image1, box, cv::Scalar(0, 255, 0), 3);
//             rectangle(decoded_image1, cv::Point(box.x, top - round(1.5*labelSize.height)), cv::Point(box.x + round(1.5*labelSize.width), top + baseLine), cv::Scalar(255, 255, 255), cv::FILLED);
//             putText(decoded_image1, label, cv::Point(box.x, top), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0,0,0),1);
//         }
//         cv::imshow("Decoded Image1", decoded_image1);
//         char key = cv::waitKey(1) & 0xFF;
//         if (key == '1') {
//             result1 = 1 -result1;
//         }
//     }).detach();
// }

void ClusterStubImpl::sendImage1(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image1, sendImage1Reply_t _reply) {
    std::thread([this, _client, _image1, _reply]() {
        
        cv::Mat decoded_image1 = cv::imdecode(_image1, cv::IMREAD_COLOR);
        
        std::vector<cv::Mat> img_vector1 = {decoded_image1};  // img_vector를 생성

        // Preprocess
        cuda_batch_preprocess(img_vector1, device_buffers1[0], kInputW, kInputH, stream1);  // img_vector를 전달

        // Run inference
        // auto start = std::chrono::system_clock::now();
        infer(*context1, stream1, (void**)device_buffers1, output_buffer_host1, 1);  // Assuming batch size of 1
        // auto end = std::chrono::system_clock::now();
        // std::cout << "inference time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

        // NMS
        std::vector<std::vector<Detection>> res_batch;
        batch_nms(res_batch, output_buffer_host1, 1, kOutputSize, kConfThresh, kNmsThresh);  // Assuming batch size of 1

        // Draw bounding boxes
        draw_bbox(img_vector1, res_batch);  // img_vector를 전달

        cv::imshow("Decoded Image1 with TensorRT", decoded_image1);
        char key = cv::waitKey(1) & 0xFF;
        if (key == '1') {
            result1 = 1 - result1;
        }
        _reply(result1);

    }).detach();
}

void ClusterStubImpl::sendImage2(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image2, sendImage2Reply_t _reply) {
    std::thread([this, _client, _image2, _reply]() {
        
        cv::Mat decoded_image2 = cv::imdecode(_image2, cv::IMREAD_COLOR);
        
        std::vector<cv::Mat> img_vector2 = {decoded_image2};  // img_vector를 생성

        // Preprocess
        cuda_batch_preprocess(img_vector2, device_buffers2[0], kInputW, kInputH, stream2);  // img_vector를 전달

        // Run inference
        // auto start = std::chrono::system_clock::now();
        infer(*context2, stream2, (void**)device_buffers2, output_buffer_host2, 1);  // Assuming batch size of 1
        // auto end = std::chrono::system_clock::now();
        // std::cout << "inference time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

        // NMS
        std::vector<std::vector<Detection>> res_batch;
        batch_nms(res_batch, output_buffer_host2, 1, kOutputSize, kConfThresh, kNmsThresh);  // Assuming batch size of 1

        // Draw bounding boxes
        draw_bbox(img_vector2, res_batch);  // img_vector를 전달

        cv::imshow("Decoded Image2 with TensorRT", decoded_image2);
        char key = cv::waitKey(1) & 0xFF;
        if (key == '2') {
            result2 = 1 - result2;
        }
        _reply(result2);

    }).detach();
}



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