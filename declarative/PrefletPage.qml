/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2016 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import Fluid.Controls 1.0

Page {
    id: page

    default property alias content: column.data

    property bool centered: false

    Flickable {
        id: flickable
        anchors {
            fill: centered ? undefined : parent
            horizontalCenter: centered ? parent.horizontalCenter : undefined
            verticalCenter: centered ? parent.verticalCenter : undefined
            topMargin: centered ? 0 : Units.smallSpacing * 8
            bottomMargin: centered ? 0 : Units.smallSpacing * 8
        }
        contentWidth: parent.width
        contentHeight: column.implicitHeight

        ColumnLayout {
            id: column
            anchors.fill: parent
            spacing: Units.smallSpacing * 2
        }

        ScrollBar.vertical: ScrollBar {}
    }
}
