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

import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import Fluid.Core 1.0 as FluidCore
import Fluid.Controls 1.0 as FluidControls
import Liri.Settings 1.0

FluidControls.ApplicationWindow {
    id: window

    readonly property bool wideAspectRatio: width >= height

    title: qsTr("Settings")
    width: 800
    height: 600
    visibility: FluidCore.Device.isMobile ? Window.Maximized : Window.Windowed
    visible: true

    Material.accent: Material.Blue
    Material.primary: Material.color(Material.BlueGrey, Material.theme === Material.Light
                                     ? Material.Shade700 : Material.Shade800)

    initialPage: SettingsPage {}

    ModulesModel {
        id: modulesModel
    }

    Component {
        id: errorPageComponent

        ErrorPage {}
    }

    function loadModule(module) {
        var component = Qt.createComponent(module.mainScriptUrl);

        if (component.status === Component.Ready)
            window.pageStack.push(component, { title: module.title });
        else
            window.pageStack.push(errorPageComponent, { title: module.title, message: component.errorString()});
    }

    function loadModuleByName(moduleName) {
        var module = modulesModel.getByName(moduleName);
        if (module)
            loadModule(module);
    }
}
