#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/Cluster1Proxy.hpp>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qqml.h>
#include "Detect1.h"

using namespace v1_0::commonapi;

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<Detect1>("com.seame.Detect1", 1, 0, "Detect1");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

