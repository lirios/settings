/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2018 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.2
import Fluid.Controls 1.0 as FluidControls

FluidControls.Page {
    id: page

    default property alias content: layout.data

    property int windowWidth: window.defaultWidth
    property int windowHeight: window.defaultHeight

    property bool needsAuthorization: false
    property bool unlocked: true

    signal unlockRequested()

    actions: [
        FluidControls.Action {
            icon.source: FluidControls.Utils.iconUrl("action/lock_open")
            text: qsTr("Unlock")
            toolTip: qsTr("Dialog is locked, click to unlock")
            visible: needsAuthorization && !unlocked
            onTriggered: page.unlockRequested()
        }
    ]

    ScrollView {
        id: scrollView
        anchors.fill: parent

        ColumnLayout {
            id: layout
            width: page.width
            height: children.height
        }
    }
}
