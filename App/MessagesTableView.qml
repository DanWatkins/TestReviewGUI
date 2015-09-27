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

	model: ListModel {
		id: fruitModel

		ListElement {
			name: "Apple"
			cost: 2.45
		}
		ListElement {
			name: "Orange"
			cost: 3.25
		}
		ListElement {
			name: "Banana"
			cost: 1.95
		}
	}

	delegate: Component {
		id: myDelegate

		Item {
			width: 180
			height: 40

			Column {
				anchors.fill: parent
				anchors.margins: 5

				Text { text: '<b>Name:</b> ' + name }
				Text { text: '<b>Cost:</b> ' + cost }
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
