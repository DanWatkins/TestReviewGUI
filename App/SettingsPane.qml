//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

import TestReviewGUI 1.0
import ValpineBase 1.0

Item {
    id: item1
    width: 600
    height: 350

    RowLayout {
        anchors.fill: parent
        Layout.alignment: Qt.AlignLeft
        spacing: 5

        ColumnLayout {

            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: 100
            Layout.minimumWidth: 200

            spacing: 5

            Rectangle {
                anchors.fill: parent
                color: "gray"
                opacity: 0.3
            }

            ColorPicker {
                Layout.fillWidth: true
                height: 20
                text: "Class Background"

                Component.onCompleted: setColor('white')
            }

            ColorPicker {
                Layout.fillWidth: true
                height: 20
                text: "Test Background:"

                Component.onCompleted: setColor('blue')
            }

            ColorPicker {
                Layout.fillWidth: true
                height: 20
                text: "Passed Status:"
            }

            ColorPicker {
                Layout.fillWidth: true
                height: 20
                text: "Failed Status:"
            }

			SettingsCheckBox {
                appSettingsProvider: appSettings
				settingsKey: SettingsEnum.GraphicsWindowIsFullscreen
				title: "Is Fullscreen"
			}
        }

        ColumnLayout {
            id: column1
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: 100
            Layout.minimumWidth: 300
            spacing: 5

            Rectangle {
                anchors.fill: parent
                color: "gray"
                opacity: 0.3
            }

            PathPicker {
                Layout.fillWidth: true
                text: "Path to QtCreator:"
                value: "fill in"
            }
        }
    }
}
