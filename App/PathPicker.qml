import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

Item {
    id: hey
    property alias text: label1.text
    property alias value: textField_pathToQtCreator.text

    width: 25

    Label {
        id: label1
        width: 100
        horizontalAlignment: Text.AlignRight
        anchors.verticalCenter: textField_pathToQtCreator.verticalCenter
    }

    TextField {
        id: textField_pathToQtCreator
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: label1.right
        anchors.leftMargin: 5
        anchors.right: button1.left
        anchors.rightMargin: 5
        placeholderText: qsTr("Text Field")
    }

    Button {
        id: button1
        width: 50
        text: qsTr("...")
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.verticalCenter: textField_pathToQtCreator.verticalCenter

        onClicked: fileDialog.open();
    }

    FileDialog {
        id: fileDialog
        modality: Qt.WindowModal
        title: "Path to QT Creator executable"
        selectMultiple: false
        nameFilters: [ "All files (*.*)" ]

        onAccepted: {
            textField_pathToQtCreator.text = fileUrl;
        }
    }
}
