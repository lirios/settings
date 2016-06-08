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
import Fluid.Ui 1.0 as FluidUi
import Fluid.Controls 1.0 as FluidControls
import MeeGo.Connman 0.2

Item {
    id: networkPreflet
    width: FluidUi.Units.dp(800)
    height: FluidUi.Units.dp(600)

    property var profileDialog: ProfileDialog {}

    SystemPalette {
        id: palette
    }

    NetworkManagerFactory {
        id: networkManager
    }

    RowLayout {
        anchors.fill: parent

        ListView {
            id: technologiesView
            focus: true
            model: networkManager.instance.technologiesList()
            delegate: ListItem.Standard {
                property NetworkTechnology technology: networkManager.instance.getTechnology(modelData)

                iconName: {
                    if (modelData == "ethernet")
                        return "network-wired" + (technology.connected ? "" : "-disconnected") + "-symbolic";
                    else if (modelData == "wifi")
                        return "network-wireless-signal-" + (technology.connected ? "excellent" : "none") + "-symbolic";
                    return "network-vpn-symbolic";
                }
                text: {
                    if (modelData == "ethernet")
                        return qsTr("Wired");
                    else if (modelData == "wifi")
                        return qsTr("Wireless");
                    return qsTr("Unknown");
                }
                onClicked: {
                    ListView.currentIndex = index;
                    technologiesView.switchPage(modelData);
                }
            }
            width: parent.width / 6
            visible: networkManager.instance.available

            Layout.fillHeight: true

            Component.onCompleted: {
                if (visible)
                    switchPage(model[currentIndex])
            }

            function switchPage(tech) {
                switch (tech) {
                case "ethernet":
                    pageStack.push(Qt.resolvedUrl("WiredPage.qml"));
                    break;
                case "wifi":
                    pageStack.push(Qt.resolvedUrl("WirelessPage.qml"));
                    break;
                default:
                    break;
                }
            }
        }

        StackView {
            id: pageStack
            delegate: StackViewDelegate {
                function transitionFinished(properties) {
                    properties.exitItem.opacity = 1;
                }

                property Component pushTransition: StackViewTransition {
                    PropertyAnimation {
                        target: enterItem
                        property: "opacity"
                        from: 0
                        to: 1
                    }
                    PropertyAnimation {
                        target: exitItem
                        property: "opacity"
                        from: 1
                        to: 0
                    }
                }
            }
            initialItem: Item {
                width: parent.width
                height: parent.height
                visible: !networkManager.instance.available

                RowLayout {
                    spacing: 11

                    FluidUi.Icon {
                        iconName: "computer-fail"
                        width: 48
                        height: 48
                    }

                    ColumnLayout {
                        Label {
                            font.bold: true
                            text: qsTr("Network service unavailable");
                        }

                        Label {
                            text: qsTr("Please make sure the \"connman\" service is running.");
                        }

                        Layout.fillWidth: true
                    }
                }
            }

            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
