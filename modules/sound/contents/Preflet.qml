/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2016 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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
import QtQuick.Controls 2.0
import Fluid.Controls 1.0
import Hawaii.SystemSettings 1.0

PrefletPage {
    ModulePane {
        ListItem {
            iconName: sound.iconName
            text: qsTr("Sound volume")
            interactive: false

            valueText: sound.muted || sound.master == 0 ? qsTr("Muted") : sound.master + "%"
            rightItem: Slider {
                id: soundslider

                width: parent.width
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: Units.dp(7)

                from: 0
                to: 100

                value: sound.muted ? 0 : sound.master

                onValueChanged: {
                    if (value != sound.master) {
                        sound.muted = value == 0
                        sound.master = value
                        value = Qt.binding(function() {
                            return sound.muted ? 0 : sound.master
                        })
                    }
                }
            }
        }
    }

/*
    Sound {
        id: sound

        property string iconName: sound.muted || sound.master == 0
                ? "av/volume_off"
                : sound.master <= 33 ? "av/volume_mute"
                : sound.master >= 67 ? "av/volume_up"
                : "av/volume_down"
    }
*/
}
