/****************************************************************************
 * This file is part of Hawaii.
 *
 * Copyright (C) 2016 Pier Luigi Fiorini
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
    ModuleContainer {
        title: qsTr("General")

        ListItem {
            text: qsTr("Primary Button")
            subText: qsTr("Sets the order of physical buttons on mice and touchpads")
            rightItem: Row {
                Button {
                    text: qsTr("Left")
                }
                Button {
                    text: qsTr("Right")
                }
            }
        }
    }

    ModuleContainer {
        title: qsTr("Mouse")
    }

    ModuleContainer {
        title: qsTr("Touchpad")
    }
}
