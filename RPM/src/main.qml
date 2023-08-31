import QtQuick 2.7
import QtQuick.Controls 2.2
import com.seame.RPM 1.0

ApplicationWindow {
    visible: true
    width: 1280
    height: 960
    title: qsTr("rpm")


    RPM {
        id: rpm
    }

    Slider {
        id: rpmBar
        width: 631
        height: 219
        rotation: 270
        anchors.verticalCenterOffset: -26
        anchors.horizontalCenterOffset: 231
        from: 0
        to: 100
        value: 0

        onValueChanged: {
            rpm.adjustRPM(rpmBar.value);
        }

        anchors.centerIn: parent

        property bool increment: true

        Timer {
            interval: 1
            running: true
            repeat: true
            onTriggered: {
                if (rpmBar.increment) {
                    rpmBar.value += 1;
                    if (rpmBar.value >= 100) {
                        rpmBar.increment = false;
                    }
                } else {
                    rpmBar.value -= 1;
                    if (rpmBar.value <= 0) {
                        rpmBar.increment = true;
                    }
                }
            }
        }
    }

    Text {
        id: text2
        x: 831
        y: 91
        text: qsTr("RPM")
        font.bold: true
        font.pixelSize: 36
    }
}
