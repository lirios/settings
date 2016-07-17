import QtQuick 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import Fluid.UI 1.0

Item {
    property string moduleTitle
    property alias errorMessage: messageLabel.text

    ColumnLayout {
        anchors.centerIn: parent
        width: parent.width - 32

        Icon {
            name: "alert/warning"
            size: 96
            color: Material.color(Material.Red)

            Layout.alignment: Qt.AlignHCenter
        }

        Label {
            text: qsTr("Error loading \"%1\"").arg(moduleTitle)
            font: FluidStyle.titleFont
            color: Material.secondaryTextColor
            horizontalAlignment: Qt.AlignHCenter

            Layout.fillWidth: true
        }

        Label {
            id: messageLabel
            font: FluidStyle.subheadingFont
            color: Material.secondaryTextColor
            horizontalAlignment: Qt.AlignHCenter
            wrapMode: Text.Wrap

            Layout.fillWidth: true
        }
    }
}
