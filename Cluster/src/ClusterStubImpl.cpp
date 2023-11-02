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

ClusterStubImpl::ClusterStubImpl() {
    last_fps_time = std::chrono::high_resolution_clock::now();
 }
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
int fps;
int number;

void ClusterStubImpl::sendImage1(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image1, sendImage1Reply_t _reply) {
    std::thread([this, _client, _image1, _reply]() {
        
        cv::Mat decoded_image1 = cv::imdecode(_image1, cv::IMREAD_COLOR);

        std::vector<cv::Mat> img_vector1 = {decoded_image1};  // img_vector를 생성

        // Preprocess
        cuda_batch_preprocess(img_vector1, device_buffers1[0], kInputW, kInputH, stream1);  // img_vector를 전달
        _reply(result1);
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
            result1 = 1;
            std::cout << "Order Emergency2" << std::endl;
        }

        frame_counter++;  // 프레임 카운터 증가
        auto current_time = std::chrono::high_resolution_clock::now();
        auto elapsed_time = std::chrono::duration<double>(current_time - last_fps_time).count();

        // 1초 이상 경과했을 때 FPS 계산 및 출력
        if (elapsed_time >= 1.0) {
            std::cout << "FPS: " << frame_counter << std::endl;  // 프레임 카운터 값이 바로 FPS입니다
            if (number > 2 && frame_counter < 20) {
                result1 = 1;
                std::cout << "Order Emergency1" << std::endl;
            }
            last_fps_time = current_time;
            frame_counter = 0;
        }
        number = number + 1;
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