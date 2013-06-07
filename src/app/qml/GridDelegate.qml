
import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

ColumnLayout {
    Image {
        source: "image://desktoptheme/" + iconName
        sourceSize: Qt.size(48, 48)
        width: 48
        height: 48

        Layout.alignment: Qt.AlignCenter
    }

    Label {
        text: title
        horizontalAlignment: Qt.AlignHCenter
        wrapMode: Text.Wrap

        Layout.fillWidth: true
    }
}
