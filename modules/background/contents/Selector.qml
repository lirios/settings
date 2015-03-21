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
import org.hawaii.settings 0.1 as Settings

Button {
    readonly property real aspectRatio: Screen.width / Screen.height
    property alias type: bgConfig.group

    style: ButtonStyle {
        label: Item {
            id: wrapper
            implicitWidth: implicitHeight * aspectRatio
            implicitHeight: Themes.Units.dp(200)

            Column {
                anchors {
                    centerIn: parent
                    margins: Themes.Units.largeSpacing
                }
                spacing: Themes.Units.largeSpacing

                Loader {
                    id: loader
                    asynchronous: true
                    width: height * aspectRatio
                    height: wrapper.implicitHeight - label.paintedHeight - (2 * Themes.Units.largeSpacing)
                    sourceComponent: {
                        switch (bgSettings.mode) {
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
                    anchors.horizontalCenter: parent.horizontalCenter
                    renderType: Text.NativeRendering
                    text: control.text
                }
            }
        }
    }
    onClicked: dialog.open()

    Settings.ConfigGroup {
        id: bgConfig
        file: "hawaii/shellrc"
        group: "Background"
        onGroupChanged: loadSettings()
        onConfigChanged: loadSettings()

        function loadSettings() {
            bgSettings.mode = bgConfig.readEntry("Mode");
            bgSettings.primaryColor = bgConfig.readEntry("PrimaryColor", Qt.rgba(0, 0, 0, 0));
            bgSettings.secondaryColor = bgConfig.readEntry("SecondaryColor", Qt.rgba(0, 0, 0, 0));
            bgSettings.pictureUrl = bgConfig.readEntry("PictureUrl");
            bgSettings.fillMode = bgConfig.readEntry("FillMode", Image.Stretch);
        }
    }

    QtObject {
        id: bgSettings

        property string mode
        property color primaryColor
        property color secondaryColor
        property url pictureUrl
        property int fillMode
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
                    type: bgConfig.group
                    mode: bgSettings.mode

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
            color: bgSettings.primaryColor
        }
    }

    Component {
        id: gradient

        Rectangle {
            property bool vertical: bgSettings.mode == "vgradient"

            gradient: Gradient {
                GradientStop {
                    position: 0
                    color: bgSettings.primaryColor
                }
                GradientStop {
                    position: 1
                    color: bgSettings.secondaryColor
                }
            }
            rotation: vertical ? 270 : 0
            scale: vertical ? 0.5 : 1
        }
    }

    Component {
        id: wallpaper

        Image {
            source: bgSettings.pictureUrl
            sourceSize.width: width
            sourceSize.height: height
            fillMode: bgSettings.fillMode
        }
    }

    Component.onCompleted: bgConfig.loadSettings()
}

