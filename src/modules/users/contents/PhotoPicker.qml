/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2018 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

import QtQuick
import QtQuick.Controls
import Qt.labs.platform as LabsPlatform
import Fluid.Controls as FluidControls

Item {
    id: photoPicker

    property alias source: image.source

    signal fileSelected(string fileName)

    width: FluidControls.Units.iconSizes.large
    height: width

    Image {
        id: image
        anchors.fill: parent
        visible: status == Image.Ready
    }

    FluidControls.Icon {
        anchors.fill: parent
        source: FluidControls.Utils.iconUrl("action/account_circle")
        size: parent.width
        visible: !image.visible
    }

    MouseArea {
        anchors.fill: parent
        onClicked: menu.open()
    }

    LabsPlatform.FileDialog {
        id: fileDialog
        folder: LabsPlatform.StandardPaths.writableLocation(LabsPlatform.StandardPaths.PicturesLocation)
        nameFilters: ["Pictures (*.png *.jpg *.gif)"]
        onFileChanged: {
            image.source = currentFile;
            photoPicker.fileSelected(currentFile);
        }
    }

    Menu {
        id: menu

        x: image.width
        y: image.height

        MenuItem {
            text: qsTr("Browse...")
            onTriggered: fileDialog.open()
        }
    }
}
