/****************************************************************************
 * This file is part of Hawaii.
 *
 * Copyright (C) 2013-2015 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
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
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.0

ColumnLayout {
/*
    Configuration {
        id: settings
        category: "peripherals/keyboard"

        property bool keyboardRepeatEnabled: true
        property int keyboardInputInterval: 30
        property int keyboardAutoRepeatRate: 500
        property bool cursorFlashEnabled: true
        property int cursorFlashTime: 400

        Component.onCompleted: {
            repeatKeysGroup.checked = settings.keyboardRepeatEnabled;
            inputIntervalSlider.value = inputIntervalSlider.maximumValue - settings.keyboardInputInterval;
            autoRepeatRateSlider.value = autoRepeatRateSlider.maximumValue - settings.keyboardAutoRepeatRate;
            cursorBlinkingGroup.checked = settings.cursorFlashEnabled;
            cursorFlashTimeSlider.value = settings.cursorFlashTime - settings.cursorFlashTime;
        }
    }
*/

    GroupBox {
        id: repeatKeysGroup
        title: qsTr("Repeat Keys")
        checkable: true
        onCheckedChanged: settings.keyboardRepeatEnabled = checked

        GridLayout {
            rows: 2
            columns: 4

            Label {
                text: qsTr("Delay:")

                Layout.alignment: Qt.AlignRight
            }

            Label {
                text: qsTr("Short")
                scale: 0.82999999999999996
            }

            Slider {
                id: inputIntervalSlider
                minimumValue: 0
                maximumValue: 1000
                onValueChanged: settings.keyboardInputInterval = maximumValue - value

                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Long")
                scale: 0.82999999999999996
            }

            Label {
                text: qsTr("Speed:")

                Layout.alignment: Qt.AlignRight
            }

            Label {
                text: qsTr("Slow")
                scale: 0.82999999999999996
            }

            Slider {
                id: autoRepeatRateSlider
                minimumValue: 0
                maximumValue: 1000
                onValueChanged: settings.keyboardAutoRepeatRate = maximumValue - value

                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Fast")
                scale: 0.82999999999999996
            }
        }
    }

    GroupBox {
        id: cursorBlinkingGroup
        title: qsTr("Cursor Blinking")
        checkable: true
        onCheckedChanged: settings.cursorFlashEnabled = checked

        GridLayout {
            rows: 1
            columns: 4

            Label {
                text: qsTr("Speed:")

                Layout.alignment: Qt.AlignRight
            }

            Label {
                text: qsTr("Slow")
                scale: 0.82999999999999996
            }

            Slider {
                id: cursorFlashTimeSlider
                minimumValue: 0
                maximumValue: 1000
                onValueChanged: settings.cursorFlashTime = maximumValue - value

                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Fast")
                scale: 0.82999999999999996
            }
        }
    }

    Item {
        Layout.fillHeight: true
    }
}
