import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

TableView {
    id: tableView

    TableViewColumn {
        role: "status"
        title: "Status"
        width: 120
    }

    TableViewColumn {
        role: "class"
        title: "Class"
        width: 120
    }

    TableViewColumn {
        role: "name"
        title: "Name"
        width: 120
    }

    TableViewColumn {
        role: "message"
        title: "Message"
        width: 120
    }

    model: ListModel {
        ListElement {
            path: "C:/Users/Dan/Desktop/"
            recursive: "Yes"
            cleanFrequency: 10.5
        }

        ListElement {
            path: "C:/Program Files/"
            recursive: "Yes"
            cleanFrequency: 1.5
        }
    }

    Menu {
        id: contextMenu
        MenuItem {
            text: qsTr("Start")
        }
        MenuItem {
            text: qsTr("Stop")
        }
        MenuItem {
            text: qsTr("Force run")
        }

        MenuSeparator { }

        MenuItem {
            text: qsTr("Delete")
        }
        MenuItem {
            text: qsTr("Edit conditions...")
        }
    }

    rowDelegate: Item {
        Rectangle {
            anchors {
                left: parent.left
                right: parent.right
                verticalCenter: parent.verticalCenter
            }
            height: parent.height
            color: styleData.selected ? 'lightblue' : 'white'

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.RightButton
                propagateComposedEvents: true

                signal rightClick()

                onReleased: {
                    mouse.accepted = false
                    tableView.selection.deselect(0, tableView.rowCount-1)
                    tableView.selection.select(styleData.row)
                    contextMenu.popup()
                }
            }
        }
    }
}
