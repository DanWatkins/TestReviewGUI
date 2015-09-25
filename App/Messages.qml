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
    function showMessages(messages) {
        textEdit1.remove(0, textEdit1.length);

        for (var i in messages) {
            textEdit1.append(messages[i]);
        }
    }

    GroupBox {
        title: "Messages"
        anchors.fill: parent
        anchors.margins: 5

        TextArea {
            id: textEdit1
            anchors.fill: parent
            anchors.margins: 2

            readOnly: true
        }
    }
}
