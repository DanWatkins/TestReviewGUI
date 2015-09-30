import qbs 1.0

StaticLibrary {
	name: "TestReviewGUI_Lib"
	cpp.cxxLanguageVersion: "c++14"
	cpp.includePaths: [
        "../Src/",
        "../Ext/ValpineBase/Src"
	]

    Group {
        name: "C++"
        prefix: "TestReviewGUI/**/"
        files: ["*.cpp", "*.h"]
    }


    Group {
        name: "Resources"
        prefix: "TestReviewGUI/Resources/**/"
        files: ["*.*"]
    }

	Depends { name: "cpp" }
	Depends { name: "Qt.core" }
	Depends { name: "Qt.quick" }
	Depends { name: "Qt.widgets" }
}
