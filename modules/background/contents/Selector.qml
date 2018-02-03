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

import QtQuick 2.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.1
import Fluid.Controls 1.0

Item {
    id: selector

    readonly property real aspectRatio: Screen.width / Screen.height
    property alias text: label.text
    property var settings
    property string type: "background"

    width: column.width + 32
    height: column.height + 32

    Ripple {
        anchors.fill: parent

        onClicked: {
            selectorDialog.select();
            dialog.open();
        }
    }

    ColumnLayout {
        id: column
        anchors.centerIn: parent

        spacing: 16

        Loader {
            id: loader

            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: Layout.preferredHeight * aspectRatio
            Layout.preferredHeight: 100

            sourceComponent: {
                switch (settings.mode) {
                    case "solid":
                        return solidComponent
                    case "hgradient":
                    case "vgradient":
                        return gradientComponent
                    case "wallpaper":
                        return wallpaperComponent
                    default:
                        return null
                }
            }
        }

        SubheadingLabel {
            id: label

            Layout.alignment: Qt.AlignHCenter
        }
    }

    Dialog {
        id: dialog
        parent: ApplicationWindow.window.contentItem
        title: qsTr("Pick a background")
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        width: parent.width - (parent.width * 0.2)
        height: parent.height - (parent.height * 0.2)
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel

        onAccepted: {
            selectorDialog.saveSettings();
            dialog.close();
        }
        onRejected: dialog.close()

        contentItem: SelectorDialog {
            id: selectorDialog
            settings: selector.settings
            width: parent.width
            height: parent.height
        }
    }

    Component {
        id: solidComponent

        Rectangle {
            color: settings.primaryColor
            radius: 2
        }
    }

    Component {
        id: gradientComponent

        Rectangle {
            property bool vertical: settings.mode === "vgradient"

            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: settings.primaryColor
                }
                GradientStop {
                    position: 1
                    color: settings.secondaryColor
                }
            }
            radius: 2
            rotation: vertical ? 270 : 0
            scale: vertical ? 0.5 : 1
        }
    }

    Component {
        id: wallpaperComponent

        Image {
            source: settings.pictureUrl || ""
            sourceSize.width: width * Screen.devicePixelRatio
            sourceSize.height: height * Screen.devicePixelRatio

            fillMode: {
                switch (settings.fillMode) {
                    case "preserve-aspect-fit":
                        return Image.PreserveAspectFit;
                    case "preserve-aspect-crop":
                        return Image.PreserveAspectCrop;
                    case "tile":
                        return Image.Tile;
                    case "tile-vertically":
                        return Image.TileVertically;
                    case "tile-horizontally":
                        return Image.TileHorizontally;
                    case "pad":
                        return Image.Pad;
                    default:
                        break;
                }

                return Image.Stretch;
            }
        }
    }
}
