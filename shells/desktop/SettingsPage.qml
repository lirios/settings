/****************************************************************************
 * This file is part of Hawaii.
 *
 * Copyright (C) 2016 Michael Spencer
 *
 * Author(s):
 *    Michael Spencer <sonrisesoftware@gmail.com>
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

import QtQuick 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import Fluid.UI 1.0
import Fluid.Controls 1.0
import Hawaii.Settings 1.0

Page {
    id: settingsPage

    title: qsTr("Settings")

    Material.background: "#f3f3f3"

    property var selectedModule

    Pane {
        id: listPane

        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
        }

        Material.background: "white"
        Material.elevation: 1

        width: 200
        padding: 0

        ListView {
            anchors.fill: parent

            model: PluginsModel {}

            section.property: "category"
            section.delegate: Subheader {
                id: subheader
                text: section

                ThinDivider {
                    anchors.top: parent.top
                    visible: subheader.y > 0
                }
            }

            delegate: SettingsListItem {}

            ScrollBar.vertical: ScrollBar {}
        }

        z: 2
    }

    Item {
        id: moduleView

        anchors {
            left: listPane.right
            top: parent.top
            bottom: parent.bottom
            right: parent.right
        }

        Loader {
            id: moduleLoader
            anchors.fill: parent
            source: selectedModule ? selectedModule.mainScriptUrl : ""
        }

        WelcomeView {
            anchors.fill: parent
            visible: moduleLoader.status == Loader.Null
        }

        ErrorView {
            id: errorView
            anchors.fill: parent
            visible: moduleLoader.status == Loader.Error
            moduleTitle: selectedModule ? selectedModule.title : ""
            errorMessage: moduleLoader.sourceComponent ? moduleLoader.sourceComponent.errorString() : ""
        }
    }
}
