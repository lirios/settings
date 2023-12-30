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
import Fluid.Controls as FluidControls
import Liri.Settings.Users
import QtAccountsService

Dialog {
    id: addUserDialog

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    parent: ApplicationWindow.contentItem
    modal: true

    onRejected: clearFields()

    function clearFields() {
        userNameField.text = "";
        realNameField.text = "";
        setPasswordLater.checked = true;
        passwordField1.text = "";
        passwordField2.text = "";
    }

    AccountsManager {
        id: manager

        onUserAdded: {
            if (account.userName === userNameField.text) {
                console.info("Set password for", account.userName);
                if (setPasswordNow.checked) {
                    account.passwordMode = UserAccount.RegularPasswordMode;
                    account.setPassword(Password.cryptPassword(passwordField1.text));
                } else if (noPassword.checked) {
                    account.passwordMode = UserAccount.NonePasswordMode;
                } else {
                    account.passwordMode = UserAccount.SetAtLoginPasswordMode;
                }

                clearFields();
            }
        }
    }

    footer: DialogButtonBox {
        Button {
            text: qsTr("Cancel")
            flat: true
            onClicked: addUserDialog.reject()

            DialogButtonBox.buttonRole: DialogButtonBox.Cancel
        }

        Button {
            id: okButton
            text: qsTr("OK")
            flat: true
            enabled: realNameField.text != "" &&
                     userNameField.text != "" &&
                     (setPasswordLater.checked ||
                      noPassword.checked || (
                          setPasswordNow.checked &&
                          passwordField1.text != "" &&
                          passwordField1.text == passwordField2.text)
                      )
            onClicked: {
                if (manager.createUser(userNameField.text, realNameField.text, accountTypeCombo.currentIndex))
                    addUserDialog.accept();
            }

            DialogButtonBox.buttonRole: DialogButtonBox.Ok
        }
    }

    ColumnLayout {
        RowLayout {
            Label {
                text: qsTr("Account type")
            }

            Item {
                Layout.fillWidth: true
            }

            ComboBox {
                id: accountTypeCombo
                model: [qsTr("Standard"), qsTr("Administrator")]

                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.preferredWidth: 200
            }
        }

        TextField {
            id: realNameField
            placeholderText: qsTr("Full name")
            focus: true

            Layout.fillWidth: true
        }

        TextField {
            id: userNameField
            placeholderText: qsTr("User name")

            Layout.fillWidth: true
        }

        ColumnLayout {
            RadioButton {
                id: setPasswordLater
                text: qsTr("Allow user to set a password at the next login")
                checked: true
            }

            RadioButton {
                id: setPasswordNow
                text: qsTr("Set a password now")
            }

            RadioButton {
                id: noPassword
                text: qsTr("No password")
            }
        }

        TextField {
            id: passwordField1
            placeholderText: qsTr("New password")
            echoMode: TextField.Password
            enabled: setPasswordNow.checked
            visible: !noPassword.checked

            Layout.fillWidth: true
        }

        TextField {
            id: passwordField2
            placeholderText: qsTr("Verify new password")
            echoMode: TextField.Password
            enabled: setPasswordNow.checked
            visible: !noPassword.checked

            Layout.fillWidth: true
        }
    }
}
