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

Item {
    property int columns: 3
    property int cellPadding: 10
    property real aspectRatio: 1.6

    SystemPalette {
        id: palette
    }

    ScrollView {
        anchors {
            fill: parent
            margins: 11
        }

        GridView {
            id: gridView
            model: ColorsModel {}
            cellWidth: parent.width / columns
            cellHeight: cellWidth / aspectRatio
            delegate: Item {
                width: gridView.cellWidth
                height: gridView.cellHeight

                Rectangle {
                    anchors {
                        fill: parent
                        margins: cellPadding
                    }
                    color: model.color

                    MouseArea {
                        anchors.fill: parent
                        onClicked: gridView.currentIndex = index
                    }
                }
            }
            highlight: Rectangle {
                radius: 4
                color: palette.highlight
            }
        }
    }
}
