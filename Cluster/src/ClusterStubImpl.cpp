#include "ClusterStubImpl.hpp"
#include <opencv2/opencv.hpp>
#include <unistd.h>

ClusterStubImpl::ClusterStubImpl() { }
ClusterStubImpl::~ClusterStubImpl() { }

void ClusterStubImpl::updateSpeed(const std::shared_ptr<CommonAPI::ClientId> _client, int _speed, updateSpeedReply_t _reply) {
    std::cerr << "Connect!" << std::endl;
    _reply(0);
}

void ClusterStubImpl::sendImage1(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image1, sendImage1Reply_t _reply) {
    cv::Mat decoded_image1 = cv::imdecode(_image1, cv::IMREAD_COLOR);
    if (decoded_image1.empty()) {
        std::cerr << "Failed to decode image." << std::endl;
        return;
    };
    cv::imshow("Decoded Image1", decoded_image1);
    cv::waitKey(1);
    _reply(0);
}

void ClusterStubImpl::sendImage2(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image2, sendImage2Reply_t _reply) {
    cv::Mat decoded_image2 = cv::imdecode(_image2, cv::IMREAD_COLOR);
    if (decoded_image2.empty()) {
        std::cerr << "Failed to decode image." << std::endl;
        return;
    };
    cv::imshow("Decoded Image2", decoded_image2);
    cv::waitKey(1);
    _reply(0);
}
