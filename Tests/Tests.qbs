import qbs 1.0

Application {
    name: "QtTestReviewGUI_Tests"

    cpp.cxxLanguageVersion: "c++14"
    cpp.includePaths: [
        "../Ext/ValpineBase/Src",
        "../Src/"
    ]

    Group {
        name: "C++"
        prefix: "**/"
        files: ["*.cpp", "*.h"]
    }


    Group {
        name: "Resources"
        prefix: "Resources/**/"
        files: ["*.*"]
    }

    Depends { name: "cpp" }
    Depends { name: "Qt.core" }
    Depends { name: "Qt.testlib" }

    Depends { name: "QtTestReviewGUI_Lib" }
    Depends { name: "ValpineBase" }
}
