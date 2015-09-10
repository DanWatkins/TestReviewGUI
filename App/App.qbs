import qbs 1.0

Application {
	name: "QtTestReviewGUI"

	cpp.cxxLanguageVersion: "c++14"
	cpp.includePaths: [
        "../Src/",
		"../Ext/ValpineBase/Src"
	]

    Group {
        name: "C++"
        prefix: "**/"
        files: ["*.cpp", "*.h"]
    }


    Group {
        name: "Resources"
        prefix: "**/"
        files: ["*.qml*", "*.qrc"]
    }

	Depends { name: "cpp" }
	Depends { name: "Qt.core" }
	Depends { name: "Qt.quick" }
	Depends { name: "Qt.widgets" }

    Depends { name: "ValpineBase" }
	Depends { name: "QtTestReviewGUI_Lib" }
}
