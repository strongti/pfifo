import QtQuick 2.7
import QtQuick.Controls 2.2
import com.seame.Speed 1.0

ApplicationWindow {
    visible: true
    width: 1280
    height: 960
    title: qsTr("Speed")

    Speed {
        id: speed
    }


    Slider {
        id: speedBar
        width: 631
        height: 219
        rotation: 270
        anchors.verticalCenterOffset: -26
        anchors.horizontalCenterOffset: -236
        from: 0
        to: 100
        value: 0

        onValueChanged: {
            speed.adjustSpeed(speedBar.value);
        }

        anchors.centerIn: parent

        property bool increment: true

        Timer {
            interval: 1
            running: true
            repeat: true
            onTriggered: {
                if (speedBar.increment) {
                    speedBar.value += 1;
                    if (speedBar.value >= 100) {
                        speedBar.increment = false;
                    }
                } else {
                    speedBar.value -= 1;
                    if (speedBar.value <= 0) {
                        speedBar.increment = true;
                    }
                }
            }
        }
    }


    Text {
        id: text1
        x: 350
        y: 91
        text: qsTr("Speed")
        font.bold: true
        font.pixelSize: 36
    }

}
