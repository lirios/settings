/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2019 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 * Copyright (C) 2016 Michael Spencer <sonrisesoftware@gmail.com>
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
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import Fluid.Controls 1.0 as FluidControls

FluidControls.Page {
    id: settingsPage

    property alias component: moduleLoader.sourceComponent

    Material.background: window.wideAspectRatio ? "#f3f3f3" : "white"

    Loader {
        id: moduleLoader
        anchors.fill: parent
        onLoaded: {
            settingsPage.actions = [];
            if (item.actions !== undefined && item.actions.length > 0)
                settingsPage.actions = item.actions;
        }
    }

    ErrorView {
        id: errorView
        anchors.fill: parent
        visible: moduleLoader.status == Loader.Error
        moduleTitle: settingsPage.title
        errorMessage: moduleLoader.sourceComponent ? moduleLoader.sourceComponent.errorString() : ""
    }
}
