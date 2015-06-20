import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: applicationWindow1
    title: qsTr("Hello World")
    width: 640
    height: 480
    visible: true

    ProgressBar {
        id: progressBar1
        anchors.right: text1.left
        anchors.rightMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5
    }


    Text {
        id: text1
        x: 617
        y: 10
        text: qsTr("1297 of 1300 passed")
        anchors.right: parent.right
        anchors.rightMargin: 5
        font.pixelSize: 12
    }

    TestTableView {
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.top: progressBar1.bottom
        anchors.topMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5
    }
}
