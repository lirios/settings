import qbs 1.0

LiriDynamicLibrary {
    name: "Liri.Settings"
    targetName: "systemsettingsplugin"

    Depends { name: "lirideployment" }
    Depends { name: "Qt"; submodules: ["gui", "xml", "qml", "quick"] }
    Depends { name: "Qt5Xdg" }

    files: ["*.cpp", "*.h"]

    Group {
        name: "QML Files"
        files: [
            "*.qml",
            "qmldir"
        ]
        fileTags: ["qml"]
    }

    Group {
        qbs.install: true
        qbs.installDir: lirideployment.qmlDir + "/Liri/Settings"
        fileTagsFilter: ["dynamiclibrary", "qml"]
    }
}
