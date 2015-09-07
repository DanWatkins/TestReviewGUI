//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtTestReviewGUI 1.0

Item {
    id: item1
    default property alias text: label1.text

    function setColor(color) {
        button1.setColor(color);
        colorDialog1.currentColor = color;
    }

    width: 150
    height: 20

    Label {
        id: label1
        x: 31
        y: 9
        text: "Sample Text:"
        anchors.verticalCenter: button1.verticalCenter
        anchors.right: button1.left
        anchors.rightMargin: 6
    }

    Button {
        id: button1
        width: 50
        text: qsTr("")

        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.margins: 0

        function setColor(newColor) {
            rect.color = newColor;
        }

        Rectangle {
            id: rect
            color: "#af1010"
            anchors.fill: parent
        }

        onClicked: {
            colorDialog1.currentColor = rect.color;
            colorDialog1.open();
        }
    }

    ColorDialog {
        id: colorDialog1

        onAccepted: {
            button1.setColor(color);
        }
    }
}
