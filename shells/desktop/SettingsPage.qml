import QtQuick 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import Fluid.UI 1.0
import Fluid.Controls 1.0
import org.hawaiios.systempreferences 0.1

Page {
    id: settingsPage

    title: qsTr("Settings")

    Material.background: "#f3f3f3"

    property string selectedModuleUrl

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

    StackView {
        id: moduleStack
        anchors.left: listPane.right
        anchors.top: listPane.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        initialItem: WelcomeView {}
    }
}
