import qbs 1.0
import qbs.TextFile

SettingsModule {
    shortName: "network"
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
        files: [
            "HiddenWifiDialog.qml",
            "IPAddressField.qml",
            "IPAddressPage.qml",
            "MultiLineItem.qml",
            "PasswordListItem.qml",
            "Preflet.qml",
            "SecurityMD5.qml",
            "SecurityPage.qml",
            "SecurityTLS.qml",
            "WiredIdentityPage.qml",
            "WiredPage.qml",
            "WirelessPage.qml",
        ]
        prefix: "contents/"
        fileTags: ["liri.settings.contents"]
    }

    Group {
        name: "Translations"
        files: ["*_*.ts"]
        prefix: "translations/"
    }
}
