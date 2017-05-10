import qbs 1.0
import qbs.File

Product {
    property string shortName

    name: "Module (" + shortName + ")"
    type: "liri.settings.metadata"

    Depends { name: "lirideployment" }
    Depends { name: "cpp" }
    Depends { name: "Qt"; submodules: ["core", "qml", "quick"] }

    Rule {
        inputs: ["liri.settings.desktop"]

        Artifact {
            filePath: product.buildDirectory + "/metadata.desktop"
            fileTags: ["liri.settings.metadata"]
        }

        prepare: {
            var cmd = new JavaScriptCommand();
            cmd.description = "merge translations into " + input.filePath;
            cmd.highlight = "filegen";
            cmd.sourceCode = function() {
                File.copy(input.filePath, output.filePath);
            };
            return [cmd];
        }
    }

    Group {
        qbs.install: shortName != undefined
        qbs.installDir: lirideployment.dataDir + "/liri/settings/modules/" + shortName
        fileTagsFilter: "liri.settings.metadata"
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
