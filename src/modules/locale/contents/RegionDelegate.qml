/****************************************************************************
 * This file is part of Liri.
 *
 * Copyright (C) 2019 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

ItemDelegate {
    id: control

    property string language: ""
    property string country: ""

    contentItem: Row {
        RadioIndicator {
            anchors.verticalCenter: parent.verticalCenter
            id: radioIndicator
            control: control
        }

        Item {
            width: control.rightPadding
            height: 1
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: model.language
            font: control.font
            width: (parent.width - radioIndicator.width - control.rightPadding) / 2
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: model.country
            font: control.font
            color: Material.secondaryTextColor
            horizontalAlignment: Text.AlignRight
            width: (parent.width - radioIndicator.width - control.rightPadding) / 2
        }
    }
}
