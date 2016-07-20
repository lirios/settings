import QtQuick 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import Fluid.UI 1.0
import Hawaii.Settings 1.0

Item {
    ColumnLayout {
        anchors.centerIn: parent

        Icon {
            name: "action/settings"
            size: 96

            Layout.alignment: Qt.AlignHCenter
        }

        Label {
            text: qsTr("Welcome to Settings")
            font: FluidStyle.titleFont
            color: Material.secondaryTextColor
            horizontalAlignment: Qt.AlignHCenter

            Layout.fillWidth: true
        }

        Label {
            text: qsTr("Select an item from the list to see the available options.")
            font: FluidStyle.subheadingFont
            color: Material.secondaryTextColor
            horizontalAlignment: Qt.AlignHCenter
            wrapMode: Text.Wrap

            Layout.fillWidth: true
        }
    }
}
