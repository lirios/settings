import qbs 1.0

LiriSettingsModulePlugin {
    shortName: "display"
    qmlModuleName: "Display"

    Depends { name: "LiriWaylandClient" }

    //cpp.defines: []
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
        files: ["metadata.desktop.in"]
        fileTags: ["liri.desktop.template"]
    }

    Group {
        name: "Metadata Translations"
        files: ["metadata_*.desktop"]
        prefix: "translations/"
        fileTags: ["liri.desktop.translations"]
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
