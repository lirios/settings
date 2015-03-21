/****************************************************************************
 * This file is part of Hawaii Shell.
 *
 * Copyright (C) 2013-2015 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
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
import Hawaii.Themes 1.0 as Themes
import org.hawaii.settings 0.1 as Settings

Item {
    property alias type: bgConfig.group

    id: root

    Settings.ConfigGroup {
        id: bgConfig
        file: "hawaii/shellrc"

        function loadSettings() {
            bgSettings.vertical = bgConfig.readEntry("Mode") === "vgradient";
            bgSettings.primaryColor = bgConfig.readEntry("PrimaryColor", Qt.rgba(0, 0, 0, 0));
            bgSettings.secondaryColor = bgConfig.readEntry("SecondaryColor", Qt.rgba(0, 0, 0, 0));
        }
    }

    QtObject {
        id: bgSettings

        property bool vertical
        property color primaryColor
        property color secondaryColor
    }

    RowLayout {
        anchors.centerIn: parent

        ComboBox {
            model: [
                qsTr("Horizontal"),
                qsTr("Vertical")
            ]
            currentIndex: bgSettings.vertical ? 1 : 0
            onActivated: bgSettings.vertical = index == 1

            Layout.minimumWidth: Themes.Units.gu(10)
        }

        ColorButton {
            id: colorButton1
            color: bgSettings.primaryColor
            onColorChanged: bgSettings.primaryColor = color
        }

        ColorButton {
            id: colorButton2
            color: bgSettings.secondaryColor
            onColorChanged: bgSettings.secondaryColor = color
        }
    }

    function saveSettings() {
        bgConfig.writeEntry("Mode", bgSettings.vertical ? "vgradient" : "hgradient");
        bgConfig.writeEntry("PrimaryColor", bgSettings.primaryColor);
        bgConfig.writeEntry("SecondaryColor", bgSettings.secondaryColor);
    }

    Component.onCompleted: {
        // Load settings
        bgConfig.loadSettings();
    }
}
