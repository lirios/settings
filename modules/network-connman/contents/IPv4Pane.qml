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

import QtQuick 2.1
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import Fluid.Controls 1.0 as FluidControls
import MeeGo.Connman 0.2

Item {
    property NetworkService service

    ColumnLayout {
        anchors.fill: parent

        RadioButton {
            text: qsTr("Obtain an IP address automatically")
            onClicked: {
                service.ipv4Config["Method"] = "dhcp";
                ipAddress.enabled = false;
                subnetMask.enabled = false;
                defaultGateway.enabled = false;
            }
        }

        RadioButton {
            text: qsTr("Use the following IP address")
            onClicked: {
                service.ipv4Config["Method"] = "manual";
                ipAddress.enabled = true;
                subnetMask.enabled = true;
                defaultGateway.enabled = true;
            }
        }

        GridLayout {
            Label {
                text: qsTr("IP Address:")
            }

            Label {
                text: qsTr("Subnet Mask:")
            }

            Label {
                text: qsTr("Default Gateway:")
            }

            TextField {
                id: ipAddress
            }

            TextField {
                id: subnetMask
            }

            TextField {
                id: defaultGateway
            }
        }

        RadioButton {
            text: qsTr("Obtain DNS server address automatically")
        }

        RadioButton {
            text: qsTr("Use the following DNS server addresses")
        }

        GridLayout {
            Label {
                text: qsTr("Primary DNS Server:")
            }

            Label {
                text: qsTr("Secondary DNS Server:")
            }

            TextField {
                id: primaryDns
            }

            TextField {
                id: secondaryDns
            }
        }

        CheckBox {
            text: qsTr("Connect automatically")
        }
    }
}
