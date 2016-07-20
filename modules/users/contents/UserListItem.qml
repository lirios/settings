/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2016 Michael Spencer <sonrisesoftware@gmail.com>
 *
 * $BEGIN_LICENSE:LGPL2.1+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import Fluid.Controls 1.0

ListItem {
    property alias iconSource: image.source
    property bool isAdminUser

    leftItem: [
        CircleImage {
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

        Icon {
            name: "action/account_circle"
            visible: !image.visible
            anchors.centerIn: parent
            size: 40
        }
    ]

    rightItem: Icon {
        name: "action/verified_user"
        anchors.centerIn: parent
        visible: isAdminUser
    }
}
