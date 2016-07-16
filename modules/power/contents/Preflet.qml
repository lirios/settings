/****************************************************************************
 * This file is part of Hawaii.
 *
 * Copyright (C) 2015-2016 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

import QtQuick 2.1
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import Fluid.Controls 1.0
import Fluid.UI 1.0
import org.hawaiios.hardware 0.1

Page {
    HardwareEngine {
        id: hardwareEngine
    }

    Pane {
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 64
        }

        width: column.width
        height: column.height
        padding: 0

        Material.background: "white"
        Material.elevation: 1

        Column {
            id: column

            width: 400

            Subheader {
                text: qsTr("Devices")
            }

            ListItem {
                visible: repeater.count == 0
                enabled: false
                text: qsTr("No devices found!")
                iconName: "alert/warning"
            }

            Repeater {
                id: repeater
                model: hardwareEngine.batteries
                delegate: BatteryListItem { battery: modelData }
            }
        }
    }
}
