/****************************************************************************
 * This file is part of Hawaii.
 *
 * Copyright (C) 2013-2016 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Private 1.0
import QtQuick.Layouts 1.0

GroupBoxStyle {
    property string iconName
    readonly property int iconSize: 22

    padding {
        top: (control.title.length > 0 || control.checkable ? 16 : 0) + 20
        left: 16
    }

    panel: Item {
        anchors.fill: parent

        RowLayout {
            Image {
                source: "image://desktoptheme/" + iconName
                sourceSize.width: width
                sourceSize.height: height
                width: iconSize
                height: iconSize
            }

            Label {
                text: control.title
                font.bold: true
            }
        }
    }
}
