/****************************************************************************
 * This file is part of Hawaii.
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

import QtQuick 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import Fluid.Controls 1.0
import Hawaii.SystemSettings 1.0

PrefletPage {
    header: ToolBar {
        height: bar.height

        TabBar {
            id: bar
            width: parent.width

            TabButton {
                text: qsTr("Shortcuts")
            }

            TabButton {
                text: qsTr("Behavior")
            }

            TabButton {
                text: qsTr("Layout")
            }
        }
    }

    StackLayout {
        anchors.fill: parent
        anchors.margins: Units.largeSpacing
        currentIndex: bar.currentIndex

        ColumnLayout {
            Label {
                text: "Not yet implemented"

                Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            }
        }

        TypingPage {}

        LayoutPage {}
    }
}
