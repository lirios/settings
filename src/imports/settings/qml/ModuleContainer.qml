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

import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import Fluid.Controls 1.0 as FluidControls

Item {
    id: moduleContainer

    default property alias content: column.data

    property alias title: titleLabel.text

    readonly property real paneWidth: window.wideAspectRatio
                                      ? moduleContainer.width - (FluidControls.Units.largeSpacing * 4)
                                      : parent.width

    implicitWidth: parent.width
    implicitHeight: pane.height +
                    (window.wideAspectRatio ? (FluidControls.Units.smallSpacing * 4) : 0)

    ModulePane {
        id: pane

        anchors.centerIn: parent
        height: column.implicitHeight + divider.height

        Column {
            id: column

            width: moduleContainer.paneWidth

            FluidControls.Subheader {
                id: titleLabel
                textColor: Material.accent
                visible: text !== ""
            }
        }

        FluidControls.ThinDivider {
            id: divider

            anchors.left: parent.left
            anchors.top: column.bottom
            anchors.right: parent.right

            visible: !window.wideAspectRatio
        }
    }
}
