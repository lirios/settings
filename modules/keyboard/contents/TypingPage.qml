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
import Vibe.Settings 1.0
import Fluid.Controls 1.0

ColumnLayout {
    spacing: Units.smallSpacing

    Settings {
        id: keyboardSettings
        schema.id: "io.liri.desktop.peripherals.keyboard"
        schema.path: "/io/liri/desktop/peripherals/keyboard/"
    }

    Settings {
        id: uiSettings
        schema.id: "io.liri.desktop.interface"
        schema.path: "/io/liri/desktop/interface/"
    }

    GroupBox {
        id: repeatKeysGroup
        label: CheckBox {
            text: qsTr("Repeat Keys")
            onCheckedChanged: keyboardSettings.repeat = checked
        }

        GridLayout {
            rows: 2
            columns: 4

            /*
             * Delay
             */

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
                stepSize: 1
                from: 0
                to: 1000
                onValueChanged: keyboardSettings.repeatInterval = to - value

                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Long")
                scale: 0.82999999999999996
            }

            /*
             * Speed
             */

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
                stepSize: 1
                from: 0
                to: 1000
                onValueChanged: keyboardSettings.delay = to - value

                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Fast")
                scale: 0.82999999999999996
            }
        }

        Layout.fillWidth: true
    }

    GroupBox {
        id: cursorBlinkingGroup
        label: CheckBox {
            text: qsTr("Cursor Blinking")
            onCheckedChanged: uiSettings.cursorBlink = checked
        }

        GridLayout {
            rows: 2
            columns: 4

            /*
             * Blink Time
             */

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
                stepSize: 1
                from: 100
                to: 2500
                onValueChanged: uiSettings.cursorBlinkTime = to - value

                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Fast")
                scale: 0.82999999999999996
            }

            /*
             * Blink Timeout
             */

            Label {
                text: qsTr("Timeout:")

                Layout.alignment: Qt.AlignRight
            }

            Label {
                text: qsTr("Slow")
                scale: 0.82999999999999996
            }

            Slider {
                id: cursorFlashTimeoutSlider
                stepSize: 1
                from: 1
                to: 2147483647
                onValueChanged: uiSettings.cursorBlinkTimeout = to - value

                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Fast")
                scale: 0.82999999999999996
            }
        }

        Layout.fillWidth: true
    }

    GroupBox {
        id: inputSourcesGroup
        title: qsTr("Input Sources")

        RowLayout {
            spacing: Units.smallSpacing

            Switch {
                id: virtualKeyboardSwitch
                onCheckedChanged: uiSettings.inputMethod = checked ? "qtvirtualkeyboard" : ""
            }

            Label {
                text: qsTr("Virtual Keyboard")
            }
        }

        Layout.fillWidth: true
    }

    Item {
        Layout.fillHeight: true
    }

    Component.onCompleted: {
        repeatKeysGroup.label.checked = keyboardSettings.repeat;
        cursorBlinkingGroup.label.checked = uiSettings.cursorBlink;
        inputIntervalSlider.value = inputIntervalSlider.to - keyboardSettings.repeatInterval;
        autoRepeatRateSlider.value = autoRepeatRateSlider.to - keyboardSettings.delay;
        cursorFlashTimeSlider.value = cursorFlashTimeSlider.to - uiSettings.cursorBlinkTime;
        virtualKeyboardSwitch.checked = uiSettings.inputMethod == "qtvirtualkeyboard"
    }
}
