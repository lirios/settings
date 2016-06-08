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
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import MeeGo.Connman 0.2

Item {
    property NetworkService service
    property int profileNumber: 1

    GridLayout {
        anchors.fill: parent
        columns: 2
        rows: 6
        flow: GridLayout.TopToBottom

        Label {
            text: qsTr("Name:")

            Layout.alignment: Qt.AlignRight
        }

        Label {
            text: qsTr("MAC Address:")

            Layout.alignment: Qt.AlignRight
        }

        Label {
            text: qsTr("Cloned Address:")

            Layout.alignment: Qt.AlignRight
        }

        Label {
            text: qsTr("MTU:")

            Layout.alignment: Qt.AlignRight
        }

        Item {
            Layout.fillWidth: true
        }

        Item {
            Layout.fillHeight: true
        }

        TextField {
            id: name
            text: qsTr("Profile %1").arg(profileNumber)

            Layout.fillWidth: true
        }

        ComboBox {
            id: macAddress
            model: [ "%1 (%2)".arg(service.ethernet["Address"]).arg(service.ethernet["Interface"]) ]

            Layout.fillWidth: true
        }

        TextField{
            id: clonedAddress

            Layout.fillWidth: true
        }

        SpinBox {
            id: mtu
            value: service.ethernet["MTU"]
        }

        CheckBox {
            id: autoConnect
            checked: service.autoConnect
            text: qsTr("Connect automatically")
            onClicked: service.autoConnect = !service.autoConnect
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
