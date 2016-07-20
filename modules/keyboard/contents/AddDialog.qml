/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2015-2016 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import Fluid.Controls 1.0
import Hawaii.SystemSettings.Keyboard 1.0

Popup {
    id: addDialog
    x: (parent.width - implicitWidth) / 2
    y: (parent.height - implicitHeight) / 2
    focus: true
    modal: true
    closePolicy: Popup.OnEscape | Popup.OnPressOutside
    implicitWidth: mainLayout.implicitWidth +
                   addDialog.leftPadding + addDialog.rightPadding +
                   addDialog.leftMargin + addDialog.rightMargin
    implicitHeight: mainLayout.implicitHeight +
                    addDialog.topPadding + addDialog.bottomPadding +
                    addDialog.topMargin + addDialog.bottomMargin

    KeyboardData {
        id: keyboardData
    }

    ColumnLayout {
        id: mainLayout
        spacing: Units.largeSpacing

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

                Layout.minimumWidth: Units.gu(15)
                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Variant:")

                Layout.alignment: Qt.AlignRight
            }

            ComboBox {
                id: variantComboBox
                textRole: "description"

                Layout.minimumWidth: Units.gu(15)
                Layout.fillWidth: true
            }
        }

        RowLayout {
            spacing: Units.largeSpacing

            Item {
                Layout.fillWidth: true
            }

            Button {
                text: qsTr("Cancel")
                onClicked: addDialog.close()
            }

            Button {
                text: qsTr("OK")
                onClicked: {
                    var layout = keyboardData.layouts[layoutComboBox.currentIndex];
                    var variant = layout.variants[variantComboBox.currentIndex];

                    var layouts = keyboardSettings.layouts;
                    layouts.push(layout.name);
                    keyboardSettings.layouts = layouts;

                    var variants = keyboardSettings.variants;
                    variants.push(variant ? variant.name : "");
                    keyboardSettings.variants = variants;

                    layoutModel.appendLayout(layout.name, variant.name);

                    addDialog.close();
                }
            }
        }
    }
}
