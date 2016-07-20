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
import QtQuick.Controls.Material 2.0
import Fluid.Controls 1.0
import Hawaii.SystemSettings 1.0
import Hawaii.SystemSettings.Display 1.0 as CppDisplay

PrefletPage {
    property int minimumWidth: 40
    property int minimumHeight: 40

    id: root

    CppDisplay.OutputsModel {
        id: outputsModel
    }

    ListView {
        id: listView
        anchors.fill: parent
        anchors.margins: Units.largeSpacing
        model: outputsModel
        delegate: ItemDelegate {
            id: control
            text: number + " - " + name
            width: ListView.view.width
            onClicked: detailsDialog.open()

            Popup {
                id: detailsDialog
                parent: root
                closePolicy: Popup.OnEscape | Popup.OnPressOutside
                modal: true
                x: (root.width - detailsDialog.width) / 2
                y: (root.height - detailsDialog.height) / 2
                width: detailsLayout.implicitWidth + (2 * detailsLayout.spacing)
                height: detailsLayout.implicitHeight + (2 * detailsLayout.spacing)

                ColumnLayout {
                    id: detailsLayout
                    spacing: Units.smallSpacing

                    OutputPreview {
                        outputId: number
                        width: Units.gu(20)
                        height: width / aspectRatio

                        Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
                    }

                    Row {
                        spacing: 0

                        ToolButton {
                            id: transform90Button
                            indicator: Icon {
                                anchors.centerIn: parent
                                name: "image/rotate-left"
                                width: Units.iconSizes.smallMedium
                                height: width
                                color: diagonalSizeLabel.color
                            }
                            //tooltip: qsTr("Rotate counterclockwise by 90\xc2\xb0")
                            checkable: true
                            checked: model.transform === CppDisplay.OutputsModel.Transform90
                            autoExclusive: true
                        }

                        ToolButton {
                            id: transform180Button
                            indicator: Icon {
                                anchors.centerIn: parent
                                name: "image/flip"
                                width: Units.iconSizes.smallMedium
                                height: width
                                color: diagonalSizeLabel.color
                            }
                            //tooltip: qsTr("Rotate by 180\xc2\xb0")
                            checkable: true
                            checked: model.transform === CppDisplay.OutputsModel.Transform180
                            autoExclusive: true
                        }

                        ToolButton {
                            id: transform270Button
                            indicator: Icon {
                                anchors.centerIn: parent
                                name: "image/rotate-right"
                                width: Units.iconSizes.smallMedium
                                height: width
                                color: diagonalSizeLabel.color
                            }
                            //tooltip: qsTr("Rotate clockwise by 90\xc2\xb0")
                            checkable: true
                            checked: model.transform === CppDisplay.OutputsModel.Transform270
                            autoExclusive: true
                        }

                        Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
                    }

                    GridLayout {
                        rows: 3
                        columns: 2
                        rowSpacing: Units.smallSpacing
                        columnSpacing: Units.smallSpacing

                        Label {
                            text: qsTr("Size:")
                            visible: diagonalSizeLabel.visible
                            opacity: 0.8
                            horizontalAlignment: Qt.AlignRight

                            Layout.minimumWidth: Units.gu(6)
                        }

                        Label {
                            id: diagonalSizeLabel
                            text: diagonalSize
                            visible: text != ""
                        }

                        Label {
                            text: qsTr("Aspect Ratio:")
                            visible: aspectRatioLabel.visible
                            opacity: 0.8
                            horizontalAlignment: Qt.AlignRight

                            Layout.minimumWidth: Units.gu(6)
                        }

                        Label {
                            id: aspectRatioLabel
                            text: aspectRatioString
                            visible: text != ""
                        }

                        Label {
                            text: qsTr("Resolution:")
                            opacity: 0.8
                            horizontalAlignment: Qt.AlignRight

                            Layout.minimumWidth: Units.gu(6)
                        }

                        ComboBox {
                            id: modesCombo
                            model: modes
                            textRole: "name"
                            currentIndex: model.currentMode

                            Layout.minimumWidth: Units.gu(12)
                        }

                        Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
                    }

                    Row {
                        spacing: Units.smallSpacing

                        Button {
                            text: qsTr("Cancel")
                            onClicked: detailsDialog.close()
                        }

                        Button {
                            text: qsTr("Apply")
                            highlighted: true
                            enabled: outputsModel.configurationEnabled
                            onClicked: {
                                var newTransform = CppDisplay.OutputsModel.TransformNormal;
                                if (transform90Button.checked)
                                    newTransform = CppDisplay.OutputsModel.Transform90;
                                else if (transform180Button.checked)
                                    newTransform = CppDisplay.OutputsModel.Transform180;
                                else if (transform270Button.checked)
                                    newTransform = CppDisplay.OutputsModel.Transform270;
                                outputsModel.applyConfiguration(number, modesCombo.currentIndex, newTransform);
                            }
                        }

                        Layout.alignment: Qt.AlignRight
                    }
                }
            }
        }

        ScrollIndicator.vertical: ScrollIndicator {}
    }
}
