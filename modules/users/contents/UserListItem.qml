/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2018 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 * Copyright (C) 2016 Michael Spencer <sonrisesoftware@gmail.com>
 *
 * $BEGIN_LICENSE:GPL3+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

import QtQuick 2.4
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.1
import Fluid.Controls 1.0 as FluidControls

FluidControls.ListItem {
    property alias iconSource: image.source
    property bool isAdminUser
    property bool isCurrentUser

    signal removeUserRequested(bool removeFiles)

    FluidControls.AlertDialog {
        id: deleteDialog

        parent: ApplicationWindow.contentItem
        title: qsTr("Do you want to keep %1's files?").arg(subText)
        text: qsTr("It is possible to keep the home directory, mail spool and " +
                   "temporary files around when deleting a user account.")
        width: 400

        footer: DialogButtonBox {
            standardButtons: DialogButtonBox.Yes | DialogButtonBox.No | DialogButtonBox.Cancel
            onClicked: {
                if (button === standardButton(DialogButtonBox.Yes))
                    removeUserRequested(false);
                else if (button === standardButton(DialogButtonBox.No))
                    removeUserRequested(true);
            }
        }
    }

    leftItem: [
        FluidControls.CircleImage {
            id: image

            anchors.centerIn: parent
            width: 40
            height: width
            visible: status == Image.Ready

            Rectangle {
                anchors.fill: parent
                color: "transparent"
                radius: width/2
                border.color: Qt.rgba(0,0,0,0.3)
            }
        },

        FluidControls.Icon {
            source: FluidControls.Utils.iconUrl("action/account_circle")
            visible: !image.visible
            anchors.centerIn: parent
            size: 40
        }
    ]

    rightItem: RowLayout {
        anchors.centerIn: parent

        FluidControls.Icon {
            source: FluidControls.Utils.iconUrl("action/verified_user")
            visible: isAdminUser

            Layout.alignment: Qt.AlignVCenter
        }

        ToolButton {
            icon.source: FluidControls.Utils.iconUrl("content/remove_circle")
            enabled: modulePage.unlocked
            visible: !isCurrentUser
            onClicked: deleteDialog.open()

            ToolTip.text: qsTr("Remove user")
            ToolTip.delay: Qt.styleHints.mousePressAndHoldInterval
            ToolTip.visible: hovered

            Layout.alignment: Qt.AlignVCenter
        }
    }
}
