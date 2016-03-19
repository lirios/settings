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
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.0
import Fluid.Ui 1.0 as FluidUi
import org.hawaiios.settings 0.2
import org.hawaiios.systempreferences.keyboard 1.0

ColumnLayout {
    spacing: FluidUi.Units.smallSpacing

    Settings {
        id: keyboardSettings
        schema.id: "org.hawaiios.desktop.peripherals.keyboard"
        schema.path: "/org/hawaiios/desktop/peripherals/keyboard/"
    }

    KeyboardData {
        id: data
    }

    ListModel {
        id: layoutModel

        function appendLayout(layoutName, variantName) {
            var layoutDescr = data.layoutDescription(layoutName);
            var variantDescr = data.variantDescription(layoutName, variantName);
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

    Dialog {
        id: addDialog
        width: FluidUi.Units.dp(200)
        height: FluidUi.Units.dp(100)
        contentItem: Rectangle {
            color: syspal.window

            SystemPalette {
                id: syspal
            }

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: FluidUi.Units.largeSpacing
                spacing: FluidUi.Units.smallSpacing

                RowLayout {
                    spacing: FluidUi.Units.smallSpacing

                    Label {
                        text: qsTr("Layout:")
                        horizontalAlignment: Qt.AlignRight
                    }

                    ComboBox {
                        id: layoutComboBox
                        model: data.layouts
                        textRole: "description"
                        onCurrentIndexChanged: {
                            variantComboBox.model = data.layouts[currentIndex].variants;
                        }

                        Layout.fillWidth: true
                    }
                }

                RowLayout {
                    spacing: FluidUi.Units.smallSpacing

                    Label {
                        text: qsTr("Variant:")
                        horizontalAlignment: Qt.AlignRight
                    }

                    ComboBox {
                        id: variantComboBox
                        textRole: "description"

                        Layout.fillWidth: true
                    }
                }

                RowLayout {
                    spacing: FluidUi.Units.smallSpacing

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
                            var layout = data.layouts[layoutComboBox.currentIndex];
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
    }

    ColumnLayout {
        spacing: FluidUi.Units.smallSpacing

        ColumnLayout {
            TableView {
                TableViewColumn {
                    role: "label"
                    title: qsTr("Layout")
                }

                id: savedLayouts
                model: layoutModel
                headerVisible: false

                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            Row {
                ToolButton {
                    iconName: "list-add"
                    width: FluidUi.Units.iconSizes.smallMedium
                    height: width
                    onClicked: addDialog.open()
                }

                ToolButton {
                    iconName: "list-remove"
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
                model: data.models
                textRole: "description"
                onActivated: keyboardSettings.model = data.models[index].name

                Layout.fillWidth: true

                Component.onCompleted: {
                    var i, value = keyboardSettings.model;
                    for (i = 0; i < data.models.length; i++) {
                        if (data.models[i].name === value) {
                            modelComboBox.currentIndex = i;
                            return;
                        }
                    }

                    // Fallback
                    modelComboBox.currentIndex = 0;
                }
            }
        }

        TextField {
            placeholderText: qsTr("Type to test the layout...")

            Layout.fillWidth: true
        }
    }
}
