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
import org.hawaii.settings 0.1 as Settings
import org.hawaii.systempreferences.background 1.0

Item {
    property alias type: bgConfig.group
    property int columns: 3
    property int cellPadding: Themes.Units.smallSpacing
    property real aspectRatio: Screen.width / Screen.height

    id: root

    SystemPalette {
        id: palette
    }

    Settings.ConfigGroup {
        id: bgConfig
        file: "hawaii/shellrc"

        function loadSettings() {
            bgSettings.pictureUrl = bgConfig.readEntry("PictureUrl");
            bgSettings.fillMode = bgConfig.readEntry("FillMode", Image.Stretch);
        }
    }

    QtObject {
        id: bgSettings

        property url pictureUrl
        property int fillMode
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
                                bgSettings.pictureUrl = "file://" + backgroundsModel.get(index);
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
                    qsTr("Centered"),
                    qsTr("Tiled")
                ]
                currentIndex: mapFillModeToIndex(bgSettings.fillMode)
                onActivated: bgSettings.fillMode = mapIndexToFillMode(index)

                Layout.minimumWidth: Themes.Units.gu(10)
            }

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
        }
    }

    function mapFillModeToIndex(fillMode) {
        switch (fillMode) {
        case Image.PreserveAspectFit:
            return 1;
        case Image.PreserveAspectCrop:
            return 2;
        case Image.Pad:
            return 3;
        case Image.Tile:
            return 4;
        default:
            break;
        }

        return 0;
    }

    function mapIndexToFillMode(index) {
        switch (index) {
        case 1:
            return Image.PreserveAspectFit;
        case 2:
            return Image.PreserveAspectCrop;
        case 3:
            return Image.Pad;
        case 4:
            return Image.Tile;
        default:
            break;
        }

        return Image.Stretch;
    }

    function saveSettings() {
        bgConfig.writeEntry("Mode", "wallpaper");
        bgConfig.writeEntry("PictureUrl", bgSettings.pictureUrl);
        bgConfig.writeEntry("FillMode", bgSettings.fillMode);
    }

    Component.onCompleted: {
        // Load backgrounds
        backgroundsModel.addStandardPaths();
        //backgroundsModel.addUserPaths();

        // Load settings
        bgConfig.loadSettings();
        for (var i = 0; i < gridView.count; i++) {
            var url = "file://" + gridView.model.get(i);
            if (url === bgSettings.pictureUrl.toString()) {
                gridView.currentIndex = i;
                return;
            }
        }
        gridView.currentIndex = -1;
    }
}
