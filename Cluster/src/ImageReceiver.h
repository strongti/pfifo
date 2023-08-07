#ifndef IMAGERECEIVER_H
#define IMAGERECEIVER_H

#include <QObject>
#include <iostream>

class ImageReceiver : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int speedValue READ speedValue NOTIFY speedValueChanged)

public:
    explicit ImageReceiver(QObject *parent = nullptr);
    int speedValue() const { return qt_speedValue; }

signals:
    void speedValueChanged();

public slots:
    void receiveImage(int signal);

private:
    int qt_speedValue = 0;
};

#endif // IMAGERECEIVER_H
