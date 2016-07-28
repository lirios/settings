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
    enabled: false

    property NetworkService service

    GridLayout {
        anchors.fill: parent
        columns: 2
        rows: 7
        flow: GridLayout.TopToBottom

        Label {
            text: qsTr("802.1x Security")

            Layout.alignment: Qt.AlignRight
        }

        Label {
            text: qsTr("Authentication:")

            Layout.alignment: Qt.AlignRight
        }

        Label {
            text: qsTr("Username:")

            Layout.alignment: Qt.AlignRight
        }

        Label {
            text: qsTr("Password:")

            Layout.alignment: Qt.AlignRight
        }

        Item {
            Layout.fillWidth: true
        }

        Item {
            Layout.fillWidth: true
        }

        Item {
            Layout.fillHeight: true
        }

        CheckBox {
            id: security
        }

        ComboBox {
            id: securityType
            model: [ qsTr("None"), qsTr("MD5") ]
        }

        TextField{
            id: userName
        }

        TextField {
            id: password
        }

        CheckBox {
            text: qsTr("Ask for this password every time")
        }

        CheckBox {
            text: qsTr("Show password")
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
