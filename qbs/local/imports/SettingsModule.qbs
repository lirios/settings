import qbs 1.0
import qbs.File
import qbs.TextFile

Product {
    property string shortName

    name: "Module (" + shortName + ")"

    Depends { name: "lirideployment" }
    Depends { name: "cpp" }
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
        qbs.install: shortName != undefined
        qbs.installDir: lirideployment.dataDir + "/liri/settings/translations/modules"
        fileTagsFilter: "qm"
    }
}
