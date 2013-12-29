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
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.0
import Hawaii.SystemPreferences.Background 0.1

Item {
    id: root

    property int columns: 3
    property int cellPadding: 10
    property real aspectRatio: Screen.width / Screen.height

    signal itemSelected()

    SystemPalette {
        id: palette
    }

    BackgroundSettings {
        id: settings
        //onTypeChanged: loadSettings()
        //onWallpaperUrlChanged: loadSettings()
    }

    ColumnLayout {
        anchors {
            fill: parent
            margins: 11
        }

        ScrollView {
            GridView {
                id: gridView
                model: WallpapersModel {}
                cellWidth: parent.width / columns
                cellHeight: cellWidth / aspectRatio
                currentIndex: -1
                highlightMoveDuration: 0
                delegate: Item {
                    width: gridView.cellWidth
                    height: gridView.cellHeight

                    Image {
                        anchors {
                            fill: parent
                            margins: cellPadding
                        }
                        source: model.fileName ? "file://" + model.fileName : ""
                        sourceSize.width: width
                        sourceSize.height: height
                        width: parent.width - cellPadding * 2
                        height: parent.height - cellPadding * 2
                        fillMode: Image.PreserveAspectCrop
                        asynchronous: true

                        BusyIndicator {
                            anchors.centerIn: parent
                            running: parent.status == Image.Loading
                        }

                        Rectangle {
                            id: infoOverlay
                            anchors.fill: parent
                            color: "#b3000000"
                            visible: false

                            Label {
                                anchors.fill: parent
                                color: "white"
                                verticalAlignment: Qt.AlignBottom
                                wrapMode:  Text.Wrap
                                font.bold: true
                                text: model.name
                            }
                        }

                        MouseArea {
                            id: mouse
                            anchors.fill: parent
                            hoverEnabled: model.hasMetadata
                            onEntered: infoOverlay.visible = model.hasMetadata
                            onExited: infoOverlay.visible = false
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

            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        GridLayout {
            columns: 2

            Label {
                text: qsTr("Fill Mode:")
                horizontalAlignment: Qt.AlignRight
            }

            ComboBox {
                model: [ qsTr("Stretched"), qsTr("Scaled"), qsTr("Cropped"),
                    qsTr("Centered"), qsTr("Tiled") ]
                currentIndex: settings.fillMode
                onCurrentIndexChanged: settings.fillMode = currentIndex
            }

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
        }
    }

    function resetSelection() {
        gridView.currentIndex = -1;
    }

    function loadSettings() {
        if (settings.type == BackgroundSettings.WallpaperBackground) {
            for (var i = 0; i < gridView.count; i++) {
                var url = "file://" + gridView.model.get(i).fileName;
                if (url === settings.wallpaperUrl.toString()) {
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

        settings.wallpaperUrl = "file://" + gridView.model.get(gridView.currentIndex).fileName;
        settings.type = BackgroundSettings.WallpaperBackground;
    }
}
