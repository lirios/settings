/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2013-2016 Pier Luigi Fiorini
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
import QtQuick.Window 2.1
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import Fluid.Controls 1.0

Dialog {
    id: hiddenWifiDialog
    title: qsTr("Connect to a hidden Wi-Fi network")
    modality: Qt.ApplicationModal
    width: 400
    height: 250

    ColumnLayout {
        anchors {
            fill: parent
            margins: Units.largeSpacing
        }

        RowLayout {
            Icon {
                iconName: "network-wireless"
                width: Units.iconSizes.smallMedium
                height: width

                Layout.alignment: Qt.AlignTop
            }

            ColumnLayout {
                Label {
                    text: qsTr("Hidden Wi-Fi network")
                    font.bold: true
                }

                Label {
                    text: qsTr("Enter the name and security details of the hidden Wi-Fi network you wish to connect to.")
                    wrapMode: Text.WordWrap

                    Layout.fillWidth: true
                }
            }
        }

        GridLayout {
            columns: 2
            rows: 2

            Label {
                text: qsTr("Network name:")

                Layout.alignment: Qt.AlignRight
            }

            TextField {
                id: name

                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Wi-Fi security:")

                Layout.alignment: Qt.AlignRight
            }

            ComboBox {
                id: security
                model: [ qsTr("None"),
                    qsTr("WEP 40/128-bit Key (Hex or ASCII)"),
                    qsTr("WEP 128-bit Passphrase"),
                    qsTr("LEAP"),
                    qsTr("Dynamic WEP (802.1x)"),
                    qsTr("WPA & WPA2 Personal"),
                    qsTr("WPA & WPA2 Enterprise"),
                    qsTr("WPS") ]
                onCurrentIndexChanged: tab.currentIndex = index
            }

            Layout.fillWidth: true
        }

        TabView {
            id: tab
            frameVisible: false
            tabVisible: false

            Tab {
                GridLayout {
                    columns: 2
                    rows: 4

                    Label {
                        text: qsTr("Key:")

                        Layout.alignment: Qt.AlignRight
                    }

                    TextField {
                        id: wepKey
                        echoMode: TextInput.Password
                    }

                    Item {
                        Layout.alignment: Qt.AlignRight
                        Layout.fillWidth: true
                    }

                    CheckBox {
                        text: qsTr("Show key")
                        onClicked: wepKey.echoMode = checked ? TextInput.Normal : TextInput.Password
                    }

                    Label {
                        text: qsTr("WEP index:")

                        Layout.alignment: Qt.AlignRight
                    }

                    ComboBox {
                        id: wepIndex
                        model: [ qsTr("1 (Default)"),
                            qsTr("2"), qsTr("3"), qsTr("4") ]
                    }

                    Label {
                        text: qsTr("Authentication:")

                        Layout.alignment: Qt.AlignRight
                    }

                    ComboBox {
                        id: wepAuth
                        model: [ qsTr("Open System"), qsTr("Shared Key") ]
                    }
                }
            }

            Tab {
            }

            Tab {
                GridLayout {
                    columns: 2
                    rows: 3

                    Label {
                        text: qsTr("Username:")

                        Layout.alignment: Qt.AlignRight
                    }

                    TextField {
                        id: userName

                        Layout.fillWidth: true
                    }

                    Label {
                        text: qsTr("Password:")

                        Layout.alignment: Qt.AlignRight
                    }

                    TextField {
                        id: password
                        echoMode: TextInput.Password

                        Layout.fillWidth: true
                    }

                    Item {
                        Layout.fillWidth: true
                    }

                    CheckBox {
                        text: qsTr("Show password")
                        onClicked: password.echoMode = checked ? TextInput.Normal : TextInput.Password
                    }
                }
            }

            Tab {
            }

            Tab {
                GridLayout {
                    columns: 2
                    rows: 2

                    Label {
                        text: qsTr("Password:")

                        Layout.alignment: Qt.AlignRight
                    }

                    TextField {
                        id: wpaPassword
                        echoMode: TextInput.Password

                        Layout.fillWidth: true
                    }

                    Item {
                        Layout.fillWidth: true
                    }

                    CheckBox {
                        text: qsTr("Show password")
                        onClicked: wpaPassword.echoMode = checked ? TextInput.Normal : TextInput.Password
                    }
                }
            }

            Tab {
            }

            Tab {
            }
        }

        Item {
            Layout.fillHeight: true
        }

        RowLayout {
            Button {
                text: qsTr("Cancel")
                onClicked: hiddenWifiDialog.close()
            }

            Button {
                id: connectButton
                text: qsTr("Connect")
                enabled: false
            }

            Layout.alignment: Qt.AlignRight
            Layout.fillWidth: true
        }
    }
}
