/****************************************************************************
 * This file is part of Hawaii Shell.
 *
 * Copyright (C) 2013-2015 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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
import QtQuick.Window 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.0
import Hawaii.Themes 1.0 as Themes
import org.hawaii.systempreferences.background 1.0

Item {
    property var settings: null
    property int columns: 3
    property int cellPadding: Themes.Units.smallSpacing
    property real aspectRatio: Screen.width / Screen.height

    // Cached settings
    property url pictureUrl
    property string fillMode

    id: root

    SystemPalette {
        id: palette
    }

    ColumnLayout {
        anchors.fill: parent

        ScrollView {
            GridView {
                id: gridView
                model: BackgroundsModel {
                    id: backgroundsModel
                }
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
                        cache: false

                        BusyIndicator {
                            anchors.centerIn: parent
                            running: parent.status == Image.Loading
                        }

                        MouseArea {
                            id: mouse
                            anchors.fill: parent
                            onClicked: {
                                gridView.currentIndex = index;
                                pictureUrl = "file://" + backgroundsModel.get(index);
                            }
                        }
                    }
                }
                highlight: Rectangle {
                    radius: Themes.Units.dp(4)
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
                model: [
                    qsTr("Stretched"),
                    qsTr("Scaled"),
                    qsTr("Cropped"),
                    qsTr("Tiled"),
                    qsTr("Tiled Vertically"),
                    qsTr("Tiled Horizontally"),
                    qsTr("Centered")
                ]
                currentIndex: mapFillModeToIndex(fillMode)
                onActivated: fillMode = mapIndexToFillMode(index)

                Layout.minimumWidth: Themes.Units.gu(10)
            }

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
        }
    }

    function mapFillModeToIndex(fillMode) {
        switch (fillMode) {
        case "preserve-aspect-fit":
            return 1;
        case "preserve-aspect-crop":
            return 2;
        case "tile":
            return 3;
        case "tile-vertically":
            return 4;
        case "tile-horizontally":
            return 5;
        case "pad":
            return 6;
        default:
            break;
        }

        return 0;
    }

    function mapIndexToFillMode(index) {
        switch (index) {
        case 1:
            return "preserve-aspect-fit";
        case 2:
            return "preserve-aspect-crop";
        case 3:
            return "tile";
        case 4:
            return "tile-vertically";
        case 5:
            return "tile-horizontally";
        case 6:
            return "pad";
        default:
            break;
        }

        return "stretch";
    }

    function loadSetting() {
        // Load settings
        pictureUrl = settings.pictureUrl;
        fillMode = settings.fillMode;
        for (var i = 0; i < gridView.count; i++) {
            var url = "file://" + gridView.model.get(i);
            if (url === pictureUrl.toString()) {
                gridView.currentIndex = i;
                return;
            }
        }
        gridView.currentIndex = -1;
    }

    function saveSettings() {
        settings.pictureUrl = pictureUrl;
        settings.fillMode = fillMode;
        settings.mode = "wallpaper";
    }

    Component.onCompleted: {
        // Load backgrounds
        backgroundsModel.addStandardPaths();
        //backgroundsModel.addUserPaths();
    }
}
