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
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.1
import QtQuick.Controls.Material 2.1
import Fluid.Controls 1.0
import Liri.Settings 1.0
import Liri.Settings.Display 1.0 as CppDisplay

PrefletPage {
    CppDisplay.OutputsModel {
        id: outputsModel
    }

    DetailsDialog {
        id: detailsDialog
    }

    ModuleContainer {
        title: qsTr("Screens")

        Repeater {
            model: outputsModel

            ListItem {
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
