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

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import Fluid.Controls as FluidControls
import Liri.Settings.Background

Item {
    property var settings: null

    // Cached settings
    property color primaryColor

    ScrollView {
        id: scrollView

        anchors.fill: parent
        clip: true

        GridView {
            id: gridView

            readonly property real aspectRatio: 4 / 3
            readonly property real gutters: 4
            readonly property var breakpoints: [480, 600, 1024]
            readonly property int columns: {
                var n = 2;
                for (var i = 0; i < breakpoints.length; i++) {
                    if (parent.width >= breakpoints[i])
                        n++;
                }
                return n;
            }

            model: ColorsModel {
                id: colorsModel
            }
            cellWidth: Math.floor(parent.width / columns)
            cellHeight: Math.round(cellWidth / aspectRatio)
            delegate: Item {
                width: gridView.cellWidth
                height: gridView.cellHeight

                Rectangle {
                    anchors.centerIn: parent
                    width: parent.width - gridView.gutters
                    height: parent.height - gridView.gutters
                    color: model.color

                    MouseArea {
                        id: mouse
                        anchors.fill: parent
                        onClicked: {
                            gridView.currentIndex = index;
                            primaryColor = colorsModel.get(index);
                            saveSettings();
                        }
                    }
                }

                Rectangle {
                    anchors.centerIn: parent
                    width: 48
                    height: width
                    radius: width
                    color: Material.accent
                    visible: gridView.currentIndex === index && settings.mode === "solid"

                    FluidControls.Icon {
                        anchors.centerIn: parent
                        source: FluidControls.Utils.iconUrl("navigation/check")
                        size: 32
                        color: Material.foreground

                        Material.theme: FluidControls.Color.isDarkColor(parent.color) ? Material.Dark : Material.Light
                    }
                }
            }
        }
    }

    function loadSettings() {
        primaryColor = settings.primaryColor;
        var i, color;
        for (i = 0; i < gridView.count; i++) {
            color = gridView.model.get(i);
            if (primaryColor === color) {
                gridView.currentIndex = i;
                return;
            }
        }
        gridView.currentIndex = -1;
    }

    function saveSettings() {
        settings.primaryColor = primaryColor;
        settings.mode = "solid";
    }

    Component.onCompleted: {
        // Load settings
        loadSettings();
    }
}
