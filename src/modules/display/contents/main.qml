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
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import Fluid.Controls
import Liri.Settings
import Liri.Settings.Display as CppDisplay

ModulePage {
    id: page

    CppDisplay.OutputsModel {
        id: outputsModel
    }

    ModuleContainer {
        title: qsTr("Screens")
        width: page.width

        Repeater {
            model: outputsModel

            ListItem {
                DetailsDialog {
                    id: detailsDialog
                }

                text: name
                onClicked: {
                    detailsDialog.number = number;
                    detailsDialog.modes = modes;
                    detailsDialog.currentMode = currentMode;
                    detailsDialog.diagonalSize = diagonalSize;
                    detailsDialog.aspectRatio = aspectRatio;
                    detailsDialog.aspectRatioString = aspectRatioString;
                    detailsDialog.open();
                }
            }
        }
    }
}
