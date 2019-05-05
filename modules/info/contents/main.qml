/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2018 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 * Copyright (C) 2015 Michael Spencer <sonrisesoftware@gmail.com>
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
import Fluid.Controls 1.0 as FluidControls
import QtGSettings 1.0
import Liri.Device 1.0 as Device
import Liri.Settings 1.0

ModulePage {
    property int developerClickCount: 0
    readonly property int developerTotalClicks: 7
    readonly property int developerClickRemaining: developerTotalClicks - developerClickCount

    GSettings {
        id: systemSettings
        schema.id: "io.liri.system"
        schema.path: "/io/liri/system/"
    }

    ModuleContainer {
        title: qsTr("Operating System")

        FluidControls.ListItem {
            leftItem: FluidControls.Icon {
                name: Device.LocalDevice.osRelease.logoIconName
                size: 24

                Image {
                    anchors.fill: parent
                    source: parent.status === Image.Ready ? "" : Qt.resolvedUrl("logo.png")
                    sourceSize.width: width
                    sourceSize.height: height
                }
            }
            text: {
                if (Device.LocalDevice.osRelease.prettyName)
                    return Device.LocalDevice.osRelease.prettyName;
                if (Device.LocalDevice.osRelease.name && Device.LocalDevice.osRelease.version)
                    return Device.LocalDevice.osRelease.name + " " + Device.LocalDevice.osRelease.version;
                return Device.LocalDevice.osRelease.name;
            }
            onClicked: {
                if (systemSettings.developerMode)
                    return;

                developerClickCount++;

                if (developerClickRemaining == 0) {
                    snackBar.open(qsTr("You are now a developer!"));
                    systemSettings.developerMode = true;
                } else if (developerClickRemaining <= 3) {
                    snackBar.open(qsTr("You are now %1 steps from becoming a " +
                                       "developer").arg(developerClickRemaining));
                }
            }
        }

        FluidControls.ListItem {
            text: qsTr("Open Web site...")
            visible: Device.LocalDevice.osRelease.homeUrl.toString() !== ""
            onClicked: Qt.openUrlExternally(Device.LocalDevice.osRelease.homeUrl)
        }

        FluidControls.ListItem {
            text: qsTr("Obtain Support...")
            visible: Device.LocalDevice.osRelease.supportUrl.toString() !== ""
            onClicked: Qt.openUrlExternally(Device.LocalDevice.osRelease.supportUrl)
        }

        FluidControls.ListItem {
            text: qsTr("Report a Bug...")
            visible: Device.LocalDevice.osRelease.bugReportUrl.toString() !== ""
            onClicked: Qt.openUrlExternally(Device.LocalDevice.osRelease.bugReportUrl)
        }

        FluidControls.ListItem {
            text: qsTr("Privacy Policy...")
            visible: Device.LocalDevice.osRelease.privacyPolicyUrl.toString() !== ""
            onClicked: Qt.openUrlExternally(Device.LocalDevice.osRelease.privacyPolicyUrl)
        }
    }

    FluidControls.SnackBar {
        id: snackBar
    }
}
