#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <qqml.h>
#include <QMetaType>
#include <string>
#include <iostream>
#include <thread>
#include <CommonAPI/CommonAPI.hpp>
#include "ClusterStubImpl.hpp"
#include <fstream>
#include <opencv2/dnn.hpp>
#include <opencv2/opencv.hpp>
#include <cstdint>

//#include "WeatherAPI.h"

using namespace std;
Q_DECLARE_METATYPE(std::string)

cv::dnn::Net net1;
cv::dnn::Net net2;
std::vector<std::string> classes1;
std::vector<std::string> classes2;

int main(int argc, char *argv[])
{

    qRegisterMetaType<std::string>();

    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    std::shared_ptr<ClusterStubImpl> myService =
        std::make_shared<ClusterStubImpl>();
    runtime->registerService("local", "cluster_service", myService);
    std::cout << "Successfully Registered Service!" << std::endl;
    net1 = cv::dnn::readNet("yolov4-tiny.weights", "yolov4-tiny.cfg");
    net1.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    net1.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
    net2 = cv::dnn::readNet("yolov4-tiny.weights", "yolov4-tiny.cfg");
    net2.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    net2.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);    
    std::ifstream ifs1("coco.names");
    std::string line1;
    std::ifstream ifs2("coco.names");
    std::string line2;
    while (std::getline(ifs1, line1)) classes1.push_back(line1);
    while (std::getline(ifs2, line2)) classes2.push_back(line2);
    while(true){

    }
    return 0;
}