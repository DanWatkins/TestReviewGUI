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

ListView {
	id: rootListView
	anchors.fill: parent

	function showMessagesForIndex(index) {
		console.log(index);
	}

	delegate: Component {
		id: myDelegate

		Item {
			width: 180
			height: 40

			Row {
				anchors.fill: parent
				anchors.margins: 5

				Image {
					width: 25
					height: 25

					source: "error.png"
				}

				Text { text: '<b>Name:</b> ' }
			}

			MouseArea {
				anchors.fill: parent

				onClicked: {
					rootListView.currentIndex = index
				}
			}
		}
	}

	highlight: Rectangle {
		color: "lightblue"
		radius: 5
	}
}
