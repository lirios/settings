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
import Fluid.Controls 1.0 as FluidControls
import Liri.Settings 1.0

PrefletPage {
    anchors.fill: parent

    ModuleContainer {
        title: qsTr("General")

        FluidControls.ListItem {
            secondaryItem: TextField {
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width
                text: wiredSettings.name
                placeholderText: qsTr("Name")
                onAccepted: wiredSettings.name = text
            }
        }

        FluidControls.ListItem {
            secondaryItem: CheckBox {
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Connect automatically")
                checked: wiredSettings.autoConnect
                onCheckedChanged: wiredSettings.autoConnect = checked
            }
        }

        FluidControls.ListItem {
            secondaryItem: CheckBox {
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Make available to other users")
                checked: wiredSettings.availableToOtherUsers
                onCheckedChanged: wiredSettings.availableToOtherUsers = checked
            }
        }
    }

    ModuleContainer {
        title: qsTr("Address")

        FluidControls.ListItem {
            text: qsTr("Link Speed")
            secondaryItem: SpinBox {
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width
                from: 0
                value: wiredSettings.speed
                textFromValue: function(value, locale) {
                    if (value === 0)
                        return qsTr("Automatic");
                    return Number(value).toLocaleString(locale, 'f', 0);
                }
                onValueChanged: wiredSettings.speed = value
            }
        }

        FluidControls.ListItem {
            text: qsTr("MAC address")
            rightItem: ComboBox {
                anchors.verticalCenter: parent.verticalCenter
                model: ["S", "M"]
            }
        }

        FluidControls.ListItem {
            secondaryItem: TextField {
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width
                placeholderText: qsTr("Cloned Address")
                inputMask: "HH:HH:HH:HH:HH:HH;_"
                text: wiredSettings.clonedMacAddress
                onAccepted: wiredSettings.clonedMacAddress = text
            }
        }

        FluidControls.ListItem {
            text: qsTr("MTU")
            secondaryItem: SpinBox {
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width
                from: 0
                value: wiredSettings.mtu
                textFromValue: function(value, locale) {
                    if (value === 0)
                        return qsTr("Automatic");
                    return Number(value).toLocaleString(locale, 'f', 0);
                }
                onValueChanged: wiredSettings.mtu = value
            }
        }
    }
}
