/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2013-2016 Pier Luigi Fiorini
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
import QtQuick.Controls.Material 2.0
import Fluid.Controls 1.0
import Hawaii.SystemSettings 1.0
import Hawaii.Settings 1.0

PrefletPage {
    centered: true

    Settings {
        id: backgroundSettings
        schema.id: "org.hawaiios.desktop.background"
        schema.path: "/org/hawaiios/desktop/background/"
    }

    Settings {
        id: lockScreenSettings
        schema.id: "org.hawaiios.desktop.lockscreen"
        schema.path: "/org/hawaiios/desktop/lockscreen/"
    }

    ModuleContainer {
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
