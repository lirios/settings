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
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import Fluid.Ui 1.0 as FluidUi
import Hawaii.SystemPreferences 1.0
import org.hawaiios.systempreferences.display 1.0 as CppDisplay

PrefletPage {
    id: root

    property int minimumWidth: FluidUi.Units.dp(800)
    property int minimumHeight: FluidUi.Units.dp(600)

    CppDisplay.OutputsModel {
        id: outputsModel
    }

    SystemPalette {
        id: syspal
        colorGroup: SystemPalette.Active
    }

    Component {
        id: outputDelegate

        MouseArea {
            readonly property int outputId: number
            readonly property string outputDiagonalSize: diagonalSize
            readonly property real outputAspectRatio: aspectRatio
            readonly property string outputAspectRatioString: aspectRatioString
            readonly property var outputModes: modes

            width: listView.width
            height: row.implicitHeight + (FluidUi.Units.largeSpacing * 2)
            onClicked: listView.currentIndex = index

            Rectangle {
                anchors {
                    fill: parent
                    margins: FluidUi.Units.smallSpacing
                }
                color: listView.currentIndex === index ? syspal.highlight : syspal.base

                Row {
                    id: row
                    anchors {
                        fill: parent
                        margins: FluidUi.Units.smallSpacing
                    }
                    spacing: FluidUi.Units.smallSpacing

                    OutputPreview {
                        outputId: number
                        width: FluidUi.Units.dp(50)
                        height: width / aspectRatio
                    }

                    Column {
                        spacing: FluidUi.Units.smallSpacing

                        Label {
                            text: vendor
                            font.bold: true
                            color: listView.currentIndex === index ? syspal.highlightedText : syspal.text
                            wrapMode: Text.WrapAnywhere
                        }

                        Label {
                            text: model
                            font.bold: true
                            color: listView.currentIndex === index ? syspal.highlightedText : syspal.text
                            wrapMode: Text.WrapAnywhere
                        }

                        Label {
                            text: {
                                if (!connected)
                                    return qsTranslate("Output type label", "Disconnected");
                                if (primary)
                                    return qsTranslate("Output type label", "Primary");
                                return qsTranslate("Output type label", "Secondary");
                            }
                            color: listView.currentIndex === index ? syspal.highlightedText : syspal.text
                        }
                    }
                }
            }
        }
    }

    Component {
        id: panelComponent

        ColumnLayout {
            spacing: FluidUi.Units.smallSpacing

            OutputPreview {
                outputId: listView.currentItem.outputId
                width: FluidUi.Units.gu(20)
                height: width / listView.currentItem.outputAspectRatio

                Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            }

            Row {
                spacing: 0

                ToolButton {
                    //onClicked:
                }

                ToolButton {
                    //onClicked:
                }

                ToolButton {
                    //onClicked:
                }

                Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            }

            GridLayout {
                rows: 3
                columns: 2

                Label {
                    text: qsTr("Size")
                    visible: diagonalSizeLabel.visible
                    opacity: 0.8

                    Layout.alignment: Qt.AlignRight
                }

                Label {
                    id: diagonalSizeLabel
                    text: listView.currentItem.outputDiagonalSize
                    visible: text != ""
                }

                Label {
                    text: qsTr("Aspect Ratio")
                    visible: aspectRatioLabel.visible
                    opacity: 0.8

                    Layout.alignment: Qt.AlignRight
                }

                Label {
                    id: aspectRatioLabel
                    text: listView.currentItem.outputAspectRatioString
                    visible: text != ""
                }

                Label {
                    text: qsTr("Resolution")
                    opacity: 0.8

                    Layout.alignment: Qt.AlignRight
                }

                ComboBox {
                    model: listView.currentItem.outputModes
                    textRole: "name"

                    Layout.preferredWidth: FluidUi.Units.dp(150)
                }

                Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            }

            Item {
                Layout.fillHeight: true
            }

            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    ColumnLayout {
        id: leftColumn
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
            margins: FluidUi.Units.largeSpacing
        }
        spacing: FluidUi.Units.smallSpacing
        width: FluidUi.Units.gu(20)

        TableView {
            id: listView
            model: outputsModel

            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        /*
        ListView {
            id: listView
            model: outputsModel
            currentIndex: -1
            delegate: outputDelegate
            onCurrentIndexChanged: panelLoader.sourceComponent = panelComponent

            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        */

        Button {
            text: qsTr("Arrange Combined Displays")
        }
    }

    Loader {
        id: panelLoader
        anchors {
            left: leftColumn.right
            top: leftColumn.top
            right: parent.right
            bottom: parent.bottom
            margins: FluidUi.Units.largeSpacing
        }
    }
}
