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

import QtQuick 2.1
import QtQuick.Layouts 1.0
import Qt.labs.controls 1.0
import Fluid.Ui 1.0 as FluidUi
import Hawaii.GSettings 1.0
import org.hawaiios.systempreferences.keyboard 1.0

ColumnLayout {
    spacing: FluidUi.Units.largeSpacing

    Settings {
        id: keyboardSettings
        schema.id: "org.hawaiios.desktop.peripherals.keyboard"
        schema.path: "/org/hawaiios/desktop/peripherals/keyboard/"
    }

    KeyboardData {
        id: keyboardData
    }

    ListModel {
        id: layoutModel

        function appendLayout(layoutName, variantName) {
            var layoutDescr = keyboardData.layoutDescription(layoutName);
            var variantDescr = keyboardData.variantDescription(layoutName, variantName);
            layoutModel.append({"label": layoutDescr,
                                   "layout": layoutName,
                                   "variant": variantName});
        }

        Component.onCompleted: {
            var i, numLayouts = keyboardSettings.layouts.length;
            for (i = 0; i < numLayouts; i++) {
                var layoutName = keyboardSettings.layouts[i];
                var variantName = keyboardSettings.variants[i];
                appendLayout(layoutName, variantName);
            }
        }
    }

    AddDialog {
        id: addDialog
    }

    ColumnLayout {
        spacing: FluidUi.Units.smallSpacing

        ColumnLayout {
            Frame {
                ListView {
                    id: savedLayouts
                    anchors.fill: parent
                    model: layoutModel
                    clip: true
                    delegate: ItemDelegate {
                        text: model.label
                        width: savedLayouts.width
                    }

                    ScrollBar.vertical: ScrollBar {}
                }

                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            Row {
                ToolButton {
                    //iconName: "list-add-symbolic"
                    width: FluidUi.Units.iconSizes.smallMedium
                    height: width
                    onClicked: addDialog.open()
                }

                ToolButton {
                    //iconName: "list-remove-symbolic"
                    width: FluidUi.Units.iconSizes.smallMedium
                    height: width
                    enabled: savedLayouts.selection.count > 0
                    onClicked: {
                        savedLayouts.selection.forEach(function(rowIndex) {
                            // Remove entry from settings
                            var layouts = keyboardSettings.layouts;
                            layouts.splice(rowIndex, 1);
                            keyboardSettings.layouts = layouts;

                            var variants = keyboardSettings.variants;
                            variants.splice(rowIndex, 1);
                            keyboardSettings.variants = variants;

                            // Remove row from model
                            layoutModel.remove(rowIndex);
                        });
                    }
                }
            }

            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        RowLayout {
            spacing: FluidUi.Units.smallSpacing

            Label {
                text: qsTr("Keyboard model:")
            }

            ComboBox {
                id: modelComboBox
                model: keyboardData.models
                textRole: "description"
                onActivated: keyboardSettings.model = keyboardData.models[index].name

                Layout.fillWidth: true

                Component.onCompleted: {
                    var i, value = keyboardSettings.model;
                    for (i = 0; i < keyboardData.models.length; i++) {
                        if (keyboardData.models[i].name === value) {
                            modelComboBox.currentIndex = i;
                            return;
                        }
                    }

                    // Fallback
                    modelComboBox.currentIndex = 0;
                }
            }
        }

        Pane {
            TextField {
                anchors.fill: parent
                placeholderText: qsTr("Type to test the layout...")
            }

            Layout.fillWidth: true
        }
    }
}
