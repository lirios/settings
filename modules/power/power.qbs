import qbs 1.0

SettingsModule {
    shortName: "power"

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
