import qbs 1.0

Project {
    name: "Settings"

    readonly property string version: "0.9.0"

    property bool useStaticAnalyzer: false

    condition: qbs.targetOS.contains("linux") && !qbs.targetOS.contains("android")

    minimumQbsVersion: "1.9.0"

    qbsSearchPaths: ["qbs"]

    references: [
        "app/app.qbs",
        "modules/appearance/appearance.qbs",
        "modules/background/background.qbs",
        "modules/display/display.qbs",
        "modules/info/info.qbs",
        "modules/keyboard/keyboard.qbs",
        "modules/users/users.qbs",
        "src/imports/settings/settings.qbs",
    ]
}
