/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2015-2016 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

import QtQuick 2.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import Fluid.Ui 1.0 as FluidUi

ColumnLayout {
    readonly property real aspectRatio: Screen.width / Screen.height
    property string type: "background"
    property alias text: label.text
    property var settingsObject

    MouseArea {
        anchors.fill: parent
        onClicked: {
            selectorDialog.select();
            dialog.open();
        }
    }

    Connections {
        target: settingsObject
        onModeChanged: setLoaderComponent()
    }

    Loader {
        id: loader

        Layout.alignment: Qt.AlignHCenter
        Layout.preferredWidth: Layout.preferredHeight * aspectRatio
        Layout.preferredHeight: FluidUi.Units.dp(50)
    }

    Label {
        id: label
    }

    Rectangle {
        height: FluidUi.Units.dp(1)
        color: Material.dividerColor

        Layout.fillWidth: true
    }

    Dialog {
        id: dialog
        title: qsTr("Pick a background")
        modality: Qt.ApplicationModal
        contentItem: Page {
            header: ToolBar {
                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: parent.leftPadding
                    anchors.topMargin: parent.topPadding
                    anchors.rightMargin: parent.rightPadding
                    anchors.bottomMargin: parent.bottomPadding

                    Button {
                        text: qsTr("Cancel")
                        onClicked: dialog.close()
                    }

                    Item {
                        Layout.fillWidth: true
                    }

                    Button {
                        text: qsTr("Select")
                        onClicked: {
                            selectorDialog.saveSettings();
                            dialog.close();
                        }
                    }
                }
            }

            SelectorDialog {
                id: selectorDialog
                anchors.fill: parent
                settings: settingsObject
            }
        }
        width: FluidUi.Units.dp(800)
        height: FluidUi.Units.dp(450)
    }

    Component {
        id: solid

        Rectangle {
            color: settingsObject.primaryColor
            width: height * aspectRatio
            height: FluidUi.Units.dp(50)
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
            width: height * aspectRatio
            height: FluidUi.Units.dp(50)
        }
    }

    Component {
        id: wallpaper

        Image {
            source: settingsObject.pictureUrl
            sourceSize.width: width
            sourceSize.height: height
            fillMode: mapFillModeToImage()
            width: height * aspectRatio
            height: FluidUi.Units.dp(50)

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

    function setLoaderComponent() {
        switch (settingsObject.mode) {
        case "solid":
            loader.sourceComponent = solid;
            break;
        case "hgradient":
        case "vgradient":
            loader.sourceComponent = gradient;
            break;
        case "wallpaper":
            loader.sourceComponent = wallpaper;
            break;
        default:
            break;
        }
    }

    Component.onCompleted: setLoaderComponent()
}

