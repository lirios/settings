import qbs 1.0

LiriDynamicLibrary {
    name: "Liri.Settings"
    targetName: "systemsettingsplugin"

    Depends { name: "lirideployment" }
    Depends { name: "Qt"; submodules: ["gui", "xml", "qml", "quick"] }
    Depends { name: "Qt5Xdg" }
    Depends { name: "polkit" }

    condition: {
        if (!polkit.found) {
            console.error("polkit-gobject-1 is required to build " + targetName);
            return false;
        }

        return true;
    }

    cpp.defines: base.concat(["QT_NO_KEYWORDS"])

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
