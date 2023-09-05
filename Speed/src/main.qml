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
        width: 200
        height: 203
        rotation: 270
        anchors.verticalCenterOffset: 101
        anchors.horizontalCenterOffset: -41
        from: 0
        to: 100
        value: 0

        onValueChanged: {
            speed.adjustSpeed(speedBar.value);
        }

        anchors.centerIn: parent

    }
    Text {
        id: text1
        x: 571
        y: 329
        text: qsTr("HI !")
        font.bold: true
        font.pixelSize: 36
    }

}
