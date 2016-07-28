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
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import MeeGo.Connman 0.2

Item {
    property NetworkService service

    GridLayout {
        anchors.fill: parent
        columns: 2
        rows: service.state === "online" ? 7 : 1
        flow: GridLayout.TopToBottom

        Label {
            text: qsTr("Hardware Address:")

            Layout.alignment: Qt.AlignRight
        }

        Label {
            text: qsTr("IP Address:")
            visible: service.state === "online"

            Layout.alignment: Qt.AlignRight
        }

        Label {
            text: qsTr("Subnet Mask:")
            visible: service.state === "online"

            Layout.alignment: Qt.AlignRight
        }

        Label {
            text: qsTr("Default Gateway:")
            visible: service.state === "online"

            Layout.alignment: Qt.AlignRight
        }

        Label {
            text: qsTr("DNS Server:")
            visible: service.state === "online"

            Layout.alignment: Qt.AlignRight
        }

        Label {
            text: qsTr("Domain names:")
            visible: service.state === "online"

            Layout.alignment: Qt.AlignRight
        }

        Item {
            Layout.fillHeight: true
        }

        Label {
            text: service.ethernet["Address"]
        }

        Label {
            text: service.state === "online" ? service.ipv4["Address"] : ""
            visible: service.state === "online"
        }

        Label {
            text: service.state === "online" ? service.ipv4["Netmask"] : ""
            visible: service.state === "online"
        }

        Label {
            text: service.state === "online" ? service.ipv4["Gateway"] : ""
            visible: service.state === "online"
        }

        Label {
            text: service.state === "online" ? service.nameservers.join(", ") : ""
            visible: service.state === "online"
        }

        Label {
            text: service.state === "online" ? service.domains.join(", ") : ""
            visible: service.state === "online"
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
