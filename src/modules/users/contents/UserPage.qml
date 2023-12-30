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

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material
import Fluid.Controls as FluidControls
import Liri.Settings
import Liri.Settings.Users
import QtAccountsService

ModulePage {
    id: page

    property alias userId: account.userId
    property bool isCurrentUser
    property alias iconFileName: photo.source
    property alias realName: realNameField.text
    property alias accountType: accountTypeCombo.currentIndex
    property alias automaticLogin: automaticLoginSwitch.checked
    property bool loaded: false

    title: account.realName
    needsAuthorization: true

    Component.onCompleted: loaded = true

    UserAccount {
        id: account
    }

    FluidControls.AlertDialog {
        id: errorDialog
        standardButtons: Dialog.Ok
        width: 400
    }

    FluidControls.SnackBar {
        id: snack
    }

    ScrollView {
        anchors.fill: parent
        clip: true

        Column {
            ModuleContainer {
                width: page.width

                Control {
                    width: parent.width
                    height: contentItem.implicitHeight + topPadding + bottomPadding
                    padding: FluidControls.Units.smallSpacing * 2

                    contentItem: RowLayout {
                        spacing: FluidControls.Units.smallSpacing * 2

                        PhotoPicker {
                            id: photo
                            enabled: isCurrentUser || modulePage.unlocked
                            onFileSelected: account.iconFileName = fileName.replace("file://", "")
                        }

                        TextField {
                            id: realNameField
                            placeholderText: qsTr("Full name")
                            focus: true
                            enabled: isCurrentUser || modulePage.unlocked
                            onAccepted: if (loaded) account.realName = text

                            Layout.alignment: Qt.AlignVCenter
                            Layout.fillWidth: true
                        }
                    }
                }

                FluidControls.ListItem {
                    text: qsTr("Account type")
                    rightItem: ComboBox {
                        id: accountTypeCombo
                        anchors.verticalCenter: parent.verticalCenter
                        model: [qsTr("Standard"), qsTr("Administrator")]
                        width: 200
                        enabled: modulePage.unlocked
                        onCurrentIndexChanged: if (loaded) account.accountType = currentIndex
                    }
                }

                FluidControls.ListItem {
                    text: qsTr("Automatic login")
                    rightItem: Switch {
                        id: automaticLoginSwitch
                        anchors.verticalCenter: parent.verticalCenter
                        enabled: modulePage.unlocked
                        onCheckedChanged: if (loaded) account.automaticLogin = checked
                    }
                }
            }

            ModuleContainer {
                title: qsTr("Password")
                width: page.width
                enabled: modulePage.unlocked

                Control {
                    width: parent.width
                    height: contentItem.implicitHeight + topPadding + bottomPadding
                    padding: FluidControls.Units.smallSpacing * 2

                    contentItem: ColumnLayout {
                        spacing: FluidControls.Units.smallSpacing * 2

                        TextField {
                            id: newPasswordField1
                            placeholderText: qsTr("New password")
                            echoMode: TextField.Password

                            Layout.fillWidth: true
                        }

                        TextField {
                            id: newPasswordField2
                            placeholderText: qsTr("Verify new password")
                            echoMode: TextField.Password

                            Layout.fillWidth: true
                        }

                        DialogButtonBox {
                            alignment: Qt.AlignRight

                            Layout.fillWidth: true

                            Button {
                                text: qsTr("Change")
                                flat: true
                                enabled: newPasswordField1.text && newPasswordField2.text
                                onClicked: {
                                    if (newPasswordField1.text != newPasswordField2.text) {
                                        errorDialog.title = qsTr("Wrong password verification");
                                        errorDialog.text = qsTr("The passwords did not match.");
                                        newPasswordField1.clear();
                                        newPasswordField2.clear();
                                        errorDialog.open();
                                        return;
                                    }

                                    account.setPassword(Password.cryptPassword(newPasswordField2.text));
                                    snack.open(qsTr("Password changed"));
                                    newPasswordField1.clear();
                                    newPasswordField2.clear();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
