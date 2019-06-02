import qbs 1.0

LiriSettingsModulePlugin {
    shortName: "display"
    qmlModuleName: "Display"

    Depends { name: "Qt.dbus" }

    Qt.dbus.xml2CppHeaderFlags: ["-i", "outputdevice.h"]

    files: [
        "outputdevice.h",
        "outputsmodel.cpp",
        "outputsmodel.h",
        "plugin.cpp",
    ]

    Group {
        name: "QML Files"
        files: [
            "*.qml",
            "qmldir"
        ]
        fileTags: ["qml"]
    }

    Group {
        name: "D-Bus Interfaces"
        files: [
            "data/io.liri.Shell.OutputConfiguration1.xml",
            "data/io.liri.Shell.OutputDevice1.xml",
            "data/io.liri.Shell.OutputManagement1.xml",
        ]
        fileTags: ["qt.dbus.interface"]
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
