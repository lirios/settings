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
import QtQuick.Controls 2.1
import Fluid.Controls 1.0 as FluidControls

Dialog {
    readonly property bool __hasBatteries: hardwareEngine.batteries.length > 0

    parent: window.contentItem

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    title: qsTr("Automatic Suspend")

    modal: true

    GridLayout {
        rows: __hasBatteries ? 4 : 2
        columns: 3

        // Row 1

        Label {
            id: batteryLabel
            text: qsTr("On Battery Power")
            visible: __hasBatteries
        }

        Switch {
            id: batterySwitch
            checked: powerSettings.sleepInactiveBatteryType !== "nothing"
            visible: __hasBatteries
            onCheckedChanged: {
                powerSettings.sleepInactiveBatteryType = checked ? "suspend" : "nothing"
            }

            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignRight
        }

        // Row 2

        Item {
            visible: __hasBatteries

            Layout.minimumWidth: batteryLabel.width + FluidControls.Units.gu(2)
        }

        Label {
            enabled: batterySwitch.checked
            text: qsTr("Delay")
            visible: __hasBatteries

            Layout.alignment: Qt.AlignRight
        }

        ComboBox {
            textRole: "text"
            enabled: batterySwitch.checked
            visible: __hasBatteries
            model: ListModel {
                ListElement { text: QT_TR_NOOP("15 minutes"); value: 900 }
                ListElement { text: QT_TR_NOOP("30 minutes"); value: 1800 }
                ListElement { text: QT_TR_NOOP("45 minutes"); value: 2700 }
                ListElement { text: QT_TR_NOOP("1 hour"); value: 3600 }
                ListElement { text: QT_TR_NOOP("80 minutes"); value: 4800 }
                ListElement { text: QT_TR_NOOP("90 minutes"); value: 5400 }
                ListElement { text: QT_TR_NOOP("100 minutes"); value: 6000 }
                ListElement { text: QT_TR_NOOP("2 hours"); value: 7200 }
            }
            currentIndex: {
                switch (powerSettings.sleepInactiveBatteryTimeout) {
                case 900:
                    return 0;
                case 1800:
                    return 1;
                case 2700:
                    return 2;
                case 3600:
                    return 3;
                case 4800:
                    return 4;
                case 5400:
                    return 5;
                case 6000:
                    return 6;
                case 7200:
                    return 7;
                }

                return 7;
            }
            onActivated: {
                powerSettings.sleepInactiveBatteryTimeout = model.get(index).value;
            }

            Layout.preferredWidth: FluidControls.Units.gu(6)
            Layout.alignment: Qt.AlignRight
        }

        // Row 3

        Label {
            id: acLabel
            text: __hasBatteries ? qsTr("Plugged In") : qsTr("When idle")
        }

        Switch {
            id: acSwitch
            checked: powerSettings.sleepInactiveAcType !== "nothing"
            onCheckedChanged: {
                powerSettings.sleepInactiveAcType = checked ? "suspend" : "nothing"
            }

            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignRight
        }

        // Row 4

        Item {
            Layout.minimumWidth: acLabel.width + FluidControls.Units.gu(2)
        }

        Label {
            enabled: acSwitch.checked
            text: qsTr("Delay")

            Layout.alignment: Qt.AlignRight
        }

        ComboBox {
            textRole: "text"
            enabled: acSwitch.checked
            model: ListModel {
                ListElement { text: QT_TR_NOOP("15 minutes"); value: 900 }
                ListElement { text: QT_TR_NOOP("30 minutes"); value: 1800 }
                ListElement { text: QT_TR_NOOP("45 minutes"); value: 2700 }
                ListElement { text: QT_TR_NOOP("1 hour"); value: 3600 }
                ListElement { text: QT_TR_NOOP("80 minutes"); value: 4800 }
                ListElement { text: QT_TR_NOOP("90 minutes"); value: 5400 }
                ListElement { text: QT_TR_NOOP("100 minutes"); value: 6000 }
                ListElement { text: QT_TR_NOOP("2 hours"); value: 7200 }
            }
            currentIndex: {
                switch (powerSettings.sleepInactiveAcTimeout) {
                case 900:
                    return 0;
                case 1800:
                    return 1;
                case 2700:
                    return 2;
                case 3600:
                    return 3;
                case 4800:
                    return 4;
                case 5400:
                    return 5;
                case 6000:
                    return 6;
                case 7200:
                    return 7;
                }

                return 7;
            }
            onActivated: {
                powerSettings.sleepInactiveAcTimeout = model.get(index).value;
            }

            Layout.preferredWidth: FluidControls.Units.gu(6)
            Layout.alignment: Qt.AlignRight
        }
    }
}
