/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2016 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

import QtQuick 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import Fluid.Controls 1.0
import Liri.Settings 1.0

FluidWindow {
    id: window

    property real itemSize: Units.iconSizes.large

    title: qsTr("Settings")
    width: minimumWidth
    height: minimumHeight
    minimumWidth: 800
    minimumHeight: 600
    maximumWidth: minimumWidth
    maximumHeight: minimumHeight
    visible: true

    Material.accent: Material.Blue
    Material.primary: Material.color(Material.BlueGrey, Material.theme === Material.Light
                                     ? Material.Shade700 : Material.Shade800)



    initialPage: SettingsPage {
        id: settingsPage
        model: PluginsModel {}
    }

    Component.onCompleted: {
        // Load the plugin specified by the command line
        if (Qt.application.arguments.length >= 2) {
            var plugin = initialPage.model.getByName(Qt.application.arguments[1]);
            if (plugin) {
                settingsPage.moduleLoader.sourceComponent = Qt.createComponent(plugin.mainScriptUrl);
                //prefletTitle.text = plugin.title;
                //window.width = plugin.item.width;
                //window.height = plugin.item.height;
            }
        }
    }
}
