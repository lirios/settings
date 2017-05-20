import qbs 1.0

QtGuiApplication {
    name: "liri-settings"
    targetName: "liri-settings"

    Depends { name: "lirideployment" }
    Depends { name: "Qt"; submodules: ["qml", "quick", "quickcontrols2"] }
    Depends { name: "Translations" }
    //Depends { name: "polkit_qt5"; submodules: ["core"] }

    cpp.defines: base.concat(['LIRISETTINGS_VERSION="' + project.version + '"'])

    files: ["*.cpp", "*.h", "*.qrc"]

    Group {
        name: "Desktop File"
        files: ["io.liri.Settings.desktop.in"]
        fileTags: ["liri.desktop.template"]
    }

    Group {
        name: "Desktop File Translations"
        files: ["io.liri.Settings_*.desktop"]
        prefix: "translations/"
        fileTags: ["liri.desktop.translations"]
    }

    Group {
        name: "Translations"
        files: ["*_*.ts"]
        prefix: "translations/"
    }

    Group {
        qbs.install: true
        qbs.installDir: lirideployment.binDir
        fileTagsFilter: product.type
    }

    Group {
        qbs.install: true
        qbs.installDir: lirideployment.applicationsDir
        fileTagsFilter: "liri.desktop.file"
    }

    Group {
        qbs.install: true
        qbs.installDir: lirideployment.dataDir + "/liri-settings/translations"
        fileTagsFilter: "qm"
    }
}
