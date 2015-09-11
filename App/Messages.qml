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

GroupBox {
    title: "Messages"

    function showMessages(messages) {
        console.log("Showing messages");
        console.log(messages);

        listView1.model = messages;
    }

    ListView {
        id: listView1
        anchors.fill: parent

        delegate: Rectangle {
            height: 20
            Layout.fillWidth: true
            Text {
                text: modelData
            }
        }
    }
}
