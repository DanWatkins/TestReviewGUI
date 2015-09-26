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

	function expandAll() {
		for (var idx=0; idx < model.rowCount(); idx++) {
			expand(model.index(idx, 0));
		}
	}

    TableViewColumn {
		role: "name"
		title: "Name"
		width: 200
        movable: false
    }

    TableViewColumn {
        role: "status"
        title: "Status"
		width: 100
        movable: false

        delegate: Item {
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
                        return '#90FF3300'
                    else if (styleData.value === qsTr("passed"))
                        return '#9000CC00'

                    return '#00000000'
                }
            }

            Text {
                text: styleData.value
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }


    TableViewColumn {
        role: "executionTime"
        title: "Execution Time (ms)"
		width: 120
        movable: false
    }

    onDoubleClicked: {
        if (!model.gotoSourceFileForRow(currentIndex))
            console.warn("Unable to goto the current test's source. Make sure Qt Creator's path is set in the application's settings.");
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
				else if (model && model.class !== qsTr(""))
                    return '#D5D5D5'
                else
                    return 'white'
            }
        }
    }
}
