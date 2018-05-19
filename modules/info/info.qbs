import qbs 1.0
import qbs.TextFile

LiriSettingsModule {
    shortName: "info"
    type: base.concat(["liri.settings.contents"])

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

    Rule {
        inputs: ["liri.desktop.template"]

        Artifact {
            filePath: "version.js"
            fileTags: ["liri.settings.contents"]
        }

        prepare: {
            var cmd = new JavaScriptCommand();
            cmd.description = "creating " + output.fileName;
            cmd.highlight = "filegen";
            cmd.sourceCode = function() {
                var file = new TextFile(output.filePath, TextFile.WriteOnly);
                file.writeLine('var version = "' + project.version + '";');
                file.close();
            };
            return [cmd];
        }
    }
}
