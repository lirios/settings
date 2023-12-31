/****************************************************************************
 * This file is part of Settings.
 *
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

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import Fluid.Controls as FluidControls

Item {
    property string moduleTitle
    property alias message: messageLabel.text

    ColumnLayout {
        anchors.centerIn: parent
        width: parent.width - 32

        FluidControls.Icon {
            source: FluidControls.Utils.iconUrl("alert/warning")
            size: 96
            color: Material.color(Material.Red)

            Layout.alignment: Qt.AlignHCenter
        }

        FluidControls.TitleLabel {
            text: qsTr("Error loading \"%1\"").arg(moduleTitle)
            color: Material.secondaryTextColor
            horizontalAlignment: Qt.AlignHCenter

            Layout.fillWidth: true
        }

        FluidControls.SubheadingLabel {
            id: messageLabel
            color: Material.secondaryTextColor
            horizontalAlignment: Qt.AlignHCenter
            wrapMode: Text.Wrap

            Layout.fillWidth: true
        }
    }
}
