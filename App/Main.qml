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

ApplicationWindow {
    id: root
	title: qsTr("QtTestReviewGUI - v" + appVersion)
	width: 750
	height: 400
    visible: true

	Component.onCompleted: {
		if (openFilepath) {
			doFile(openFilepath);
		}
	}

	property var savedFilepath: qsTr("")


	function doFile(filepath) {
		console.log("Doing file " + filepath);
		savedFilepath = filepath;
		testTableView.model.parseFile(savedFilepath);
		testTableView.expandAll();
	}

	//consider making a root c++ type to replace AplicationWindow
	Connections {
		target: appSingleInstance

		onReceivedArguments: {
			if (arguments[0].length == 2) {
				doFile(arguments[0][1]);
			}

			for (var n=0; n<arguments[0].length; n++) {
				console.log(arguments[0][n]);
			}
		}
	}

    menuBar: MenuBar {
        Menu {
            title: "File"

            MenuItem {
                text: "Open"
                onTriggered: {
                    fileDialog.open();
                }
            }

            MenuSeparator { }

            MenuItem {
                text: "Settings"
                onTriggered: {
                    settingsDialog.showNormal();
                }
            }
        }

        Menu {
            title: "View"

            MenuItem {
                text: "Show passed tests"
                checkable: true
                checked: true
            }

            MenuItem {
                text: "Show failed tests"
                checkable: true
                checked: true
            }

			MenuItem {
				text: "Refresh"
				shortcut: "F5"

				onTriggered: {
					doFile(savedFilepath);
				}
			}
        }
    }

    SplitView {
        anchors.fill: parent
		orientation: Qt.Horizontal

		ProxiedGroupBox {
			groupBox.title: "Tests"
			groupBox.anchors.margins: 5

			Layout.minimumWidth: 200
			Layout.fillWidth: true

			TestResultsTreeView {
				id: testTableView
				anchors.fill: parent
				model: TestResultsTreeViewModel {}

				onDoubleClicked: {
					messagesTableView.showMessagesForIndex(currentIndex);
				}

				Component.onCompleted: {
					doFile(qsTr("C:/Users/Dan/Desktop/here.json"));
				}
			}
		}

		ProxiedGroupBox {
			groupBox.title: "Messages"
			groupBox.anchors.margins: 5

			width: 300
			Layout.minimumWidth: 200

			MessagesTableView {
				id: messagesTableView
				anchors.fill: parent
			}
		}
    }

    FileDialog {
        id: fileDialog
        modality: Qt.WindowModal
        title: "File to parse"
        selectMultiple: false
        nameFilters: [ "All files (*)" ]
        selectedNameFilter: "All files (*)"

        onAccepted: {  
			doFile(Qt.resolvedUrl(fileUrl));
        }
    }

	Window {
		id: settingsDialog
		modality: Qt.WindowModal
		title: "Settings"
		minimumWidth: pane.width
		maximumWidth: pane.width
		minimumHeight: pane.height
		maximumHeight: pane.height

		SettingsPane {
			id: pane
		}
	}

    statusBar: StatusBar {
        Row {
            spacing: 15

            Label {
                text: testTableView.model.statusText
            }

            Label {
                text: {
                    var t1 = testTableView.model.dateTime_started.getTime();
                    var t2 = testTableView.model.dateTime_finished.getTime();

                    return "Total Execution Time (ms): <font color=\"blue\">" + (t2-t1) + "</font>";
                }
            }

            Label {
                text: "Execution DateTime: <font color=\"blue\">" + testTableView.model.dateTime_finished + "</font>"
            }
        }
    }
}
