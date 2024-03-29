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
import QtQuick.Controls.Material
import QtQuick.Layouts
import Fluid.Controls as FluidControls
import Liri.Settings
import QtGSettings

ModulePage {
    id: backgroundModulePage

    GSettings {
        id: backgroundSettings
        schema.id: "io.liri.desktop.background"
        schema.path: "/io/liri/desktop/background/"
    }

    GSettings {
        id: lockScreenSettings
        schema.id: "io.liri.desktop.lockscreen"
        schema.path: "/io/liri/desktop/lockscreen/"
    }

    Pane {
        anchors.centerIn: parent

        padding: 0

        Material.elevation: 1

        Row {
            Selector {
                settings: backgroundSettings
                text: qsTr("Background")
            }

            Rectangle {
                height: parent.height
                width: 1
                color: Material.dividerColor
            }

            Selector {
                settings: lockScreenSettings
                text: qsTr("Lock Screen")
            }
        }
    }
}
