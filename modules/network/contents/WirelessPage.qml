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

Item {
    property var wirelessModel

    id: wirelessPage

    property var __syspal: SystemPalette {
        colorGroup: SystemPalette.Active
    }

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Icon {
                iconName: wirelessModel.available ? "network-wireless" : "network-wireless-disconnected"
                width: Units.iconSizes.smallMedium
                height: width
            }

            ColumnLayout {
                Label {
                    text: qsTr("Wireless")
                    font.bold: true
                }

                Label {
                    text: {
                        if (wirelessModel.powered)
                            return wirelessModel.connected ? qsTr("Connected") : qsTr("Disconnected");
                        return qsTr("Unavailable");
                    }
                }
            }

            Item {
                Layout.fillWidth: true
            }

            Button {
                text: qsTr("Rescan")
                enabled: wirelessModel.powered
                onClicked: wirelessModel.requestScan()
            }

            CheckBox {
                text: qsTr("Enable")
                checked: wirelessModel.powered
                onClicked: wirelessModel.powered = !wirelessModel.powered
            }

            Layout.fillWidth: true
        }

        ListView {
            id: servicesList
            model: wirelessModel
            clip: true
            delegate: FluidControls.StandardListItem {
                text: model.networkService.name

                RowLayout {
                    ToolButton {
                        Icon {
                            iconName: "emblem-system-symbolic"
                            width: Units.iconSizes.small
                            height: width
                            color:__syspal.text
                        }
                    }

                    Icon {
                        iconName: "network-wireless-encrypted-symbolic"
                        width: Units.iconSizes.small
                        height: width
                        color: __syspal.text
                        visible: !(model.networkService.security.length === 0 && model.networkService.security.contains("none"))
                    }

                    Icon {
                        iconName: {
                            if (model.networkService.strength > 80)
                                return "network-wireless-signal-excellent-symbolic";
                            if (model.networkService.strength > 55)
                                return "network-wireless-signal-good-symbolic";
                            if (model.networkService.strength > 30)
                                return "network-wireless-signal-ok-symbolic";
                            if (model.networkService.strength > 5)
                                return "network-wireless-signal-weak-symbolic";
                            return "network-wireless-signal-none-symbolic";
                        }
                        width: Units.iconSizes.small
                        height: width
                        color: __syspal.text
                    }
                }
            }
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        RowLayout {
            Button {
                text: qsTr("Use as Hotspot...")
                enabled: wirelessModel.connected
            }

            Button {
                text: qsTr("Connect to Hidden Network...")
                onClicked: {
                    var component = Qt.createComponent(Qt.resolvedUrl("HiddenWifiDialog.qml"));
                    var dialog = component.createObject(wirelessPage);
                    dialog.visible = true;
                }
            }

            Button {
                text: qsTr("History")
            }
        }
    }
}
