import qbs 1.0

QtGuiApplication {
    name: "liri-settings"
    targetName: "liri-settings"

    Depends { name: "lirideployment" }
    Depends { name: "Qt"; submodules: ["qml", "quick", "quickcontrols2"] }
    //Depends { name: "polkit_qt5"; submodules: ["core"] }

    cpp.defines: base.concat(['LIRISETTINGS_VERSION="' + project.version + '"'])

    files: ["*.cpp", "*.h", "*.qrc"]

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
        qbs.installDir: lirideployment.dataDir + "/liri-settings/translations"
        fileTagsFilter: "qm"
    }
}
