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
import MeeGo.Connman 0.2

Item {
    id: wiredPage

    SystemPalette {
        id: palette
    }

    TechnologyModel {
        id: wiredModel
        name: "ethernet"
    }

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Icon {
                iconName: wiredModel.connected ? "network-wired" : "network-wired-disconnected"
                width: 48
                height: 48
            }

            ColumnLayout {
                Label {
                    text: qsTr("Wired")
                    font.bold: true
                }

                Label {
                    text: {
                        if (wiredModel.powered)
                            return wiredModel.connected ? qsTr("Connected") : qsTr("Disconnected");
                        return qsTr("Unavailable");
                    }
                }
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                property NetworkService service: wiredModel.get(0)

                text: wiredModel.connected ? qsTr("Disconnect") : qsTr("Connect")
                onClicked: wiredModel.connected ? service.requestDisconnect() : service.requestConnect()
            }

            CheckBox {
                text: qsTr("Enable")
                checked: wiredModel.powered
                onClicked: wiredModel.powered = !wiredModel.powered
            }

            Layout.fillWidth: true
        }

        ListView {
            id: profilesList
            model: wiredModel
            delegate: ListItem.Standard {
                text: model.networkService.name
            }
            visible: count > 1

            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        WiredInformation {
            service: wiredModel.get(0)
            visible: profilesList.count == 1

            Layout.fillWidth: true
        }

        Item {
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
                    width: 22
                    height: 22
                    color: palette.text
                }

                Layout.maximumWidth: 32
                Layout.maximumHeight: 32
            }

            Layout.fillWidth: true
        }
    }
}
