/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2013 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
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
import QtQuick.Controls 1.0

Item {
    TabView {
        id: tabView
        anchors.fill: parent

        Tab {
            id: wallpapersTab
            title: qsTr("Wallpapers")
            onActiveChanged: item.loadSettings()

            WallpapersPage {
                onItemSelected: {
                    if (colorsTab.item)
                        colorsTab.item.resetSelection();
                }
            }
        }

        /*
        Tab {
            title: qsTr("Pictures")

            PicturesPage {}
        }
        */

        Tab {
            id: colorsTab
            title: qsTr("Colors")
            onActiveChanged: item.loadSettings()

            ColorsPage {
                onItemSelected: {
                    if (wallpapersTab.item)
                        wallpapersTab.item.resetSelection();
                }
            }
        }

        /*
        Tab {
            title: qsTr("Gradients")

            GradientsPage {}
        }
        */
    }

    function selectDefaultTab() {
        tabView.currentIndex = 0;
    }

    function loadSettings() {
        tabView.getTab(tabView.currentIndex).item.loadSettings();
    }

    function saveSettings() {
        tabView.getTab(tabView.currentIndex).item.saveSettings();
    }
}
