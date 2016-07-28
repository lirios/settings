/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2013-2016 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import Hawaii.Settings.Desktop 0.1

Item {
    TabView {
        anchors {
            fill: parent
            margins: 11
        }

        Tab {
            title: qsTr("Launcher")

            LauncherPage {}
        }

        Tab {
            title: qsTr("Hot Corners")

            ColumnLayout {
                Label {
                    text: "Not yet implemented"

                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                }
            }
        }
    }
}
