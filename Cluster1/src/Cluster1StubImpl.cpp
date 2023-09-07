#include "Cluster1StubImpl.hpp"
#include <opencv2/opencv.hpp>
#include <unistd.h>

Cluster1StubImpl::Cluster1StubImpl() { }
Cluster1StubImpl::~Cluster1StubImpl() { }

void Cluster1StubImpl::sendImage1(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image1, sendImage1Reply_t _reply) {
    cv::Mat decoded_image1 = cv::imdecode(_image1, cv::IMREAD_COLOR);
    if (decoded_image1.empty()) {
        std::cerr << "Failed to decode image." << std::endl;
        return;
    };
    cv::imshow("Decoded Image1", decoded_image1);
    cv::waitKey(1);
}
