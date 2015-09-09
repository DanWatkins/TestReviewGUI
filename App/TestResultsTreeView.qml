//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

import QtTestReviewGUI 1.0

TreeView {
    id: tableView

    TableViewColumn {
        role: "class"
        title: "Class"
        width: 120
        movable: false
    }

    TableViewColumn {
        role: "test"
        title: "Test"
        width: 120
        movable: false
    }

    TableViewColumn {
        role: "status"
        title: "Status"
        width: 120
        movable: false

        delegate: Item {
            Text {
                text: styleData.value
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
            }

            Rectangle {
                anchors {
                    left: parent.left
                    right: parent.right
                    verticalCenter: parent.verticalCenter
                }

                height: parent.height
                radius: width*0.5

                color: {
                    if (styleData.value === qsTr("failed"))
                        return '#60FF3300'
                    else if (styleData.value === qsTr("passed"))
                        return '#6000CC00'

                    return '#00000000'
                }
            }
        }
    }

    onDoubleClicked: {
        model.gotoSourceFileForRow(currentIndex)
    }

    rowDelegate: Item {
        Rectangle {
            anchors {
                left: parent.left
                right: parent.right
                verticalCenter: parent.verticalCenter
            }

            height: parent.height

            color: {
                if (styleData.selected)
                    return 'lightblue'
//                else if (currentIndex)
//                    return '#D5D5D5'
//                else
                    return 'white'
            }
        }
    }
}
