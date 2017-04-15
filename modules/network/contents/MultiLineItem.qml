/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2017 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import Fluid.Controls 1.0 as FluidControls

Repeater {
    id: repeater

    FluidControls.ListItem {
        id: listItem
        //text: qsTr("DNS")
        secondaryItem: IPAddressField {
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
            width: parent.width
            placeholderText: qsTr("Address")
            text: model.address
        }
        rightItem: Row {
            anchors.verticalCenter: parent.verticalCenter

            ToolButton {
                id: removeButton

                icon.source: FluidControls.Utils.iconUrl("content/remove_circle")

                ToolTip.text: qsTr("Remove")
                ToolTip.visible: hovered && visible

                opacity: 0.5
                visible: listItem.hovered && repeater.model.count > 1
                onClicked: {
                    repeater.model.remove(index);
                }
            }

            ToolButton {
                id: addButton

                icon.source: FluidControls.Utils.iconUrl("content/add_circle")
                icon.color: Material.color(Material.Blue, Material.Shade800)

                ToolTip.text: qsTr("Add")
                ToolTip.visible: hovered && visible

                visible: index === repeater.model.count - 1
                onClicked: {
                    repeater.model.append({address: ""});
                }
            }
        }
    }
}
