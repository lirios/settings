/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2016 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 * Copyright (C) 2016 Michael Spencer <sonrisesoftware@gmail.com>
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

import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import Fluid.Controls 1.0
import QtGSettings 1.0
import Liri.Settings 1.0

PrefletPage {
    ModuleContainer {
        title: qsTr("Desktop")

        ListItem {
            text: qsTr("Transparent app shelf")

            onClicked: appShelfSwitch.checked = !appShelfSwitch.checked

            rightItem: Switch {
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

        ListItem {
            text: qsTr("Accent color")
            //tintColor: "transparent"
            showDivider: true

            onClicked: colorPicker.open()

            rightItem: Rectangle {
                anchors.centerIn: parent

                radius: 2
                width: 24
                height: width
                color: Material.color(ShellSettings.desktop.accentColor)
                border.color: Material.color(ShellSettings.desktop.accentColor, Material.Shade700)
            }
        }

        Popup {
            id: colorPicker
            //title: "Accent Color"
            x: (parent.width - width) / 2
            y: (parent.height - height) / 2
            modal: true

            property var selectedColor: ShellSettings.desktop.accentColor

            //positiveButton.visible: false

            Grid {
                columns: 7
                spacing: 8

                Repeater {
                    model: [
                        Material.Red, Material.Pink, Material.Purple, Material.DeepPurple,
                        Material.Indigo, Material.Blue, Material.LightBlue, Material.Cyan,
                        Material.Teal, Material.Green, Material.LightGreen, Material.Lime,
                        Material.Yellow, Material.Amber, Material.Orange, Material.DeepOrange,
                        Material.Grey, Material.BlueGrey, Material.Brown
                    ]

                    Rectangle {
                        width: 30
                        height: width
                        radius: 2
                        color: Material.color(modelData)
                        border.color: Material.color(modelData, Material.Shade700)

                        MouseArea {
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

    ModuleContainer {
        title: "Lockscreen"

        ListItem {
            text: "Nothing here yet"
            showDivider: true
            //itemLabel.opacity: 0.5
            interactive: false
        }
    }

    ModuleContainer {
        title: "Screen saver"

        ListItem {
            text: "Nothing here yet"
            //itemLabel.opacity: 0.5
            interactive: false
        }
    }
}
