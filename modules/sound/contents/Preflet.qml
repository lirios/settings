/****************************************************************************
 * This file is part of Settings.
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
import QtQuick.Controls.Material 2.0
import Fluid.Controls 1.0
import Liri.Settings 1.0
import Vibe.PulseAudio 1.0 as PA

PrefletPage {
    ModuleContainer {
        ListItem {
            text: qsTr("Media")
            rightItem: Slider {
                anchors.centerIn: parent
                from: 0
                to: 100
                value: 50
            }
        }

        ListItem {
            text: qsTr("Alerts")
            rightItem: Slider {
                anchors.centerIn: parent
                from: 0
                to: 100
                value: 50
            }
        }

        ListItem {
            text: qsTr("Alarms")
            rightItem: Slider {
                anchors.centerIn: parent
                from: 0
                to: 100
                value: 50
            }
        }
    }

    ModulePane {
        ListItem {
            text: qsTr("Alert Sound")
            rightItem: BodyLabel {
                anchors.centerIn: parent
                text: qsTr("Random Sound")
                color: Material.secondaryTextColor
            }
        }
    }

    ModuleContainer {
        title: qsTr("Output")

        ListItem {
            text: qsTr("Volume")
            rightItem: Slider {
                anchors.centerIn: parent
                from: 0
                to: 100
                value: 50
            }
            visible: outputsView.visible
        }

        Repeater {
            id: outputsView
            model: PA.SinkModel {}
            delegate: ListItem {
                iconName: Default ? "toggle/radio_button_checked" : "toggle/radio_button_unchecked"
                text: Description
                secondaryItem: ComboBox {
                    model: PA.CardModel
                    textRole: "Description"
                }
                rightItem: Button {
                    anchors.centerIn: parent
                    text: qsTr("Test")
                }
            }
            visible: count > 0
        }

        ListItem {
            text: qsTr("Balance")
            rightItem: Slider {
                anchors.centerIn: parent
                from: 0
                to: 100
                value: 50
            }
            visible: outputsView.visible
        }

        ListItem {
            text: qsTr("No output devices available")
            opacity: 0.7
            visible: !outputsView.visible
        }
    }

    ModuleContainer {
        title: qsTr("Input")

        ListItem {
            text: qsTr("Volume")
            rightItem: Slider {
                anchors.centerIn: parent
                from: 0
                to: 100
                value: 50
            }
        }

        Repeater {
            id: inputsView
            model: PA.SourceModel {}
            delegate: ListItem {
                iconName: Default ? "toggle/radio_button_checked" : "toggle/radio_button_unchecked"
                text: Description
            }
            visible: count > 0
        }

        ListItem {
            text: qsTr("No input devices available")
            opacity: 0.7
            visible: !inputsView.visible
        }
    }
}
