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
import Fluid.Ui 1.0 as FluidUi
import Hawaii.SystemPreferences 1.0
import Hawaii.GSettings 1.0 as Settings

PrefletPage {
    property int minimumHeight: FluidUi.Units.dp(440)

    Settings.Settings {
        id: backgroundSettings
        schema.id: "org.hawaiios.desktop.background"
        schema.path: "/org/hawaiios/desktop/background/"
    }

    Settings.Settings {
        id: lockScreenSettings
        schema.id: "org.hawaiios.desktop.lockscreen"
        schema.path: "/org/hawaiios/desktop/lockscreen/"
    }

    Row {
        anchors {
            centerIn: parent
            margins: FluidUi.Units.largeSpacing
        }
        spacing: FluidUi.Units.largeSpacing

        Selector {
            settingsObject: backgroundSettings
            text: qsTr("Background")
        }

        Selector {
            settingsObject: lockScreenSettings
            text: qsTr("Lock Screen")
        }
    }
}
