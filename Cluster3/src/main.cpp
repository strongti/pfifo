#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <qqml.h>
#include <QMetaType>
#include <string>
#include <iostream>
#include <thread>
#include <CommonAPI/CommonAPI.hpp>
#include "Cluster3StubImpl.hpp"

//#include "WeatherAPI.h"

using namespace std;
Q_DECLARE_METATYPE(std::string)

int main(int argc, char *argv[])
{

    qRegisterMetaType<std::string>();

    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    std::shared_ptr<Cluster3StubImpl> myService3 =
        std::make_shared<Cluster3StubImpl>();
    runtime->registerService("local", "cluster_service3", myService3);
    std::cout << "Successfully Registered Service!" << std::endl;
    while(true){

    }
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//    QGuiApplication app(argc, argv);
//    QQmlApplicationEngine engine;

//    SpeedReceiver speedStorage;
//    ButtonsReceiver buttonStorage;
//    RPMReceiver rpmStorage;
//    WeatherAPI weatherAPIStorage;
//    DetectsReceiver detectStorage;

//    engine.rootContext()->setContextProperty("speedReceiver", &speedStorage);
//    engine.rootContext()->setContextProperty("buttonsReceiver", &buttonStorage);
//    engine.rootContext()->setContextProperty("rpmReceiver", &rpmStorage);
//    engine.rootContext()->setContextProperty("weatherAPI", &weatherAPIStorage);
//    engine.rootContext()->setContextProperty("weatherAPI", &detectStorage);

//    QObject::connect(&(*myService), &ClusterStubImpl::signalSpeed, &speedStorage, &SpeedReceiver::receiveSpeed); // Connect the instances
//    QObject::connect(&(*myService), &ClusterStubImpl::signalButtons, &buttonStorage, &ButtonsReceiver::receiveButtons); // Connect the instances
//    QObject::connect(&(*myService), &ClusterStubImpl::signalRPM, &rpmStorage, &RPMReceiver::receiveRPM); // Connect the instances

//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;
//    return app.exec();
    return 0;
}
