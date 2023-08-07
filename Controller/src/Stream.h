#ifndef STREAM_H
#define STREAM_H

#include <QObject>
#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/ClusterProxy.hpp>
#include <opencv2/opencv.hpp>
#include <cstdint>


using namespace v1_0::commonapi;

class Stream : public QObject
{
    Q_OBJECT

public:
    explicit Stream(QObject *parent = nullptr);
    std::shared_ptr < CommonAPI::Runtime > runtime;
    std::shared_ptr<ClusterProxy<>> myProxy;
    cv::VideoCapture cap;

public slots:
    void initCamera();
    void sendImage();
};

#endif // STREAM_H
