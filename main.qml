import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtTestReviewGUI 1.0

ApplicationWindow {
    id: root
    title: qsTr("QtTestReviewGUI")
    width: 640
    height: 480
    visible: true

    function loadTestResultsFile() {
        console.log("loding shit");
        testTableView.model.parseFile(textField_fileToParse.text);
    }

    TestTableView {
        id: testTableView
        anchors.top: button_browseFileToParse.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.topMargin: 5
        anchors.margins: 5

        model: TestResultsTableModel {
        }
    }

    TextField {
        id: textField_fileToParse
        height: 20
        text: "file:///C:/Users/Dan/Desktop/Results.txt"

        anchors.right: button_browseFileToParse.left
        anchors.rightMargin: 5
        anchors.left: text1.right
        anchors.leftMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 5

        onAccepted: {
            root.loadTestResultsFile();
        }
    }

    Text {
        id: text1
        x: 5
        y: 8
        text: qsTr("File to parse:")
        font.pixelSize: 12
    }

    Button {
        id: button_browseFileToParse
        x: 560
        text: qsTr("...")
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.right: parent.right
        anchors.rightMargin: 5

        onClicked: {
            fileDialog.open();
        }
    }

    FileDialog {
        id: fileDialog
        modality: Qt.WindowModal
        title: "File to parse"
        selectMultiple: false
        nameFilters: [ "All files (*)" ]
        selectedNameFilter: "All files (*)"

        onAccepted: {
            textField_fileToParse.text = fileUrl
            root.loadTestResultsFile();
        }
        onRejected: {
            console.log("Rejected")
        }
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
