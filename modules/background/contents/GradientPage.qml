/****************************************************************************
 * This file is part of Hawaii Shell.
 *
 * Copyright (C) 2013-2016 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:GPL2+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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

import QtQuick 2.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.0
import Fluid.Ui 1.0 as FluidUi

Item {
    property var settings: null

    // Cached settings
    property bool vertical
    property color primaryColor
    property color secondaryColor

    id: root

    RowLayout {
        anchors.centerIn: parent

        ComboBox {
            model: [
                qsTr("Horizontal"),
                qsTr("Vertical")
            ]
            currentIndex: vertical ? 1 : 0
            onActivated: vertical = index == 1

            Layout.minimumWidth: FluidUi.Units.gu(10)
        }

        ColorButton {
            id: colorButton1
            color: primaryColor
            onColorChanged: primaryColor = color
        }

        ColorButton {
            id: colorButton2
            color: secondaryColor
            onColorChanged: secondaryColor = color
        }
    }

    function loadSettings() {
        // Load settings
        vertical = settings.mode === "vgradient";
        primaryColor = settings.primaryColor;
        secondaryColor = settings.secondaryColor;
    }

    function saveSettings() {
        settings.primaryColor = primaryColor;
        settings.secondaryColor = secondaryColor;
        settings.mode = vertical ? "vgradient" : "hgradient";
    }
}
