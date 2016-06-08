/****************************************************************************
 * This file is part of Hawaii Shell.
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

import QtQuick 2.1
import QtQuick.Window 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import Fluid.Ui 1.0 as FluidUi
import org.hawaiios.systempreferences.background 1.0

Item {
    property var settings: null
    property int columns: 4
    property real aspectRatio: Screen.width / Screen.height

    // Cached settings
    property color primaryColor

    GridView {
        id: gridView
        anchors.fill: parent
        model: ColorsModel {}
        clip: true
        cellWidth: parent.width / columns
        cellHeight: cellWidth / aspectRatio
        currentIndex: -1
        highlightMoveDuration: 0
        delegate: Item {
            width: gridView.cellWidth
            height: gridView.cellHeight

            Rectangle {
                anchors {
                    fill: parent
                    margins: FluidUi.Units.smallSpacing
                }
                color: model.color

                MouseArea {
                    id: mouse
                    anchors.fill: parent
                    onClicked: {
                        gridView.currentIndex = index;
                        primaryColor = parent.color;
                    }
                }
            }
        }
        highlight: Rectangle {
            radius: FluidUi.Units.dp(4)
            color: Material.accentColor
        }

        Layout.fillWidth: true
        Layout.fillHeight: true
        ScrollBar.vertical: ScrollBar {}
    }

    function loadSettings() {
        // Load settings
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
}
