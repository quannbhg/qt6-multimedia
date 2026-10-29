import QtQuick
import QtQuick.Controls

ApplicationWindow {
    width: 1024
    height: 600
    visible: true
    title: appInfo.appTitle

    Column {
        anchors.centerIn: parent
        spacing: 12

        Label {
            text: "Hello " + appInfo.appTitle
            font.pixelSize: 32
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Label {
            text: "Media mau: " + appInfo.sampleMedia
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}