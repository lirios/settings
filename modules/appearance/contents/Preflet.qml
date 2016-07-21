/*
 * System Settings - Settings app for Papyros
 * Copyright (C) 2015-2016 Michael Spencer <sonrisesoftware@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
import QtQuick 2.4
import Material 0.2
import Material.ListItems 0.1 as ListItem
import Papyros.Desktop 0.1
import io.papyros.settings 0.1

ModuleView {

    ListItem.Subheader {
        text: "Desktop"
        textColor: Theme.accentColor
    }

    ListItem.Standard {
        text: "Transparent app shelf"

        onClicked: appShelfSwitch.checked = !appShelfSwitch.checked

        secondaryItem: Switch {
            id: appShelfSwitch
            anchors.centerIn: parent

            checked: ShellSettings.appShelf.transparentShelf
            onCheckedChanged: {
                ShellSettings.appShelf.transparentShelf = checked
                checked = Qt.binding(function() {
                    return ShellSettings.appShelf.transparentShelf
                })
            }
        }
    }

    ListItem.Standard {
        text: "Accent color"
        tintColor: "transparent"
        showDivider: true

        onClicked: colorPicker.open()

        secondaryItem: Rectangle {
            anchors.centerIn: parent

            radius: Units.dp(2)
            width: Units.dp(24)
            height: width
            color: Palette.colors[ShellSettings.desktop.accentColor]['500']
            border.color: Palette.colors[ShellSettings.desktop.accentColor]['700']
        }
    }

    ListItem.Subheader {
        text: "Lockscreen"
        textColor: Theme.accentColor
    }

    ListItem.Standard {
        text: "Nothing here yet"
        showDivider: true
        itemLabel.opacity: 0.5
        interactive: false
    }

    ListItem.Subheader {
        text: "Screen saver"
        textColor: Theme.accentColor
    }

    ListItem.Standard {
        text: "Nothing here yet"
        itemLabel.opacity: 0.5
        interactive: false
    }

    Dialog {
        id: colorPicker
        title: "Accent Color"

        property var selectedColor: ShellSettings.desktop.accentColor

        positiveButton.visible: false

        Grid {
            columns: 7
            spacing: Units.dp(8)

            Repeater {
                model: [
                    "red", "pink", "purple", "deepPurple", "indigo",
                    "blue", "lightBlue", "cyan", "teal", "green",
                    "lightGreen", "lime", "yellow", "amber", "orange",
                    "deepOrange", "grey", "blueGrey", "brown", "black",
                    "white"
                ]

                View {
                    width: Units.dp(30)
                    height: width
                    radius: Units.dp(2)
                    backgroundColor: Palette.colors[modelData]["500"]
                    border.color: Palette.colors[modelData]["700"]
                            ? Palette.colors[modelData]["700"] : "#ddd"

                    tintColor: ink.containsMouse ? border.color
                                                 : "transparent"

                    Ink {
                        id: ink
                        anchors.fill: parent

                        onClicked: {
                            ShellSettings.desktop.accentColor = modelData
                            colorPicker.close()
                        }
                    }
                }
            }
        }
    }
}
