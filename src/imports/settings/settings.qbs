import qbs 1.0

LiriQmlPlugin {
    name: "systemsettingsplugin"
    pluginPath: "Liri/Settings"

    Depends { name: "Qt"; submodules: ["gui", "xml"] }
    Depends { name: "Qt5Xdg" }
    Depends { name: "polkit" }

    condition: {
        if (!polkit.found) {
            console.error("polkit-gobject-1 is required to build " + targetName);
            return false;
        }

        return true;
    }

    Qt.core.enableKeywords: false

    files: ["*.cpp", "*.h", "qmldir", "*.qml"]
}
