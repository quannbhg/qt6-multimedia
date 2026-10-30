import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

Page {
    FileDialog {
        id: fileDialog
        title: "Select a media file"
        nameFilters: ["Audio files (*.mp3 *.wav *.flac *.ogg *.m4a)", "All files (*)"]
        onAccepted: playerVM.openFile(selectedFile)
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 16

        Button {
            text: "Open file"
            onClicked: fileDialog.open()
        }

        Label {
            Layout.fillWidth: true
            font.pixelSize: 24
            elide: Text.ElideRight
            text: playerVM.fileName === "" ? "No file selected" : playerVM.fileName
        }

        Label {
            Layout.fillWidth: true
            color: "red"
            visible: playerVM.errorMessage !== ""
            text: playerVM.errorMessage
        }

        RowLayout {
            Layout.fillWidth: true

            Label {
                text: playerVM.positionText
            }

            Slider {
                Layout.fillWidth: true
                from: 0
                to: playerVM.duration
                value: playerVM.position
                enabled: playerVM.duration > 0
                onMoved: playerVM.seek(value)
            }

            Label {
                text: playerVM.durationText
            }
        }

        RowLayout {
            spacing: 8

            Button {
                text: "-10s"
                onClicked: playerVM.seekBackward()
            }

            Button {
                text: playerVM.playing ? "Pause" : "Play"
                onClicked: playerVM.togglePlayPause()
            }

            Button {
                text: "Stop"
                onClicked: playerVM.stop()
            }

            Button {
                text: "+10s"
                onClicked: playerVM.seekForward()
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                text: playerVM.muted ? "Unmute" : "Mute"
                onClicked: playerVM.toggleMute()
            }

            Slider {
                from: 0
                to: 100
                value: playerVM.volume
                onMoved: playerVM.volume = value
            }

            ComboBox {
                model: [0.5, 1.0, 1.5, 2.0]
                currentIndex: 1
                displayText: currentValue + "x"
                onActivated: playerVM.playbackRate = currentValue
            }
        }

        Item {
            Layout.fillHeight: true
        }
    }
}