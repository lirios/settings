/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2016 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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
import QtQuick.Dialogs 1.1
import QtQuick.Controls 2.0

Button {
    id: button

    property alias color: dialog.color

    contentItem: Rectangle {
        anchors {
            fill: parent
            leftMargin: button.leftPadding
            topMargin: button.topPadding
            rightMargin: button.rightPadding
            bottomMargin: button.bottomPadding
        }
        color: button.color
    }
    onClicked: dialog.visible = true

    ColorDialog {
        id: dialog
        modality: Qt.WindowModal
        title: qsTr("Choose a color")
        showAlphaChannel: false
    }
}
