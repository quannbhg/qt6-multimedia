import QtQuick
import QtQuick.Controls

ApplicationWindow {
    width: 1024
    height: 600
    visible: true
    title: appInfo.appTitle

    PlayerPage {
        anchors.fill: parent
    }
}