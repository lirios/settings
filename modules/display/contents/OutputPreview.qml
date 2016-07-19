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

import QtQuick 2.0
import QtQuick.Controls 2.0
import Fluid.UI 1.0 as FluidUi
import Hawaii.Themes 1.0 as Themes

Rectangle {
    property int outputId

    color: "grey"

    Rectangle {
        anchors {
            left: parent.left
            top: parent.top
            margins: FluidUi.Units.smallSpacing
        }
        color: "black"
        radius: FluidUi.Units.dp(6)
        width: label.paintedWidth + FluidUi.Units.largeSpacing
        height: width

        Label {
            id: label
            anchors {
                centerIn: parent
                margins: FluidUi.Units.smallSpacing
            }
            font.pointSize: Themes.Theme.defaultFont.pointSize * 0.8
            color: "white"
            text: outputId
        }
    }
}

