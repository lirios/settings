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
import Fluid.Controls as FluidControls
import Liri.Settings.Keyboard

Dialog {
    id: addDialog

    parent: ApplicationWindow.contentItem
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    focus: true
    modal: true
    standardButtons: Dialog.Ok | Dialog.Cancel

    onAccepted: {
        var layout = keyboardData.layouts[layoutComboBox.currentIndex];
        var variant = layout.variants[variantComboBox.currentIndex];

        var layouts = keyboardSettings.layouts;
        layouts.push(layout.name);
        keyboardSettings.layouts = layouts;

        var variants = keyboardSettings.variants;
        variants.push(variant ? variant.name : "");
        keyboardSettings.variants = variants;

        layoutModel.appendLayout(layout.name, variant.name);
    }
    onRejected: addDialog.close()

    KeyboardData {
        id: keyboardData
    }

    ColumnLayout {
        id: mainLayout
        spacing: FluidControls.Units.largeSpacing

        GridLayout {
            rows: 2
            columns: 2

            Label {
                text: qsTr("Layout:")

                Layout.alignment: Qt.AlignRight
            }

            ComboBox {
                id: layoutComboBox
                model: keyboardData.layouts
                textRole: "description"
                onCurrentIndexChanged: {
                    variantComboBox.model = keyboardData.layouts[currentIndex].variants;
                }

                Layout.minimumWidth: FluidControls.Units.gu(15)
                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Variant:")

                Layout.alignment: Qt.AlignRight
            }

            ComboBox {
                id: variantComboBox
                textRole: "description"

                Layout.minimumWidth: FluidControls.Units.gu(15)
                Layout.fillWidth: true
            }
        }
    }
}
