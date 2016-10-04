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
import Fluid.Controls 1.0 as FluidControls
import io.liri.networkmanager 0.1 as NM

Item {
    property var wiredModel

    id: wiredPage

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Icon {
                iconName: wiredModel.connected ? "network-wired" : "network-wired-disconnected"
                width: Units.iconSizes.large
                height: width
            }

            ColumnLayout {
                Label {
                    text: wiredModel.Name
                    font.bold: true
                }

                Label {
                    text: {
                        if (wiredModel.ConnectionState === NM.Enums.Activating) {
                            if (wiredModel.Type === NM.Enums.Vpn)
                                return wiredModel.VpnState;
                            else
                                return wiredModel.DeviceState;
                        } else if (wiredModel.ConnectionState === NM.Enums.Deactivating) {
                            if (wiredModel.Type === NM.Enums.Vpn)
                                return wiredModel.VpnState;
                            else
                                return wiredModel.DeviceState;
                        } else if (wiredModel.ConnectionState === NM.Enums.Deactivated) {
                            var result = wiredModel.LastUsed;
                            if (wiredModel.SecurityType > NM.Enums.None)
                                result += ", " + wiredModel.SecurityTypeString;
                            return result;
                        } else if (wiredModel.ConnectionState === NM.Enums.Activated) {
                            return qsTr("Connected");
                        }
                    }
                }
            }

            Item {
                Layout.fillWidth: true
            }

            Switch {
                checked: wiredModel.ConnectionState === NM.Enums.Activated
                onCheckedChanged: {
                    if (wiredModel.ConnectionState === NM.Enums.Deactivated) {
                        if (!wiredModel.Uuid) {
                            handler.addAndActivateConnection(wiredModel.DevicePath, wiredModel.SpecificPath);
                        } else {
                            // ask pass
                        }
                    } else {
                        handler.deactivateConnection(wiredModel.ConnectionPath, wiredModel.DevicePath);
                    }
                }
            }

            Layout.fillWidth: true
        }

        GridLayout {
            columns: 2
            rows: wiredModel.ConnectionDetails.length / 2
            columnSpacing: Units.smallSpacing
            rowSpacing: Units.smallSpacing
            flow: GridLayout.TopToBottom

            Repeater {
                model: wiredModel.ConnectionDetails.length / 2

                Label {
                    text: wiredModel.ConnectionDetails[index * 2] + ":"
                    font.bold: true

                    Layout.alignment: Qt.AlignRight
                }
            }

            Repeater {
                model: wiredModel.ConnectionDetails.length / 2

                Label {
                    text: wiredModel.ConnectionDetails[(index * 2) + 1]
                }
            }

            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        RowLayout {
            Button {
                text: qsTr("Add Profile...")
                enabled: false
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                onClicked: {
                    networkPreflet.profileDialog.service = wiredModel.get(0);
                    networkPreflet.profileDialog.visible = !networkPreflet.profileDialog.visible;
                }

                Icon {
                    anchors.fill:parent
                    anchors.margins:4
                    iconName: "emblem-system-symbolic"
                    width: Units.iconSizes.small
                    height: width
                }

                Layout.maximumWidth: 32
                Layout.maximumHeight: 32
            }

            Layout.fillWidth: true
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
