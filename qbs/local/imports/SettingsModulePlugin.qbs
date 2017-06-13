import qbs 1.0
import qbs.File
import qbs.TextFile

LiriDynamicLibrary {
    property string shortName
    property string qmlModuleName

    name: "Module (" + shortName + ")"
    targetName: shortName + "plugin"

    Depends { name: "lirideployment" }
    Depends { name: "Qt"; submodules: ["core", "qml", "quick"] }
    Depends { name: "LiriTranslations" }

    Group {
        qbs.install: shortName != undefined
        qbs.installDir: lirideployment.dataDir + "/liri/settings/modules/" + shortName
        fileTagsFilter: "liri.desktop.file"
    }

    Group {
        qbs.install: shortName != undefined
        qbs.installDir: lirideployment.dataDir + "/liri/settings/modules/" + shortName
        fileTagsFilter: "liri.settings.contents"
    }

    Group {
        qbs.install: qmlModuleName != undefined
        qbs.installDir: lirideployment.qmlDir + "/Liri/Settings/" + qmlModuleName
        fileTagsFilter: ["dynamiclibrary", "qml"]
    }

    Group {
        qbs.install: shortName != undefined
        qbs.installDir: lirideployment.dataDir + "/liri/settings/translations/modules"
        fileTagsFilter: "qm"
    }
}
