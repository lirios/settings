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

import QtQuick
import QtQuick.Controls
import Fluid.Controls

Rectangle {
    property int outputId

    color: "grey"

    Rectangle {
        anchors {
            left: parent.left
            top: parent.top
            margins: Units.smallSpacing
        }
        color: "black"
        radius: 6
        width: label.paintedWidth + Units.largeSpacing
        height: width

        BodyLabel {
            id: label
            anchors {
                centerIn: parent
                margins: Units.smallSpacing
            }
            color: "white"
            text: outputId
        }
    }
}

