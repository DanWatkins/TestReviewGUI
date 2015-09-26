//=============================================================================|
// Copyright (C) 2015 Dan Watkins
// This file is licensed under the MIT License.
//=============================================================================|

import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

import ValpineBase 1.0
import QtTestReviewGUI 1.0

Item {
	property alias groupBox: internalGroupBox
	default property alias children: internalItem.children

	GroupBox {
		id: internalGroupBox
		anchors.fill: parent

		Item {
			id: internalItem
			anchors.fill: parent
		}
	}
}
