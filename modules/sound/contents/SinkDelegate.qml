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

import QtQuick 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import Fluid.Core 1.0 as FluidCore
import Fluid.Controls 1.0 as FluidControls
import Vibe.PulseAudio 1.0 as PA

Item {
    width: 400
    height: layout.implicitHeight + FluidControls.Units.smallSpacing * 2

    Component.onCompleted: {
        console.debug("Sink: ", JSON.stringify(Properties));
    }

    RowLayout {
        id: layout

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: FluidControls.Units.smallSpacing * 2
        width: parent.width
        spacing: FluidControls.Units.smallSpacing * 2

        ColumnLayout {
            spacing: FluidControls.Units.smallSpacing * 2

            RadioButton {
                text: Properties["device.product.name"] || Description
                checkable: false
                checked: Default
                onClicked: Default = true
            }

            VolumeSlider {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            Repeater {
                model: FluidCore.SortFilterProxyModel {
                    sourceModel: cardModel
                    filterExpression: index === CardIndex
                }
                delegate: ComboBox {
                    model: Profiles
                    textRole: "description"
                    currentIndex: ActiveProfileIndex
                    onActivated: {
                        ActiveProfileIndex = index;
                    }

                    Layout.fillWidth: true
                }
            }
        }
    }
}
