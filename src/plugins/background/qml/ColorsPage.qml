/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2013 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
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
import QtQuick.Window 2.1
import QtQuick.Controls 1.0
import Hawaii.SystemPreferences.Background 0.1

Item {
    id: root

    property int columns: 4
    property int cellPadding: 10
    property real aspectRatio: Screen.width / Screen.height

    signal itemSelected()

    SystemPalette {
        id: palette
    }

    BackgroundSettings {
        id: settings
        //onTypeChanged: loadSettings()
        //onColorShadingChanged: loadSettings()
        //onPrimaryColorChanged: loadSettings()
    }

    ScrollView {
        anchors {
            fill: parent
            margins: 11
        }

        GridView {
            id: gridView
            model: ColorsModel {}
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
                        margins: cellPadding
                    }
                    color: model.color

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            gridView.currentIndex = index;
                            root.itemSelected();
                        }
                    }
                }
            }
            highlight: Rectangle {
                radius: 4
                color: palette.highlight
            }
        }
    }

    function resetSelection() {
        gridView.currentIndex = -1;
    }

    function loadSettings() {
        if (settings.type == BackgroundSettings.ColorBackground &&
                settings.colorShading == BackgroundSettings.SolidColorShading) {
            for (var i = 0; i < gridView.count; i++) {
                var color = gridView.model.get(i).color;
                if (color == settings.primaryColor) {
                    gridView.currentIndex = i;
                    return;
                }
            }
        }

        gridView.currentIndex = -1;
    }

    function saveSettings() {
        if (gridView.currentIndex == -1)
            return;

        settings.primaryColor = gridView.model.get(gridView.currentIndex).color;
        settings.colorShading = BackgroundSettings.SolidColorShading;
        settings.type = BackgroundSettings.ColorBackground;
    }
}
