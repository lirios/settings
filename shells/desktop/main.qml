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
import Qt.labs.controls 1.0
import Qt.labs.controls.material 1.0
import Fluid.Ui 1.0 as FluidUi
import org.hawaiios.systempreferences 0.1

ApplicationWindow {
    id: root
    title: qsTr("System Preferences")
    width: minimumWidth
    height: minimumHeight
    minimumWidth: defaultMinimumWidth
    minimumHeight: defaultMinimumHeight
    maximumWidth: minimumWidth
    maximumHeight: minimumHeight

    property real defaultMinimumWidth: FluidUi.Units.dp(640)
    property real defaultMinimumHeight: FluidUi.Units.dp(540)
    property real itemSize: FluidUi.Units.iconSizes.large

    header: ToolBar {
        RowLayout {
            anchors.fill: parent

            RowLayout {
                id: leftRow

                ToolButton {
                    id: backButton
                    indicator: FluidUi.Icon {
                        anchors.centerIn: parent
                        iconName: "go-previous-symbolic"
                        width: FluidUi.Units.iconSizes.smallMedium
                        height: width
                        color: "white"
                    }
                    visible: pageStack.depth > 1
                    onClicked: {
                        root.minimumWidth = root.defaultMinimumWidth;
                        root.minimumHeight = root.defaultMinimumHeight;
                        pageStack.pop();
                    }
                }

                Layout.alignment: Qt.AlignLeft
            }

            Label {
                id: prefletTitle
                font.bold: true
                horizontalAlignment: Qt.AlignHCenter
                color: "white"
                visible: pageStack.depth > 1

                Layout.fillWidth: true
            }

            RowLayout {
                id: rightRow

                TextField {
                    id: searchEntry
                    placeholderText: qsTr("Keywords")
                    color: "white"
                    visible: pageStack.depth === 1

                    Layout.alignment: Qt.AlignVCenter
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

    StackView {
        id: pageStack
        anchors.fill: parent
        initialItem: Item {
            Flickable {
                anchors.fill: parent
                contentWidth: mainLayout.childrenRect.width
                contentHeight: mainLayout.childrenRect.height
                boundsBehavior: (contentHeight > root.width) ? Flickable.DragAndOvershootBounds : Flickable.StopAtBounds

                ColumnLayout {
                    id: mainLayout

                    CategoryGrid {
                        title: qsTr("Personal")
                        categoryName: "personal"
                        categoryIconName: "avatar-default"
                        model: pluginManager.personalPlugins
                        visible: pluginManager.personalPlugins.length > 0
                    }

                    CategoryGrid {
                        title: qsTr("Hardware")
                        categoryName: "hardware"
                        categoryIconName: "applications-system"
                        model: pluginManager.hardwarePlugins
                        visible: pluginManager.hardwarePlugins.length > 0
                    }

                    CategoryGrid {
                        title: qsTr("System")
                        categoryName: "system"
                        categoryIconName: "system"
                        model: pluginManager.systemPlugins
                        visible: pluginManager.systemPlugins.length > 0
                    }
                }

                ScrollBar.vertical: ScrollBar {}
            }
        }
    }

    Component.onCompleted: {
        // Load the plugin specified by the command line
        if (Qt.application.arguments.length >= 2) {
            var plugin = pluginManager.getByName(Qt.application.arguments[1]);
            if (plugin) {
                prefletTitle.text = plugin.title;
                root.width = plugin.item.width;
                root.height = plugin.item.height;
                pageStack.push(plugin.item);
            }
        }
    }
}
