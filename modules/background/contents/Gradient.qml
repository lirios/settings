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
    id: root
    width: Themes.Units.dp(640)
    height: Themes.Units.dp(480)

    Settings.ConfigGroup {
        id: bgConfig
        file: "hawaii/shellrc"
        group: "Background"

        function loadSettings() {
            bgSettings.primaryColor = bgConfig.readEntry("PrimaryColor");
            bgSettings.secondaryColor = bgConfig.readEntry("SecondaryColor");
        }

        function saveSettings() {
            bgConfig.writeEntry("Mode", bgSettings.vertical ? "vgradient" : "hgradient");
            bgConfig.writeEntry("PrimaryColor", bgSettings.primaryColor);
            bgConfig.writeEntry("SecondaryColor", bgSettings.secondaryColor);
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
            onActivated: {
                bgSettings.vertical = index == 1
                bgConfig.saveSettings();
            }

            Layout.minimumWidth: Themes.Units.gu(10)
        }

        ColorButton {
            id: colorButton1
            color: bgSettings.primaryColor
            onColorChanged: {
                bgSettings.primaryColor = color;
                bgConfig.saveSettings();
            }
        }

        ColorButton {
            id: colorButton2
            color: bgSettings.secondaryColor
            onColorChanged: {
                bgSettings.secondaryColor = color;
                bgConfig.saveSettings();
            }
        }
    }

    Component.onCompleted: {
        // Load settings
        bgConfig.loadSettings();
    }
}
