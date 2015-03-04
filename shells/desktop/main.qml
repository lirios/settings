/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2013 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
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

import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import org.hawaii.systempreferences 0.1

ApplicationWindow {
    id: root
    title: qsTr("System Preferences")
    width: minimumWidth
    height: minimumHeight
    minimumWidth: defaultMinimumWidth
    minimumHeight: defaultMinimumHeight
    maximumWidth: minimumWidth
    maximumHeight: minimumHeight

    property int defaultMinimumWidth: 480
    property int defaultMinimumHeight: 480
    property int itemSize: 96

    toolBar: ToolBar {
        id: mainToolBar
        width: root.width
        height: Math.max(backButton.height, searchEntry.height) + 10

        RowLayout {
            anchors.fill: parent

            ToolButton {
                id: backButton
                action: actionBack
                visible: pageStack.depth > 1
            }

            Label {
                id: prefletTitle
                font.bold: true
                horizontalAlignment: Qt.AlignHCenter
                visible: pageStack.depth > 1

                Layout.fillWidth: true
                Layout.alignment: Qt.AlignCenter
            }

            TextField {
                id: searchEntry
                placeholderText: qsTr("Keywords")
                //visible: pageStack.depth === 1
                visible: false

                Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            }
        }
    }

    Action {
        id: actionBack
        iconName: "go-previous"
        onTriggered: {
            root.minimumWidth = root.defaultMinimumWidth;
            root.minimumHeight = root.defaultMinimumHeight;
            pageStack.pop();
        }
    }

    PluginManager {
        id: pluginManager
    }

    StackView {
        id: pageStack
        anchors.fill: parent
/*
        delegate: StackViewDelegate {
            function transitionFinished(properties) {
                properties.exitItem.opacity = 1.0;
            }

            property Component pushTransition: StackViewTransition {
                PropertyAnimation { target: enterItem; property: "opacity"; from: 0.0; to: 1.0 }
                PropertyAnimation { target: exitItem; property: "opacity"; from: 1.0; to: 0.0 }
            }
        }
*/
        initialItem: Item {
            width: parent.width
            height: parent.height

            ScrollView {
                anchors.fill: parent

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
                root.width = plugin.item.width;
                root.height = plugin.item.height;
                pageStack.push({item: plugin.item});
            }
        }
    }
}
