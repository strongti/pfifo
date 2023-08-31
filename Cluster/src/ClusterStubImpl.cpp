#include "ClusterStubImpl.hpp"
#include <opencv2/opencv.hpp>

ClusterStubImpl::ClusterStubImpl() { }
ClusterStubImpl::~ClusterStubImpl() { }

void ClusterStubImpl::updateSpeed(const std::shared_ptr<CommonAPI::ClientId> _client, int _speed, updateSpeedReply_t _reply) {
    std::cout << "Speed : " << _speed << " \n";
    emit signalSpeed(_speed); // Emit the signal

    if (0 <= _speed && _speed <= 260) {
        _reply(0);
    } else {
        _reply(-1);
    }
}

void ClusterStubImpl::updateRPM(const std::shared_ptr<CommonAPI::ClientId> _client, int _rpm, updateRPMReply_t _reply) {
     std::cout << "RPM : " << _rpm << " \n";
     emit signalRPM(_rpm); // Emit the signal

     if (0 <= _rpm && _rpm <= 8000) {
         _reply(0);
     } else {
         _reply(-1);
     }
}

void ClusterStubImpl::clickButtons(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _command, clickButtonsReply_t _reply) {
     std::cout << "command : " << _command << " \n";
     emit signalButtons(_command); // Emit the signal

    _reply(0);
}

void ClusterStubImpl::sendDetects(const std::shared_ptr<CommonAPI::ClientId> _client, std::vector< uint8_t > _image, sendDetectsReply_t _reply) {
    cv::Mat decoded_image = cv::imdecode(_image, cv::IMREAD_COLOR);
     if (decoded_image.empty()) {
        std::cerr << "Failed to decode image." << std::endl;
        _reply(-1);
    }
    std::cout << "Got message@@'" << "'\n";
    cv::namedWindow("Decoded Image");
    cv::imshow("Decoded Image", decoded_image);
    cv::waitKey(0);

    _reply(0);
}
