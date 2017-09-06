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

import QtQuick 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import Fluid.Controls 1.0 as FluidControls

Item {
    readonly property bool isEventStream: Name == "sink-input-by-media-role:event"

    width: 400
    height: layout.implicitHeight + FluidControls.Units.smallSpacing * 2

    Component.onCompleted: {
        console.debug("Stream: ", JSON.stringify(Properties));
    }

    RowLayout {
        id: layout

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: FluidControls.Units.smallSpacing * 2
        width: parent.width
        spacing: FluidControls.Units.smallSpacing * 2

        FluidControls.Icon {
            name: isEventStream ? "communication/ring_volume" : PulseObject.client.properties["application.icon_name"]
            size: 48

            Layout.alignment: Qt.AlignTop
        }

        ColumnLayout {
            FluidControls.SubheadingLabel {
                text: isEventStream ? qsTr("Alerts") : PulseObject.client.properties["application.name"]
            }

            VolumeSlider {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
