/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2016 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

import QtQuick 2.1
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import Fluid.Controls 1.0
import Liri.Settings 1.0
import Vibe.Hardware 1.0

PrefletPage {
    HardwareEngine {
        id: hardwareEngine
    }

    ModuleContainer {
        title: qsTr("Devices")
        visible: repeater.count > 0

        Repeater {
            id: repeater
            model: hardwareEngine.batteries
            delegate: BatteryListItem { battery: modelData }
        }
    }

    ModuleContainer {
        title: qsTr("Power Saving")

        ListItem {
            text: qsTr("Blank screen")
            rightItem: ComboBox {
                anchors.centerIn: parent
                textRole: "text"
                model: ListModel {
                    ListElement { text: qsTr("1 minute"); value: 60000 }
                    ListElement { text: qsTr("2 minutes"); value: 120000 }
                    ListElement { text: qsTr("3 minutes"); value: 180000 }
                    ListElement { text: qsTr("4 minutes"); value: 240000 }
                    ListElement { text: qsTr("5 minutes"); value: 300000 }
                    ListElement { text: qsTr("8 minutes"); value: 480000 }
                    ListElement { text: qsTr("10 minutes"); value: 600000 }
                    ListElement { text: qsTr("12 minutes"); value: 720000 }
                    ListElement { text: qsTr("15 minutes"); value: 900000 }
                    ListElement { text: qsTr("Never"); value: -1 }
                }
            }
        }

        ListItem {
            text: qsTr("Wi-Fi")
            subText: qsTr("Turn off Wi-Fi to save power")
            rightItem: Switch {
                anchors.centerIn: parent
            }
        }
    }

    ModuleContainer {
        title: qsTr("Suspend & Power Button")

        ListItem {
            text: qsTr("Automatic suspend")
            rightItem: BodyLabel {
                anchors.centerIn: parent
                text: qsTr("Off")
                color: Material.secondaryTextColor
            }
        }

        ListItem {
            text: qsTr("When the Power Button is pressed")
            rightItem: ComboBox {
                anchors.centerIn: parent
                textRole: "text"
                model: ListModel {
                    ListElement { text: qsTr("Suspend"); value: 0 }
                    ListElement { text: qsTr("Hibernate"); value: 1 }
                    ListElement { text: qsTr("Nothing"); value: 2 }
                }
            }
        }
    }
}
