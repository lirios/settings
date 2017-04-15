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
import Liri.Settings 1.0

PrefletPage {
    anchors.fill: parent

    ModuleContainer {
        title: qsTr("Addresses")

        FluidControls.ListItem {
            text: qsTr("Configuration")
            rightItem: ComboBox {
                anchors.verticalCenter: parent.verticalCenter
                model: [
                    qsTr("Automatic (DHCP)"),
                    qsTr("Manual"),
                    qsTr("Link-Local Only"),
                    qsTr("Disabled")
                ]
            }
        }
    }

    ModuleContainer {
        title: qsTr("DNS")

        FluidControls.ListItem {
            text: qsTr("Automatic")
            rightItem: Switch {
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        MultiLineItem {
            model: ListModel {
                ListElement { address: "1.2.3.4" }
                ListElement { address: "1.2.3.4" }
                ListElement { address: "1.2.3.4" }
                ListElement { address: "1.2.3.4" }
            }
        }
    }

    ModuleContainer {
        title: qsTr("Routes")

        MultiLineItem {
            model: ListModel {
                ListElement { address: "1.2.3.4" }
                ListElement { address: "1.2.3.4" }
                ListElement { address: "1.2.3.4" }
                ListElement { address: "1.2.3.4" }
            }
        }
    }
}
