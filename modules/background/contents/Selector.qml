/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2015 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2
import Hawaii.Themes 1.0 as Themes
import org.hawaiios.settings 0.2 as Settings

Button {
    readonly property real aspectRatio: Screen.width / Screen.height
    property string type: "background"
    readonly property var settingsObject: {
        if (type == "background")
            return backgroundSettings;
        else if (type == "lockscreen")
            return lockScreenSettings;
        return null;
    }

    style: ButtonStyle {
        label: Item {
            id: wrapper
            implicitWidth: implicitHeight * aspectRatio
            implicitHeight: loader.height + label.paintedHeight +
                            Themes.Units.smallSpacing * 2

            Loader {
                id: loader
                anchors {
                    top: parent.top
                    horizontalCenter: parent.horizontalCenter
                    leftMargin: Themes.Units.smallSpacing
                    topMargin: Themes.Units.smallSpacing
                    rightMargin: Themes.Units.smallSpacing
                }
                asynchronous: true
                width: height * aspectRatio
                height: Themes.Units.dp(50)
                sourceComponent: {
                    switch (settingsObject.mode) {
                    case "solid":
                        return solid;
                    case "hgradient":
                    case "vgradient":
                        return gradient;
                    case "wallpaper":
                        return wallpaper;
                    default:
                        break;
                    }

                    return null;
                }
            }

            Text {
                id: label
                anchors {
                    top: loader.bottom
                    horizontalCenter: parent.horizontalCenter
                    topMargin: Themes.Units.smallSpacing
                    bottomMargin: Themes.Units.smallSpacing
                }
                renderType: Text.NativeRendering
                text: control.text
            }
        }
    }
    onClicked: {
        selectorDialog.select();
        dialog.open();
    }

    Settings.Settings {
        id: backgroundSettings
        schema.id: "org.hawaiios.desktop.background"
        schema.path: "/org/hawaiios/desktop/background/"
    }

    Settings.Settings {
        id: lockScreenSettings
        schema.id: "org.hawaiios.desktop.lockscreen"
        schema.path: "/org/hawaiios/desktop/lockscreen/"
    }

    Dialog {
        id: dialog
        title: qsTr("Pick a background")
        modality: Qt.ApplicationModal
        contentItem: Rectangle {
            color: palette.window

            SystemPalette {
                id: palette
            }

            ColumnLayout {
                anchors {
                    fill: parent
                    margins: Themes.Units.largeSpacing
                }
                spacing: Themes.Units.smallSpacing

                SelectorDialog {
                    id: selectorDialog
                    settings: settingsObject

                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }

                RowLayout {
                    spacing: Themes.Units.smallSpacing

                    Button {
                        text: qsTr("Cancel")
                        onClicked: dialog.close()
                    }

                    Button {
                        text: qsTr("Select")
                        onClicked: {
                            selectorDialog.saveSettings();
                            dialog.close();
                        }
                    }

                    Layout.alignment: Qt.AlignRight
                }
            }
        }
        width: Themes.Units.dp(800)
        height: Themes.Units.dp(450)
    }

    Component {
        id: solid

        Rectangle {
            color: settingsObject.primaryColor
        }
    }

    Component {
        id: gradient

        Rectangle {
            property bool vertical: settingsObject.mode === "vgradient"

            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: settingsObject.primaryColor
                }
                GradientStop {
                    position: 1
                    color: settingsObject.secondaryColor
                }
            }
            rotation: vertical ? 270 : 0
            scale: vertical ? 0.5 : 1
        }
    }

    Component {
        id: wallpaper

        Image {
            source: settingsObject.pictureUrl
            sourceSize.width: width
            sourceSize.height: height
            fillMode: mapFillModeToImage()

            function mapFillModeToImage() {
                switch (settingsObject.fillMode) {
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

