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

    readonly property real aspectRatio: Screen.width / Screen.height
    readonly property real thumbWidth: root.width * 0.5
    readonly property real thumbHeight: thumbWidth / aspectRatio

    BackgroundSettings {
        id: settings
    }

    SelectorDialog {
        id: selectorDialog
        width: root.width
        height: root.height
        visible: false
    }

    Button {
        anchors.centerIn: parent
        width: thumbWidth
        height: thumbHeight
        onClicked: selectorDialog.visible = true

        Item {
            id: container
            anchors {
                left: parent.left
                top: parent.top
                margins: 20
            }
            width: parent.width - 40
            height: parent.height - label.paintedHeight - 40

            Image {
                id: wallpaperPreview
                anchors.fill: parent
                source: settings.wallpaperUrl
                sourceSize.width: width
                sourceSize.height: height
                fillMode: convertFillMode(settings.fillMode)
                clip: wallpaperPreview.fillMode == Image.PreserveAspectCrop
                asynchronous: true
                cache: true
                visible: settings.type == BackgroundSettings.WallpaperBackground
            }

            Rectangle {
                id: colorPreview
                anchors.fill: parent
                color: settings.primaryColor
                visible: settings.type == BackgroundSettings.ColorBackground &&
                         settings.colorShading == BackgroundSettings.SolidColorShading
            }

            Item {
                id: gradientPreview
                anchors.fill: parent
                visible: settings.type == BackgroundSettings.ColorBackground &&
                         settings.colorShading != BackgroundSettings.SolidColorShading
            }

            BusyIndicator {
                anchors.centerIn: parent
                running: wallpaperPreview.visible && wallpaperPreview.status == Image.Loading
            }
        }

        Text {
            id: label
            anchors {
                top: container.bottom
                horizontalCenter: container.horizontalCenter
                margins: 10
            }

            text: qsTr("Background")
        }
    }

    function convertFillMode(value) {
        switch (value) {
        case BackgroundSettings.Scaled:
            return Image.PreserveAspectFit;
        case BackgroundSettings.Cropped:
            return Image.PreserveAspectCrop;
        case BackgroundSettings.Centered:
            return Image.Pad;
        case BackgroundSettings.Tiled:
            return Image.Tile;
        default:
            return Image.Stretch;
        }
    }
}
