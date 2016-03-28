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
import Qt.labs.controls 1.0
import Fluid.Ui 1.0 as FluidUi
import Fluid.Controls 1.0 as FluidControls
import org.hawaiios.networkmanager 0.1 as NM

Item {
    property var wiredModel

    id: wiredPage

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            FluidUi.Icon {
                iconName: wiredModel.connected ? "network-wired" : "network-wired-disconnected"
                width: FluidUi.Units.iconSizes.large
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
            columnSpacing: FluidUi.Units.smallSpacing
            rowSpacing: FluidUi.Units.smallSpacing
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

                FluidUi.Icon {
                    anchors.fill:parent
                    anchors.margins:4
                    iconName: "emblem-system-symbolic"
                    width: FluidUi.Units.iconSizes.small
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
