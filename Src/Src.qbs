import qbs 1.0

Application {
    name: "QtTestReviewGUI"
    files: "qml.qrc"
	cpp.cxxLanguageVersion: "c++14"

    Group {
        name: "C++"
        files: ["*.cpp", "*.h"]
    }

    Group {
        name: "QML"
        files: "*.qml"
    }

    Depends { name: "cpp" }
    Depends { name: "Qt.core" }
    Depends { name: "Qt.quick" }
    Depends { name: "Qt.widgets" }
}
