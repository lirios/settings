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
import QtQuick.Layouts 1.3
import Qt.labs.controls 1.0
import Hawaii.SystemPreferences 1.0
import Fluid.Ui 1.0 as FluidUi
import Fluid.Controls 1.0 as FluidControls
import org.hawaiios.networkmanager 0.1 as NM

PrefletPage {
    id: networkPreflet
    width: FluidUi.Units.dp(800)
    height: FluidUi.Units.dp(600)

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
                delegate: FluidControls.StandardListItem {
                    iconName: {
                        if (modelData == "ethernet")
                            return "network-wired" + (technology.connected ? "" : "-disconnected") + "-symbolic";
                        else if (modelData == "wifi")
                            return "network-wireless-signal-" + (technology.connected ? "excellent" : "none") + "-symbolic";
                        return "network-vpn-symbolic";
                    }
                    text: model.Name
                    onClicked: {
                        ListView.currentIndex = index;
                        technologiesView.switchPage(model.Type, model);
                    }
                }
                visible: connectionIconProvider.connectionIcon !== "network-unavailable"

                ScrollBar.vertical: ScrollBar {}
                Layout.fillHeight: true
                Layout.preferredWidth: FluidUi.Units.gu(12)

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
            spacing: FluidUi.Units.largeSpacing

            FluidUi.Icon {
                iconName: "computer-fail"
                width: FluidUi.Units.iconSizes.enormous
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
}
