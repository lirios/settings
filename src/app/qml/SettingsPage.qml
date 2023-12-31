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
import Liri.Settings

ModulePage {
    id: page

    title: qsTr("Settings")

    ScrollView {
        anchors.fill: parent
        clip: true

        Column {
            ModuleContainer {
                title: qsTr("Personal")
                width: page.width

                Repeater {
                    model: ModulesProxyModel {
                        sourceModel: modulesModel
                        category: Module.PersonalCategory
                    }
                    delegate: SettingsListItem {}
                }
            }

            ModuleContainer {
                title: qsTr("Hardware")
                width: page.width

                Repeater {
                    model: ModulesProxyModel {
                        sourceModel: modulesModel
                        category: Module.HardwareCategory
                    }
                    delegate: SettingsListItem {}
                }
            }

            ModuleContainer {
                title: qsTr("System")
                width: page.width

                Repeater {
                    model: ModulesProxyModel {
                        sourceModel: modulesModel
                        category: Module.SystemCategory
                    }
                    delegate: SettingsListItem {}
                }
            }
        }
    }
}
