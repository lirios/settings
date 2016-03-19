/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2015-2016 Pier Luigi Fiorini
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

import QtQuick 2.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.0
import Fluid.Ui 1.0 as FluidUi

Item {
    property var settings: null

    id: root

    ListModel {
        id: bgTypes

        ListElement { label: qsTr("Wallpaper"); component: "wallpaper" }
        ListElement { label: qsTr("Solid"); component: "solid" }
        ListElement { label: qsTr("Gradient"); component: "gradient" }
    }

    Component {
        id: wallpaper

        WallpaperPage {
            settings: root.settings
        }
    }

    Component {
        id: solid

        SolidPage {
            settings: root.settings
        }
    }

    Component {
        id: gradient

        GradientPage {
            settings: root.settings
        }
    }

    ColumnLayout {
        anchors {
            fill: parent
            margins: FluidUi.Units.largeSpacing
        }

        GridLayout {
            columns: 2

            Label {
                text: qsTr("Type:")
                horizontalAlignment: Qt.AlignRight
            }

            ComboBox {
                id: comboBox
                model: bgTypes
                textRole: "label"
                onCurrentIndexChanged: {
                    switch (bgTypes.get(currentIndex).component) {
                    case "wallpaper":
                        loader.sourceComponent = wallpaper;
                        break;
                    case "solid":
                        loader.sourceComponent = solid;
                        break;
                    case "gradient":
                        loader.sourceComponent = gradient;
                        break;
                    default:
                        break;
                    }
                }

                Layout.minimumWidth: FluidUi.Units.gu(10)
            }

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
        }

        Loader {
            id: loader
            //asynchronous: true
            onItemChanged: if (item) item.loadSettings()

            BusyIndicator {
                anchors.centerIn: parent
                visible: parent.status != Loader.Ready
            }

            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    function select() {
        switch (settings.mode) {
        case "wallpaper":
            comboBox.currentIndex = 0;
            break;
        case "solid":
            comboBox.currentIndex = 1;
            break;
        case "hgradient":
        case "vgradient":
            comboBox.currentIndex = 2;
            break;
        default:
            break;
        }
    }

    function saveSettings() {
        if (loader.item)
            loader.item.saveSettings();
    }
}

