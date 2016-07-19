import QtQuick 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import Fluid.UI 1.0
import Fluid.Controls 1.0
import Hawaii.Settings 1.0

Page {
    id: settingsPage

    title: qsTr("Settings")

    Material.background: "#f3f3f3"

    property var selectedModule

    Pane {
        id: listPane

        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
        }

        Material.background: "white"
        Material.elevation: 1

        width: 200
        padding: 0

        ListView {
            anchors.fill: parent

            model: PluginsModel {}

            section.property: "category"
            section.delegate: Subheader {
                id: subheader
                text: section

                ThinDivider {
                    anchors.top: parent.top
                    visible: subheader.y > 0
                }
            }

            delegate: SettingsListItem {}

            ScrollBar.vertical: ScrollBar {}
        }

        z: 2
    }

    Item {
        id: moduleView

        anchors {
            left: listPane.right
            top: parent.top
            bottom: parent.bottom
            right: parent.right
        }

        Loader {
            id: moduleLoader
            anchors.fill: parent
            source: selectedModule ? selectedModule.mainScriptUrl : ""
        }

        WelcomeView {
            anchors.fill: parent
            visible: moduleLoader.status == Loader.Null
        }

        ErrorView {
            id: errorView
            anchors.fill: parent
            visible: moduleLoader.status == Loader.Error
            moduleTitle: selectedModule ? selectedModule.title : ""
            errorMessage: moduleLoader.sourceComponent ? moduleLoader.sourceComponent.errorString() : ""
        }
    }
}
