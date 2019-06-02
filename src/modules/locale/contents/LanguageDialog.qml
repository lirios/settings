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
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.2
import Fluid.Controls 1.0 as FluidControls
import Liri.Settings.Locale 1.0

Dialog {
    id: langDialog

    property string selectedCode: ""

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    width: parent.width * 0.8
    height: parent.height * 0.8

    title: qsTr("Language")

    modal: true

    leftPadding: 0
    rightPadding: 0

    standardButtons: Dialog.Ok | Dialog.Cancel

    onOpened: {
        langDialog.selectedCode = localeSettings.language;
        searchField.forceActiveFocus();
    }

    onAccepted: {
        localeSettings.language = langDialog.selectedCode;
    }

    ButtonGroup {
        id: buttonGroup
    }

    ColumnLayout {
        anchors.fill: parent

        Pane {
            TextField {
                id: searchField
                placeholderText: qsTr("Search a language")
                width: parent.width
                focus: true
            }

            Layout.fillWidth: true
        }

        ScrollView {
            clip: true

            Layout.fillWidth: true
            Layout.fillHeight: true

            ListView {
                id: localeListView
                model: LocaleFilterModel {
                    filter: searchField.text
                }
                currentIndex: -1
                delegate: RegionDelegate {
                    width: localeListView.width
                    language: model.language
                    country: model.country
                    checked: model.code === langDialog.selectedCode
                    onClicked: langDialog.selectedCode = model.code

                    ButtonGroup.group: buttonGroup
                }
            }
        }
    }
}
