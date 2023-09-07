#include "Cluster3StubImpl.hpp"
#include <opencv2/opencv.hpp>
#include <unistd.h>

Cluster3StubImpl::Cluster3StubImpl() { }
Cluster3StubImpl::~Cluster3StubImpl() { }

void Cluster3StubImpl::sendImage3(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image3, sendImage3Reply_t _reply) {
    cv::Mat decoded_image3 = cv::imdecode(_image3, cv::IMREAD_COLOR);
    if (decoded_image3.empty()) {
        std::cerr << "Failed to decode image." << std::endl;
        return;
    };
    cv::imshow("Decoded Image3", decoded_image3);
    cv::waitKey(1);
}
