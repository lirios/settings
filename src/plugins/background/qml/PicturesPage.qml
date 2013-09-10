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
import Qt.labs.folderlistmodel 1.0
import Hawaii.SystemPreferences.Background 0.1

Item {
    property string picturesPath
    property int columns: 3
    property int cellPadding: 10
    property real aspectRatio: Screen.width / Screen.height

    SystemPalette {
        id: palette
    }

    BackgroundSettings {
        id: settings
        onTypeChanged: changeWallpaper()
        onWallpaperUrlChanged: changeWallpaper()
    }

    ScrollView {
        anchors {
            fill: parent
            margins: 11
        }

        GridView {
            id: gridView
            model: FolderListModel {
                nameFilters: ["*.png", "*.jpg", "*.svg", "*.svgz"]
                folder: "file://" + picturesPath
                showDirs: false
                showDotAndDotDot: false
                showOnlyReadable: true
                sortField: FolderListModel.Name
            }
            cellWidth: parent.width / columns
            cellHeight: cellWidth / aspectRatio
            cacheBuffer: 80
            delegate: Item {
                width: gridView.cellWidth
                height: gridView.cellHeight

                Image {
                    anchors {
                        fill: parent
                        margins: cellPadding
                    }
                    source: "file://" + model.filePath
                    width: parent.width - cellPadding * 2
                    height: parent.height - cellPadding * 2

                    MouseArea {
                        id: mouse
                        anchors.fill: parent
                        onClicked: {
                            settings.type = BackgroundSettings.WallpaperBackground;
                            settings.wallpaperUrl = "file://" + model.filePath;
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

    function changeWallpaper() {
        if (settings.type == BackgroundSettings.WallpaperBackground) {
            for (var i = 0; i < gridView.count; i++) {
                var url = "file://" + gridView.model.get(i).filePath;
                if (url == settings.wallpaperUrl.toString()) {
                    gridView.currentIndex = i;
                    return;
                }
            }
        }

        gridView.currentIndex = -1;
    }

    Component.onCompleted: changeWallpaper()
}
