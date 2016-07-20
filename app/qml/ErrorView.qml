/****************************************************************************
 * This file is part of Hawaii.
 *
 * Copyright (C) 2016 Michael Spencer
 *
 * Author(s):
 *    Michael Spencer <sonrisesoftware@gmail.com>
 *
 * $BEGIN_LICENSE:GPL2+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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

import QtQuick 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import Fluid.Controls 1.0

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
