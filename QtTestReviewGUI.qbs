import qbs 1.0

Project {
	references: [
        "Ext"
	]

    StaticLibrary {
        name: "QtTestReviewGUI_Lib"
        cpp.cxxLanguageVersion: "c++14"
        cpp.includePaths: [
            "./Src/",
            "./Ext/ValpineBase/Src"
        ]


        Group {
            name: "C++"
            files: ["Src/**/*.cpp", "Src/**/*.h"]
        }

        Group {
            name: "QML"
            files: ["Src/**/*.qml"]
        }

        Depends { name: "cpp" }
        Depends { name: "Qt.core" }
        Depends { name: "Qt.quick" }
        Depends { name: "Qt.widgets" }
    }


    Application {
        name: "QtTestReviewGUI"

        cpp.cxxLanguageVersion: "c++14"
        cpp.includePaths: [
            "./Src/",
            "../Ext/ValpineBase/Src"
        ]

        Group {
            name: "C++"
            files: ["Src/Main.cpp", "Src/QtTestReviewGUI/qml.qrc"]
        }

        Depends { name: "cpp" }
        Depends { name: "Qt.core" }
        Depends { name: "Qt.quick" }
        Depends { name: "Qt.widgets" }
        Depends { name: "QtTestReviewGUI_Lib" }
    }


    Application {
        name: "QtTestReviewGUI_Tests"

        cpp.cxxLanguageVersion: "c++14"
        cpp.includePaths: [
            "./Ext/ValpineBase/Src",
            "./Src/"
        ]

        Group {
            name: "C++"
            files: ["Tests/**/*.cpp", "Tests/**/*.h"]
        }

        Depends { name: "cpp" }
        Depends { name: "Qt.core" }
        Depends { name: "Qt.testlib" }

        Depends { name: "QtTestReviewGUI_Lib" }
        Depends { name: "ValpineBase" }
    }
}
