/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2013-2016 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:LGPL2.1+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import MeeGo.Connman 0.2

Item {
    property NetworkService service

    GridLayout {
        anchors.fill: parent
        columns: 2
        rows: service.state === "online" ? 6 : 1
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
    }
}
