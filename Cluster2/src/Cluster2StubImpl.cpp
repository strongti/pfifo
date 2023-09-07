#include "Cluster2StubImpl.hpp"
#include <opencv2/opencv.hpp>
#include <unistd.h>

Cluster2StubImpl::Cluster2StubImpl() { }
Cluster2StubImpl::~Cluster2StubImpl() { }

void Cluster2StubImpl::sendImage2(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image2, sendImage2Reply_t _reply) {
    cv::Mat decoded_image2 = cv::imdecode(_image2, cv::IMREAD_COLOR);
    if (decoded_image2.empty()) {
        std::cerr << "Failed to decode image." << std::endl;
        return;
    };
    cv::imshow("Decoded Image2", decoded_image2);
    cv::waitKey(1);
}
