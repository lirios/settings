/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2018 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 * Copyright (C) 2016 Michael Spencer <sonrisesoftware@gmail.com>
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

import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.2
import Fluid.Controls 1.0 as FluidControls
import Liri.Settings 1.0
import QtAccountsService 1.0

ModulePage {
    id: modulePage

    needsAuthorization: true
    unlocked: authorization.authorized

    onUnlockRequested: authorization.authorize()

    AuthorizedAction {
        id: authorization
        actionId: "org.freedesktop.accounts.user-administration"
    }

    UserAccount {
        id: currentUser
    }

    UsersModel {
        id: userModel
    }

    AccountsManager {
        id: accountsManager
    }

    Component {
        id: userPage

        UserPage {
            onUnlockRequested: authorization.authorize()
        }
    }

    UserAddDialog {
        id: addUserDialog
    }

    ScrollView {
        anchors.fill: parent
        clip: true

        Column {
            width: Math.max(implicitWidth, parent.width)

            ModuleContainer {
                title: qsTr("Your Account")

                UserListItem {
                    iconSource: currentUser.iconFileName
                    text: currentUser.realName
                    subText: currentUser.userName
                    isAdminUser: currentUser.accountType == UserAccount.AdministratorAccountType
                    isCurrentUser: true
                    onClicked: window.pageStack.push(userPage, {
                                                         "unlocked": Qt.binding(function() { return modulePage.unlocked; }),
                                                         "userId": currentUser.userId,
                                                         "isCurrentUser": true,
                                                         "iconFileName": currentUser.iconFileName,
                                                         "realName": currentUser.realName,
                                                         "accountType": currentUser.accountType,
                                                         "automaticLogin": currentUser.automaticLogin
                                                     })
                }
            }

            ModuleContainer {
                title: qsTr("Other Accounts")

                // Only show if larger than one because the first user
                // is the current user and is hidden
                visible: userRepeater.count > 1

                Repeater {
                    id: userRepeater
                    model: userModel
                    delegate: UserListItem {
                        iconSource: iconFileName
                        text: realName
                        subText: userName
                        isAdminUser: accountType == UserAccount.AdministratorAccountType
                        isCurrentUser: userId === currentUser.userId
                        visible: userId !== currentUser.userId
                        onClicked: window.pageStack.push(userPage, {
                                                             "unlocked": Qt.binding(function() { return modulePage.unlocked; }),
                                                             "userId": userId,
                                                             "isCurrentUser": false,
                                                             "iconFileName": iconFileName,
                                                             "realName": realName,
                                                             "accountType": accountType,
                                                             "automaticLogin": automaticLogin
                                                         })
                        onRemoveUserRequested: accountsManager.deleteUser(userId, removeFiles)
                    }
                }

                FluidControls.ListItem {
                    icon.source: FluidControls.Utils.iconUrl("content/add")
                    text: qsTr("Add user...")
                    enabled: modulePage.unlocked
                    onClicked: addUserDialog.open()
                }
            }
        }
    }
}
