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
import QtQuick.Window 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import MeeGo.Connman 0.2

Window {
    title: service ? service.name : ""
    width: 640
    height: 480
    color: palette.window

    property NetworkService service: null

    SystemPalette {
        id: palette
    }

    ListModel {
        id: optionsModel

        ListElement { title: "Details"; value: "details" }
        ListElement { title: "Security"; value: "security" }
        ListElement { title: "Identity"; value: "identity" }
        ListElement { title: "IPv4"; value: "ipv4" }
        ListElement { title: "IPv6"; value: "ipv6" }
        ListElement { title: "Reset"; value: "reset" }
    }

    RowLayout {
        anchors.fill: parent

        TableView {
            model: optionsModel
            headerVisible: false
            currentRow: 0
            onActivated: {
                switch (row) {
                case 0:
                    pageStack.push({"item": Qt.resolvedUrl("DetailsPane.qml"),
                                    "properties": {"service": service}});
                    break;
                case 1:
                    pageStack.push({"item": Qt.resolvedUrl("SecurityPane.qml"),
                                    "properties": {"service": service}});
                    break;
                case 2:
                    pageStack.push({"item": Qt.resolvedUrl("IdentityPane.qml"),
                                    "properties": {"service": service}});
                    break;
                case 3:
                    pageStack.push({"item": Qt.resolvedUrl("IPv4Pane.qml"),
                                    "properties": {"service": service}});
                    break;
                case 4:
                    pageStack.push({"item": Qt.resolvedUrl("IPv6Pane.qml"),
                                    "properties": {"service": service}});
                    break;
                case 5:
                    pageStack.push({"item": Qt.resolvedUrl("ResetPane.qml"),
                                    "properties": {"service": service}});
                    break;
                default:
                    break;
                }
            }

            TableViewColumn { role: "title" }

            Layout.fillHeight: true
        }

        StackView {
            id: pageStack
            delegate: StackViewDelegate {
                function transitionFinished(properties) {
                    properties.exitItem.opacity = 1;
                }

                property Component pushTransition: StackViewTransition {}
            }

            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
