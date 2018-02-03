/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2018 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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
import QtQuick.Controls 2.2
import Vibe.PulseAudio 1.0 as PA

Item {
    height: Math.max(slider.implicitHeight, muteSwitch.implicitHeight) + label.paintedHeight

    RowLayout {
        width: parent.width

        Slider {
            id: slider

            from: PA.PulseAudio.MinimalVolume
            to: PA.PulseAudio.MaximalVolume
            value: Volume
            onMoved: Volume = value

            Layout.fillWidth: true
        }

        Switch {
            id: muteSwitch

            checked: !Muted
            onClicked: Muted = !checked
        }
    }

    Label {
        id: label

        readonly property real position: (slider.width / slider.to) * PA.PulseAudio.NormalVolume

        x: (Qt.application.layoutDirection == Qt.RightToLeft ? slider.width - position : position) - width / 2
        y: slider.implicitHeight / 1.2
        z: slider.z - 1
        font.pixelSize: slider.handle.height
        opacity: 0.5
        text: qsTr("100%")

        MouseArea {
            anchors.fill: parent
            onClicked: slider.value = PA.PulseAudio.NormalVolume
        }
    }
}
