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

import QtQuick 2.10
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.3
import QtQuick.Layouts 1.0
import Fluid.Controls 1.0 as FluidControls
import Liri.Settings.Display 1.0 as CppDisplay

Dialog {
    id: detailsDialog

    property int number: 0
    property alias modes: modesCombo.model
    property alias currentMode: modesCombo.currentIndex
    property alias diagonalSize: diagonalSizeLabel.text
    property real aspectRatio: 1.0
    property alias aspectRatioString: aspectRatioLabel.text

    parent: ApplicationWindow.window.contentItem
    modal: true
    x: (parent.width - detailsDialog.width) / 2
    y: (parent.height - detailsDialog.height) / 2
    standardButtons: Dialog.Ok | Dialog.Cancel

    onAccepted: {
        var newTransform = CppDisplay.OutputsModel.TransformNormal;
        if (transform90Button.checked)
            newTransform = CppDisplay.OutputsModel.Transform90;
        else if (transform180Button.checked)
            newTransform = CppDisplay.OutputsModel.Transform180;
        else if (transform270Button.checked)
            newTransform = CppDisplay.OutputsModel.Transform270;
        outputsModel.applyConfiguration(number, modesCombo.currentIndex, newTransform);
        detailsDialog.close();
    }
    onRejected: {
        detailsDialog.close();
    }

    ColumnLayout {
        id: detailsLayout
        spacing: FluidControls.Units.smallSpacing

        OutputPreview {
            outputId: number
            width: 150
            height: width / aspectRatio

            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
        }

        Row {
            spacing: 0

            ToolButton {
                id: transform90Button

                ToolTip.text: qsTr("Rotate counterclockwise by 90\xb0")
                ToolTip.visible: hovered

                icon.source: FluidControls.Utils.iconUrl("image/rotate_left")
                checkable: true
                checked: model.transform === CppDisplay.OutputsModel.Transform90
                autoExclusive: true
            }

            ToolButton {
                id: transform180Button

                ToolTip.text: qsTr("Rotate by 180\xb0")
                ToolTip.visible: hovered

                icon.source: FluidControls.Utils.iconUrl("image/flip")
                checkable: true
                checked: model.transform === CppDisplay.OutputsModel.Transform180
                autoExclusive: true
            }

            ToolButton {
                id: transform270Button

                ToolTip.text: qsTr("Rotate clockwise by 90\xb0")
                ToolTip.visible: hovered

                icon.source: FluidControls.Utils.iconUrl("image/rotate_right")
                checkable: true
                checked: model.transform === CppDisplay.OutputsModel.Transform270
                autoExclusive: true
            }

            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
        }

        GridLayout {
            rows: 3
            columns: 2
            rowSpacing: FluidControls.Units.smallSpacing
            columnSpacing: FluidControls.Units.smallSpacing

            Label {
                text: qsTr("Size:")
                visible: diagonalSizeLabel.visible
                opacity: 0.8
                horizontalAlignment: Qt.AlignRight

                Layout.minimumWidth: FluidControls.Units.gu(6)
            }

            Label {
                id: diagonalSizeLabel
                visible: text != ""
            }

            Label {
                text: qsTr("Aspect Ratio:")
                visible: aspectRatioLabel.visible
                opacity: 0.8
                horizontalAlignment: Qt.AlignRight

                Layout.minimumWidth: FluidControls.Units.gu(6)
            }

            Label {
                id: aspectRatioLabel
                visible: text != ""
            }

            Label {
                text: qsTr("Resolution:")
                opacity: 0.8
                horizontalAlignment: Qt.AlignRight

                Layout.minimumWidth: FluidControls.Units.gu(6)
            }

            ComboBox {
                id: modesCombo
                textRole: "name"

                Layout.minimumWidth: FluidControls.Units.gu(12)
            }

            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
        }
    }
}
