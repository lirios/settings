/****************************************************************************
 * This file is part of Settings.
 *
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

import QtQuick 2.2
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import Fluid.Controls 1.0 as FluidControls
import Liri.Settings 1.0

FluidControls.Page {
    id: settingsPage

    title: qsTr("Settings")

    Material.background: "#f3f3f3"

    property alias model: listView.model
    property alias moduleLoader: moduleLoader
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
            id: listView
            anchors.fill: parent

            section.property: "category"
            section.delegate: FluidControls.Subheader {
                id: subheader
                text: section

                FluidControls.ThinDivider {
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

        FluidControls.Placeholder {
            anchors.fill: parent

            iconName: "action/settings"
            text: qsTr("Welcome to Settings")
            subText: qsTr("Select an item from the list to see the available options.")
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
