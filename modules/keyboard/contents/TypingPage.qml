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

import QtQuick 2.1
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import QtGSettings 1.0
import Fluid.Controls 1.0
import Liri.Settings 1.0

ModulePage {
    GSettings {
        id: keyboardSettings
        schema.id: "io.liri.desktop.peripherals.keyboard"
        schema.path: "/io/liri/desktop/peripherals/keyboard/"
    }

    GSettings {
        id: uiSettings
        schema.id: "io.liri.desktop.interface"
        schema.path: "/io/liri/desktop/interface/"
    }

        ModuleContainer {
            title: qsTr("Typing")

            ListItem {
                text: qsTr("Repeat Keys")
                rightItem: Switch {
                    id: repeatKeysSwitch
                    anchors.centerIn: parent
                    onCheckedChanged: keyboardSettings.repeat = checked
                }
            }

            ListItem {
                text: qsTr("Delay")
                rightItem: Slider {
                    id: inputIntervalSlider
                    anchors.centerIn: parent
                    stepSize: 1
                    from: 0
                    to: 1000
                    onValueChanged: keyboardSettings.repeatInterval = to - value
                }
            }

            ListItem {
                text: qsTr("Speed")
                rightItem: Slider {
                    id: autoRepeatRateSlider
                    anchors.centerIn: parent
                    stepSize: 1
                    from: 0
                    to: 1000
                    onValueChanged: keyboardSettings.delay = to - value
                }
            }
        }

        ModuleContainer {
            title: qsTr("Cursor")

            ListItem {
                text: qsTr("Cursor Blinking")
                rightItem: Switch {
                    id: cursorBlinkingSwitch
                    anchors.centerIn: parent
                }
            }

            ListItem {
                text: qsTr("Speed")
                rightItem: Slider {
                    id: cursorFlashTimeSlider
                    anchors.centerIn: parent
                    stepSize: 1
                    from: 100
                    to: 2500
                    onValueChanged: uiSettings.cursorBlinkTime = to - value
                }
            }

            ListItem {
                text: qsTr("Timeout")
                rightItem: Slider {
                    id: cursorFlashTimeoutSlider
                    anchors.centerIn: parent
                    stepSize: 1
                    from: 1
                    to: 2147483647
                    onValueChanged: uiSettings.cursorBlinkTimeout = to - value
                }
            }
        }

        ModuleContainer {
            title: qsTr("Input Sources")

            ListItem {
                text: qsTr("Virtual Keyboard")
                rightItem: Switch {
                    id: virtualKeyboardSwitch
                    onCheckedChanged: uiSettings.inputMethod = checked ? "qtvirtualkeyboard" : ""
                }
            }
        }

    Component.onCompleted: {
        repeatKeysSwitch.checked = keyboardSettings.repeat;
        cursorBlinkingSwitch.checked = uiSettings.cursorBlink;
        inputIntervalSlider.value = inputIntervalSlider.to - keyboardSettings.repeatInterval;
        autoRepeatRateSlider.value = autoRepeatRateSlider.to - keyboardSettings.delay;
        cursorFlashTimeSlider.value = cursorFlashTimeSlider.to - uiSettings.cursorBlinkTime;
        virtualKeyboardSwitch.checked = uiSettings.inputMethod === "qtvirtualkeyboard";
    }
}
