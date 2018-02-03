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
import QtQuick.Controls.Material 2.0
import Fluid.Controls 1.0 as FluidControls
import Liri.Settings 1.0
import Vibe.Hardware 1.0
import QtGSettings 1.0

PrefletPage {
    GSettings {
        id: sessionSettings

        schema.id: "io.liri.session"
        schema.path: "/io/liri/session/"
    }

    GSettings {
        id: powerSettings

        schema.id: "io.liri.hardware.power"
        schema.path: "/io/liri/hardware/power/"
    }

    HardwareEngine {
        id: hardwareEngine
    }

    AutomaticSuspendDialog {
        id: automaticSuspendDialog
    }

    ModuleContainer {
        title: qsTr("Devices")
        visible: repeater.count > 0

        Repeater {
            id: repeater
            model: hardwareEngine.batteries
            delegate: BatteryListItem { battery: modelData }
        }
    }

    ModuleContainer {
        title: qsTr("Power Saving")

        FluidControls.ListItem {
            text: qsTr("Screen brightness")
            secondaryItem: Slider {
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width
                from: 0
                to: 100
                value: 50
            }
            visible: false // hardwareEngine.batteries.length > 0
        }

        FluidControls.ListItem {
            text: qsTr("Keyboard brightness")
            secondaryItem: Slider {
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width
                from: 0
                to: 100
                value: 50
            }
            visible: false // hardwareEngine.batteries.length > 0
        }

        FluidControls.ListItem {
            text: qsTr("Dim screen when inactive")
            rightItem: Switch {
                anchors.centerIn: parent
                checked: powerSettings.idleDim
                onCheckedChanged: powerSettings.idleDim = checked
            }
            visible: hardwareEngine.batteries.length > 0
        }

        FluidControls.ListItem {
            text: qsTr("Blank screen")
            rightItem: ComboBox {
                anchors.centerIn: parent
                width: FluidControls.Units.gu(6)
                textRole: "text"
                model: ListModel {
                    ListElement { text: QT_TR_NOOP("1 minute"); value: 60 }
                    ListElement { text: QT_TR_NOOP("2 minutes"); value: 120 }
                    ListElement { text: QT_TR_NOOP("3 minutes"); value: 180 }
                    ListElement { text: QT_TR_NOOP("4 minutes"); value: 240 }
                    ListElement { text: QT_TR_NOOP("5 minutes"); value: 300 }
                    ListElement { text: QT_TR_NOOP("8 minutes"); value: 480 }
                    ListElement { text: QT_TR_NOOP("10 minutes"); value: 600 }
                    ListElement { text: QT_TR_NOOP("12 minutes"); value: 720 }
                    ListElement { text: QT_TR_NOOP("15 minutes"); value: 900 }
                    ListElement { text: QT_TR_NOOP("Never"); value: 0 }
                }
                currentIndex: {
                    switch (sessionSettings.idleDelay) {
                    case 60:
                        return 0;
                    case 120:
                        return 1;
                    case 180:
                        return 2;
                    case 240:
                        return 3;
                    case 300:
                        return 4;
                    case 480:
                        return 5;
                    case 600:
                        return 6;
                    case 720:
                        return 7;
                    case 900:
                        return 8;
                    }

                    return 9;
                }
                onActivated: {
                    sessionSettings.idleDelay = model.get(index).value;
                }
            }
        }

        FluidControls.ListItem {
            text: qsTr("Wi-Fi")
            subText: qsTr("Turn off Wi-Fi to save power")
            rightItem: Switch {
                anchors.centerIn: parent
                checked: true
            }
            visible: false
        }

        FluidControls.ListItem {
            text: qsTr("Bluetooth")
            subText: qsTr("Turn off Bluetooth to save power")
            rightItem: Switch {
                anchors.centerIn: parent
                checked: true
            }
            visible: false
        }
    }

    ModuleContainer {
        title: qsTr("Suspend & Power Button")

        FluidControls.ListItem {
            text: qsTr("Automatic suspend")
            rightItem: FluidControls.BodyLabel {
                anchors.centerIn: parent
                text: {
                    var batteryOn = powerSettings.sleepInactiveBatteryType === "suspend";
                    var acOn = powerSettings.sleepInactiveAcType === "suspend";

                    if (hardwareEngine.batteries.length > 0) {
                        if (batteryOn && acOn)
                            return qsTr("On");
                        else if (batteryOn)
                            return qsTr("When on battery power");
                        else if (acOn)
                            return qsTr("When plugged in");
                    } else if (acOn) {
                        return qsTr("On");
                    }

                    return qsTr("Off");
                }
                color: Material.secondaryTextColor
            }
            onClicked: automaticSuspendDialog.open()
        }

        FluidControls.ListItem {
            text: qsTr("When the Power Button is pressed")
            rightItem: ComboBox {
                anchors.centerIn: parent
                textRole: "text"
                model: ListModel {
                    ListElement { text: QT_TR_NOOP("Ask"); value: "interactive" }
                    ListElement { text: QT_TR_NOOP("Suspend"); value: "suspend" }
                    ListElement { text: QT_TR_NOOP("Hibernate"); value: "hibernate" }
                    ListElement { text: QT_TR_NOOP("Nothing"); value: "nothing" }
                }
                currentIndex: {
                    switch (powerSettings.powerButtonAction) {
                    case "interactive":
                        return 0;
                    case "suspend":
                        return 1;
                    case "hibernate":
                        return 2;
                    }

                    return 3;
                }
                onActivated: {
                    powerSettings.powerButtonAction = model.get(index).value;
                }
            }
        }
    }
}
