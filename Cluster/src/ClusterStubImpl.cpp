#include "ClusterStubImpl.hpp"
#include <opencv2/opencv.hpp>
#include <unistd.h>
#include <chrono>
#include <thread> 

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

void ClusterStubImpl::sendImage1(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image1, sendImage1Reply_t _reply) {
    std::thread([this, _client, _image1, _reply]() {    
        auto now1 = std::chrono::high_resolution_clock::now();
        cv::Mat decoded_image1 = cv::imdecode(_image1, cv::IMREAD_COLOR);
        // cv::imshow("Decoded Image1", decoded_image1);
        // cv::waitKey(1);
        std::chrono::duration<double> elapsed1 = now1 - lastTimestamp1;
        lastTimestamp1 = now1;
        double fps = 1.0 / elapsed1.count();
        totalFPS1 += fps;
        frameCount1 += 1;
        double averageFPS = totalFPS1 / (frameCount1);
        std::cout << "period 1: " << 1/fps * 1000 << std::endl;
    }).detach();
}

void ClusterStubImpl::sendImage2(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image2, sendImage2Reply_t _reply) {
    std::thread([this, _client, _image2, _reply]() {      
        auto now2 = std::chrono::high_resolution_clock::now();
        // cv::Mat decoded_image2 = cv::imdecode(_image2, cv::IMREAD_COLOR);
        // cv::imshow("Decoded Image2", decoded_image2);
        // cv::waitKey(1);
        std::chrono::duration<double> elapsed2 = now2 - lastTimestamp2;
        lastTimestamp2 = now2;
        double fps = 1.0 / elapsed2.count();
        totalFPS2 += fps;
        frameCount2 += 1;
        double averageFPS = totalFPS2 / (frameCount2);
        std::cout << "period 2: " << 1/fps * 1000 << std::endl;
    }).detach();
}

void ClusterStubImpl::sendImage3(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image3, sendImage3Reply_t _reply) {
    std::thread([this, _client, _image3, _reply]() {     
        auto now3 = std::chrono::high_resolution_clock::now();
        // cv::Mat decoded_image3 = cv::imdecode(_image3, cv::IMREAD_COLOR);
        // cv::imshow("Decoded Image3", decoded_image3);
        // cv::waitKey(1);
        std::chrono::duration<double> elapsed3 = now3 - lastTimestamp3;
        lastTimestamp3 = now3;
        double fps = 1.0 / elapsed3.count();
        totalFPS3 += fps;
        frameCount3 += 1;
        double averageFPS = totalFPS3 / (frameCount3);
        std::cout << "period 3: " << 1/fps * 1000 << std::endl;
    }).detach();
}

void ClusterStubImpl::sendImage4(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image4, sendImage4Reply_t _reply) {
    std::thread([this, _client, _image4, _reply]() {    
        auto now = std::chrono::high_resolution_clock::now();
        // cv::Mat decoded_image4 = cv::imdecode(_image4, cv::IMREAD_COLOR);
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