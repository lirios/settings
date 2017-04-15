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

Column {
    FluidControls.ListItem {
        enabled: enabledSwitch.checked
        visible: securityType.currentIndex == 1
        secondaryItem: TextField {
            id: tlsIdentityField
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width
            placeholderText: qsTr("Identity")
        }
    }

    FluidControls.ListItem {
        enabled: enabledSwitch.checked
        visible: securityType.currentIndex == 1
        secondaryItem: TextField {
            id: tlsUserCertificateField
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width
            placeholderText: qsTr("User certificate")
        }
    }

    FluidControls.ListItem {
        enabled: enabledSwitch.checked
        visible: securityType.currentIndex == 1
        secondaryItem: Column {
            Layout.fillWidth: true

            TextField {
                id: tlsCaCertificateField
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width
                placeholderText: qsTr("CA certificate")
                enabled: !tlsNoCaCheckBox.checked
            }

            CheckBox {
                id: tlsNoCaCheckBox
                text: qsTr("No CA certificate is required")
            }
        }
    }

    PasswordListItem {
        enabled: enabledSwitch.checked
        visible: securityType.currentIndex == 1
        placeholderText: qsTr("Private key password")
    }
}
