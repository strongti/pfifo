#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/ClusterProxy.hpp>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Speed.h"
#include "Buttons.h"
#include "RPM.h"
#include <qqml.h>
#include "Detect.h"

using namespace v1_0::commonapi;

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<Speed>("com.seame.Speed", 1, 0, "Speed");
    qmlRegisterType<Buttons>("com.seame.Buttons", 1, 0, "Buttons");
    qmlRegisterType<RPM>("com.seame.RPM", 1, 0, "RPM");
    qmlRegisterType<Detect>("com.seame.Detect", 1, 0, "Detect");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

