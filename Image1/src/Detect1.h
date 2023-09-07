#ifndef DETECT1_H
#define DETECT1_H

#include <QObject>
#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/Cluster1Proxy.hpp>
#include <opencv2/opencv.hpp>
#include <cstdint>


using namespace v1_0::commonapi;

class Detect1 : public QObject
{
    Q_OBJECT

public:
    explicit Detect1(QObject *parent = nullptr);
    std::shared_ptr < CommonAPI::Runtime > runtime;
    std::shared_ptr<Cluster1Proxy<>> myProxy;
    cv::VideoCapture cap;

public slots:
    void startCamera();
};


#endif // DETECT_H



