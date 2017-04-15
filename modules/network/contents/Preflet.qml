/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2018 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtGSettings 1.0
import Fluid.Controls 1.0 as FluidControls
import Vibe.NetworkManager 1.0 as NM
import Liri.Settings 1.0

PrefletPage {
    id: networkPreflet

    //property var profileDialog: ProfileDialog {}

    NM.ConnectionIcon {
        id: connectionIconProvider

        function massageIconName(iconName) {
            var newName = iconName.replace("-activated", "");
            if (newName !== "")
                return newName + "-symbolic";
            return newName;
        }
    }

    NM.Handler {
        id: handler
    }

    NM.ConnectionModel {
        id: connectionModel
    }

    Component {
        id: wiredPage

        WiredPage {}
    }

    ModuleContainer {
        title: qsTr("Wired")
        visible: wiredRepeater.count > 0

        Repeater {
            id: wiredRepeater

            model: NM.TechnologyProxyModel {
                type: NM.TechnologyProxyModel.WiredType
                sourceModel: connectionModel
            }

            FluidControls.ListItem {
                icon.source: "image://fluidicontheme/" + model.symbolicIconName

                text: model.ItemUniqueName
                onClicked: window.pageStack.push(wiredPage, {"model": model})
            }
        }
    }

    ModuleContainer {
        title: qsTr("Wireless")
        visible: wirelessRepeater.count > 0

        Repeater {
            id: wirelessRepeater

            model: NM.TechnologyProxyModel {
                type: NM.TechnologyProxyModel.WirelessType
                sourceModel: connectionModel
            }

            FluidControls.ListItem {
                icon.source: "image://fluidicontheme/" + model.symbolicIconName

                text: model.ItemUniqueName
            }
        }
    }

    ModuleContainer {
        title: qsTr("Bluetooth")
        visible: bluetoothRepeater.count > 0

        Repeater {
            id: bluetoothRepeater

            model: NM.TechnologyProxyModel {
                type: NM.TechnologyProxyModel.BluetoothType
                sourceModel: connectionModel
            }

            FluidControls.ListItem {
                icon.source: "image://fluidicontheme/" + model.symbolicIconName

                text: model.ItemUniqueName
            }
        }
    }

    ModuleContainer {
        title: qsTr("Wimax")
        visible: wimaxRepeater.count > 0

        Repeater {
            id: wimaxRepeater

            model: NM.TechnologyProxyModel {
                type: NM.TechnologyProxyModel.WimaxType
                sourceModel: connectionModel
            }

            FluidControls.ListItem {
                icon.source: "image://fluidicontheme/" + model.symbolicIconName

                text: model.ItemUniqueName
            }
        }
    }

    ModuleContainer {
        title: qsTr("ADSL")
        visible: adslRepeater.count > 0

        Repeater {
            id: adslRepeater

            model: NM.TechnologyProxyModel {
                type: NM.TechnologyProxyModel.AdslType
                sourceModel: connectionModel
            }

            FluidControls.ListItem {
                icon.source: "image://fluidicontheme/" + model.symbolicIconName

                text: model.ItemUniqueName
            }
        }
    }

    ModuleContainer {
        title: qsTr("VPN")
        visible: vpnRepeater.count > 0

        Repeater {
            id: vpnRepeater

            model: NM.TechnologyProxyModel {
                type: NM.TechnologyProxyModel.VpnType
                sourceModel: connectionModel
            }

            FluidControls.ListItem {
                icon.source: "image://fluidicontheme/" + model.symbolicIconName

                text: model.ItemUniqueName
            }
        }
    }

    /*
    Component {
        id: wiredComponent

        WiredPage {}
    }

    Component {
        id: wirelessComponent

        WirelessPage {}
    }

    StackLayout {
        anchors.fill: parent
        currentIndex: connectionIconProvider.connectionIcon == "network-unavailable" ? 1 : 0

        RowLayout {
            ListView {
                id: technologiesView
                focus: true
                model: NM.AppletProxyModel {}
                section.property: "Section"
                delegate: FluidControls.ListItem {
                    readonly property string iconName: {
                        if (modelData == "ethernet")
                            return "network-wired" + (technology.connected ? "" : "-disconnected") + "-symbolic";
                        else if (modelData == "wifi")
                            return "network-wireless-signal-" + (technology.connected ? "excellent" : "none") + "-symbolic";
                        return "network-vpn-symbolic";
                    }

                    icon.source: "image://fluidicontheme/" + iconName

                    text: model.Name
                    onClicked: {
                        ListView.currentIndex = index;
                        technologiesView.switchPage(model.Type, model);
                    }
                }
                visible: connectionIconProvider.connectionIcon !== "network-unavailable"

                ScrollBar.vertical: ScrollBar {}
                Layout.fillHeight: true
                Layout.preferredWidth: FluidControls.Units.gu(12)

                Component.onCompleted: {
                    if (visible)
                        switchPage(model[currentIndex])
                }

                function switchPage(type, model) {
                    switch (type) {
                    case NM.Enums.Wired:
                        pageStack.push(wiredComponent, {"wiredModel": model});
                        break;
                    case NM.Enums.Wireless:
                        pageStack.push(wirelessComponent, {"wirelessModel": model});
                        break;
                    default:
                        break;
                    }
                }
            }

            StackView {
                id: pageStack

                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        ColumnLayout {
            spacing: FluidControls.Units.largeSpacing

            FluidControls.Icon {
                name: "computer-fail"
                width: FluidControls.Units.iconSizes.enormous
                height: width
            }

            Label {
                font.bold: true
                text: qsTr("Network service unavailable");
            }

            Label {
                text: qsTr("Please make sure the \"NetworkManager\" service is running.");
            }

            Item {
                Layout.fillHeight: true
            }

            Layout.alignment: Qt.AlignHCenter
        }
    }
    */
}
