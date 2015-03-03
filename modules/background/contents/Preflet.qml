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
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.0

Item {
    id: root

    property int minimumWidth: 800
    property int minimumHeight: 600

    ListModel {
        id: bgTypes

        ListElement { label: qsTr("Wallpaper"); url: "Wallpaper.qml" }
        ListElement { label: qsTr("Solid"); url: "Solid.qml" }
        ListElement { label: qsTr("Gradient"); url: "Gradient.qml" }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 11

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
                onActivated: loader.source = model.url

                Layout.minimumWidth: 120
            }

            Layout.fillWidth: true
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
        }

        Loader {
            id: loader
            asynchronous: true

            BusyIndicator {
                anchors.centerIn: parent
                visible: parent.status != Loader.Ready
            }

            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    Component.onCompleted: {
        comboBox.currentIndex = 0;
        loader.source = "Wallpaper.qml";
    }
}
