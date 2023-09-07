#ifndef DETECT2_H
#define DETECT2_H

#include <QObject>
#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/Cluster2Proxy.hpp>
#include <opencv2/opencv.hpp>
#include <cstdint>


using namespace v1_0::commonapi;

class Detect2 : public QObject
{
    Q_OBJECT

public:
    explicit Detect2(QObject *parent = nullptr);
    std::shared_ptr < CommonAPI::Runtime > runtime;
    std::shared_ptr<Cluster2Proxy<>> myProxy;
    cv::VideoCapture cap;

public slots:
    void startCamera();


};


#endif // DETECT2_H



