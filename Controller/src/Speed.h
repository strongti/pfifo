#ifndef SPEED_H
#define SPEED_H

#include <QObject>
#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/ClusterProxy.hpp>
#include <QThread>

using namespace v1_0::commonapi;

class Speed : public QObject
{
    Q_OBJECT

public:
    explicit Speed(QObject *parent = nullptr);
    ~Speed();
    std::shared_ptr < CommonAPI::Runtime > runtime;
    std::shared_ptr<ClusterProxy<>> myProxy;

public slots:
    void adjustSpeed(int scrollValue);
    void processSpeed();

private:
    QThread speedThread;
    int currentSpeed;
    //std::mutex socket_speed;
};

#endif // SPEED_H
