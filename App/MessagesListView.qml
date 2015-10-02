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

ListView {
	id: rootListView
	spacing: 5
	clip: true
	highlightMoveDuration: 0
	highlightResizeDuration: 0

	function showMessagesForIndex(index) {
		model.setTestIndex(index);
	}

	model: MessagesListViewModel {}

	delegate: Component {
		Item {
			id: myDelegate

			width: parent.width
			height: headerRowLayout.implicitHeight + detailsListView.height + 10

			Rectangle {
				anchors.fill: parent
				color: "gray"
				opacity: 0.1
				radius: 4
			}

			ColumnLayout {
				anchors.fill: parent
				anchors.margins: 5
				spacing: 10


				RowLayout {
					id: headerRowLayout
					spacing: 5
					anchors.left: parent.left
					anchors.right: parent.right
					height: 25

					Image {
						Layout.maximumHeight: 20
						Layout.maximumWidth: 20
						mipmap: true
						source: "error.png"
					}

					Text {
						id: filePathText
						text: filePath + " (" + lineNumber + ")"
						Layout.fillWidth: true
						wrapMode: Text.WordWrap
					}
				}

				ListView {
					id: detailsListView

					anchors.left: parent.left
					anchors.right: parent.right
					height: count * 20
					spacing: 2

					model: details

					delegate: Component {
						Text {
							text: modelData
						}
					}
				}
			}

			MouseArea {
				anchors.fill: parent
				property int indexOfThisDelegate: index

				onClicked: {
					rootListView.currentIndex = index
				}

				onDoubleClicked: {
					rootListView.model.gotoSourceFileForRow(index);
				}
			}
		}
	}

	highlight: Rectangle {
		color: "lightblue"
		radius: 5
	}
}
