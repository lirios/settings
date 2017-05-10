import qbs 1.0

SettingsModulePlugin {
    shortName: "background"
    qmlModuleName: "Background"

    cpp.defines: []
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
        name: "Metadata"
        files: ["*.desktop.in"]
        fileTags: ["liri.settings.desktop"]
    }

    Group {
        name: "Contents"
        files: ["*.*"]
        prefix: "contents/"
        fileTags: ["liri.settings.contents"]
    }

    Group {
        name: "Translations"
        files: ["*_*.ts"]
        prefix: "translations/"
    }
}
