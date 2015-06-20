import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

ApplicationWindow {
    id: applicationWindow1
    title: qsTr("QtTestReviewGUI - W:/GoogleDrive/Code/Dev/Tests/Terrain3D_tests_20150620175611.txt")
    width: 640
    height: 480
    visible: true

    TestTableView {
        anchors.fill: parent
        anchors.margins: 5
    }

    statusBar: StatusBar {
        RowLayout {
            anchors.fill: parent

            Label {
                text: "4 passed, 1 failed, 0 skipped, 0 blacklisted"
            }
        }
    }
}
