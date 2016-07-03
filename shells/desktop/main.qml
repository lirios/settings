/****************************************************************************
 * This file is part of Hawaii.
 *
 * Copyright (C) 2013-2016 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:GPL2+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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

import QtQuick 2.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import Fluid.Ui 1.0 as FluidUi
import org.hawaiios.systempreferences 0.1

ApplicationWindow {
    property real defaultMinimumWidth: FluidUi.Units.dp(800)
    property real defaultMinimumHeight: FluidUi.Units.dp(600)
    property real itemSize: FluidUi.Units.iconSizes.large

    id: window
    title: qsTr("System Preferences")
    width: minimumWidth
    height: minimumHeight
    minimumWidth: defaultMinimumWidth
    minimumHeight: defaultMinimumHeight
    maximumWidth: minimumWidth
    maximumHeight: minimumHeight
    header: ToolBar {
        RowLayout {
            anchors.fill: parent

            RowLayout {
                id: leftRow
                width: parent.width / 3

                ToolButton {
                    id: backButton
                    indicator: FluidUi.Icon {
                        anchors.centerIn: parent
                        iconName: "go-previous-symbolic"
                        width: FluidUi.Units.iconSizes.smallMedium
                        height: width
                        color: searchEntry.color
                    }
                    visible: pageStack.depth > 1
                    onClicked: {
                        window.minimumWidth = window.defaultMinimumWidth;
                        window.minimumHeight = window.defaultMinimumHeight;
                        pageStack.pop();
                    }
                }

                Layout.alignment: Qt.AlignLeft
            }

            Label {
                id: prefletTitle
                font.bold: true
                horizontalAlignment: Qt.AlignHCenter
                color: searchEntry.color
                width: parent.width / 3
                visible: pageStack.depth > 1
            }

            RowLayout {
                id: rightRow
                width: parent.width / 3

                TextField {
                    id: searchEntry
                    placeholderText: qsTr("Keywords")
                    color: Material.primaryHighlightedTextColor
                    visible: pageStack.depth === 1

                    Layout.minimumWidth: FluidUi.Units.gu(15)
                }

                Layout.alignment: Qt.AlignRight
            }
        }
    }

    Material.accent: Material.Blue
    Material.primary: Material.color(Material.BlueGrey, Material.theme === Material.Light
                                     ? Material.Shade700 : Material.Shade800)

    PluginManager {
        id: pluginManager
    }

    Pane {
        id: listPane
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: FluidUi.Units.dp(200)

        ListView {
            anchors.fill: parent
            model: PluginsModel {}
            section.property: "category"
            section.delegate: Label {
                text: section
                width: parent.width
                font.bold: true
                color: Material.accentColor
            }
            delegate: ItemDelegate {
                text: title
                width: parent.width
                onClicked: {
                    if (!model.mainScriptUrl)
                        return;

                    var component = Qt.createComponent(model.mainScriptUrl);
                    if (component.status !== Component.Ready) {
                        console.error(component.errorString());
                        return;
                    }

                    var item = component.createObject(null);

                    if (typeof(item.minimumWidth) != "undefined")
                        window.minimumWidth = item.minimumWidth;
                    if (typeof(item.minimumHeight) != "undefined")
                        window.minimumHeight = item.minimumHeight;

                    prefletTitle.text = title;
                    pageStack.push(item);
                }
            }

            ScrollBar.vertical: ScrollBar {}
        }
    }

    StackView {
        id: pageStack
        anchors.left: listPane.right
        anchors.top: listPane.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        initialItem: Item {
            ColumnLayout {
                anchors.centerIn: parent

                FluidUi.Icon {
                    iconName: "preferences-system"
                    width: FluidUi.Units.iconSizes.enormous
                    height: width

                    Layout.alignment: Qt.AlignHCenter
                }

                Label {
                    text: qsTr("Welcome to the System Preferences")
                    horizontalAlignment: Qt.AlignHCenter

                    Layout.fillWidth: true
                }

                Label {
                    text: qsTr("Select a panel in the side list to see the available options.")
                    horizontalAlignment: Qt.AlignHCenter
                    wrapMode: Text.Wrap

                    Layout.fillWidth: true
                }
            }
        }
    }

    Component.onCompleted: {
        // Load the plugin specified by the command line
        if (Qt.application.arguments.length >= 2) {
            var plugin = pluginManager.getByName(Qt.application.arguments[1]);
            if (plugin) {
                prefletTitle.text = plugin.title;
                window.width = plugin.item.width;
                window.height = plugin.item.height;
                pageStack.push(plugin.item);
            }
        }
    }
}
