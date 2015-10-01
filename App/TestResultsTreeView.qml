//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

import TestReviewGUI 1.0

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
		role: "executionTime"
		title: "Execution Time (ms)"
		width: 120
		movable: false

		delegate: Item {
			Text {
				anchors.verticalCenter: parent.verticalCenter
				color: styleData.textColor
				elide: styleData.elideMode
				text: styleData.value
			}
		}
	}

	itemDelegate: Item {
		anchors.verticalCenter: parent.verticalCenter
		height: 25
		Row {
			anchors.fill: parent

			Item {
				width: parent.height
				height: width

				Image {
					id: idk
					mipmap: true
					source: {
						var status = tableView.model.internalProperty(styleData.index,
																	  "status");

						//TODO update later
						if (status === "passed")
							return "passed.png";
						else if (status === "warned")
							return "warning.png";
						else if (status === "errored")
							return "error.png"

						return "info.png";
					}

					anchors.fill: parent
					anchors.margins: 5
				}
			}

			Text {
				text: styleData.value
				anchors.verticalCenter: parent.verticalCenter
			}
		}
	}

	rowDelegate: Item {
		height: 25

		Rectangle {
			anchors.fill: parent

			color: {
				if (styleData.selected)
					return 'lightblue'
				else
					return 'white'
			}
		}
	}
}
