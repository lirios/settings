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
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

Item {
    property int columns: 3
    property int cellPadding: 10
    property real aspectRatio: 1.6

    SystemPalette {
        id: palette
    }

    ColumnLayout {
        anchors {
            fill: parent
            margins: 11
        }

        ColumnLayout {
            GroupBox {
                title: qsTr("First color")

                ScrollView {
                    anchors.fill: parent

                    GridView {
                        id: gridView1
                        model: ColorsModel {}
                        cellWidth: parent.width / columns
                        cellHeight: cellWidth / aspectRatio
                        delegate: Item {
                            width: gridView1.cellWidth
                            height: gridView2.cellHeight

                            Rectangle {
                                anchors {
                                    fill: parent
                                    margins: cellPadding
                                }
                                color: model.color

                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: gridView1.currentIndex = index
                                }
                            }
                        }
                        highlight: Rectangle {
                            radius: 4
                            color: palette.highlight
                        }
                    }
                }

                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            GroupBox {
                title: qsTr("Second color")

                ScrollView {
                    anchors.fill: parent

                    GridView {
                        id: gridView2
                        model: ColorsModel {}
                        cellWidth: parent.width / columns
                        cellHeight: cellWidth / aspectRatio
                        delegate: Item {
                            width: gridView2.cellWidth
                            height: gridView2.cellHeight

                            Rectangle {
                                anchors {
                                    fill: parent
                                    margins: cellPadding
                                }
                                color: model.color

                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: gridView2.currentIndex = index
                                }
                            }
                        }
                        highlight: Rectangle {
                            radius: 4
                            color: palette.highlight
                        }
                    }
                }

                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }

        ListModel {
            id: gradientMenu

            ListElement { text: "Horizontal" }
            ListElement { text: "Vertical" }
        }

        RowLayout {
            Label {
                text: qsTr("Gradient Type:")
            }

            ComboBox {
                model: gradientMenu
            }
        }
    }
}
