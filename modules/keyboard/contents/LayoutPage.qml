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

import QtQuick 2.1
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import Fluid.Controls 1.0 as FluidControls
import QtGSettings 1.0
import Liri.Settings 1.0
import Liri.Settings.Keyboard 1.0

PrefletPage {
    GSettings {
        id: keyboardSettings
        schema.id: "io.liri.desktop.peripherals.keyboard"
        schema.path: "/io/liri/desktop/peripherals/keyboard/"
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

    ModuleContainer {
        title: qsTr("Model and Test")

        FluidControls.ListItem {
            text: qsTr("Model")
            rightItem: ComboBox {
                id: modelComboBox
                anchors.centerIn: parent
                model: keyboardData.models
                textRole: "description"
                width: 200
                onActivated: keyboardSettings.model = keyboardData.models[index].name

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

        Control {
            width: parent.width
            height: contentItem.implicitHeight + topPadding + bottomPadding
            padding: FluidControls.Units.smallSpacing * 2

            contentItem: TextField {
                implicitWidth: parent.width
                placeholderText: qsTr("Type to test the layout...")
            }
        }
    }

    ModuleContainer {
        title: qsTr("Layout")

        Repeater {
            model: layoutModel

            FluidControls.ListItem {
                text: model.label
                subText: model.variant || qsTr("No variant")
                rightItem: Button {
                    anchors.centerIn: parent
                    text: qsTr("Remove")
                    flat: true
                    onClicked: {
                        // Remove entry from settings
                        var layouts = keyboardSettings.layouts;
                        layouts.splice(index, 1);
                        keyboardSettings.layouts = layouts;

                        var variants = keyboardSettings.variants;
                        variants.splice(index, 1);
                        keyboardSettings.variants = variants;

                        // Remove row from model
                        layoutModel.remove(index);
                    }
                }
            }
        }

        FluidControls.ListItem {
            icon.name: "content/add"
            text: qsTr("Add layout...")
            onClicked: addDialog.open()
        }
    }
}
