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
import Hawaii.Configuration 1.0
import Hawaii.Shell.Core 1.0

Item {
    id: root

    property int minimumWidth: 800
    property int minimumHeight: 600

    Configuration {
        id: settings
        category: "shell"

        property string background: "org.hawaii.backgrounds.wallpaper"
    }

    PackagesModel {
        id: packages
        type: PackagesModel.BackgroundPackage

        function findCurrentIndex() {
            for (var i = 0; i < packages.count; i++) {
                if (packages.get(i).identifier == settings.background)
                    return i;
            }

            return -1;
        }

        function setBackgroundType(index) {
            var item = packages.get(index);
            if (!item) {
                console.log("Invalid index " + index);
                return;
            }

            settings.background = item.identifier;
            loader.source = item.filePath("preferencesview");
        }

        Component.onCompleted: {
            for (var i = 0; i < packages.count; i++) {
                var item = packages.get(i);
                if (item.identifier == settings.background) {
                    comboBox.currentIndex = i;
                    loader.source = item.filePath("preferencesview");
                    return;
                }
            }
        }
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
                model: packages
                textRole: "name"
                onActivated: packages.setBackgroundType(index)

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
}
