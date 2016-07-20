/*
 * System Settings - Settings app for Papyros
 * Copyright (C) 2015 Michael Spencer <sonrisesoftware@gmail.com>
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

Item {
    property int developerClickCount: 0
    readonly property int developerTotalClicks: 7
    readonly property int developerClickRemaining: developerTotalClicks - developerClickCount

    Column {
        id: column
        anchors.centerIn: parent
        anchors.verticalCenterOffset: Units.dp(-40)
        spacing: Units.dp(8)

        Image {
            anchors.horizontalCenter: parent.horizontalCenter
            width: Units.dp(128)
            height: width

            source: Qt.resolvedUrl("papyros-icon.png")

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (developerSettings.developerMode == "true")
                        return

                    developerClickCount++

                    print(developerClickCount, developerClickRemaining)

                    if (developerClickRemaining == 0) {
                        snackbar.open("You are now a developer!")
                        developerSettings.developerMode = "true"
                    } else if (developerClickRemaining <= 3) {
                        snackbar.open(("You are now %1 steps from becoming a " +
                                      "developer").arg(developerClickRemaining))
                    }
                }
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            Label {
                font.pixelSize: Units.dp(40)
                font.weight: Font.Light
                text: "Papyr"
            }

            Label {
                font.pixelSize: Units.dp(40)
                text: "os"
            }
        }

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: Units.dp(20)
            text: "Version 0.1.0"
        }
    }

    Item {
        anchors {
            left: parent.left
            right: parent.right
            top: column.bottom
            bottom: parent.bottom
        }

        Row {
            anchors.centerIn: parent
            spacing: Units.dp(16)

            Button {
                text: "Website"
                textColor: Palette.colors["blue"]["400"]
                onClicked: Qt.openUrlExternally("http://papyros.io")
            }

            Button {
                text: "Report a bug"
                textColor: Palette.colors["red"]["400"]
                onClicked: Qt.openUrlExternally("https://github.com/papyros/papyros/issues")
            }

            Button {
                text: "Credits"
                textColor: Palette.colors["green"]["400"]
            }
        }
    }

    Snackbar {
        id: snackbar
    }
}
