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
    }
}
