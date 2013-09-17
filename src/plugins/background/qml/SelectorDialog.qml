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
import QtQuick.Window 2.1
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

Window {
    id: selectorDialog
    title: qsTr("Select a background")
    flags: Qt.Dialog
    modality: Qt.ApplicationModal
    width: 640
    height: 480
    color: palette.window
    onVisibleChanged: {
        if (visible) {
            selector.selectDefaultTab();
            selector.loadSettings();
        }
    }

    property var palette: SystemPalette {}

    ColumnLayout {
        anchors {
            fill: parent
            margins: 11
        }

        Selector {
            id: selector
            focus: true

            Keys.onReleased: {
                if (event.key === Qt.Key_Escape)
                    cancelButton.clicked();
            }

            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        RowLayout {
            Item {
                Layout.fillWidth: true
            }

            Button {
                id: cancelButton
                text: qsTr("Cancel")
                onClicked: selectorDialog.visible = false
            }

            Button {
                id: selectButton
                text: qsTr("Select")
                isDefault: true
                onClicked: {
                    selector.saveSettings();
                    selectorDialog.visible = false;
                }
            }
        }
    }
}
