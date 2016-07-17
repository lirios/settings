/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2016 Michael Spencer <sonrisesoftware@gmail.com>
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

import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import Fluid.Controls 1.0
import Fluid.UI 1.0
import Hawaii.SystemSettings 1.0
import QtAccountsService 1.0

PrefletPage {
    UserAccount {
        id: currentUser
    }

    UsersModel {
        id: userModel
    }

    Subheader {
        text: "Your Account"
    }

    UserListItem {
        iconSource: currentUser.iconFileName
        text: currentUser.realName
        subText: currentUser.userName
        isAdminUser: currentUser.accountType == UserAccount.AdministratorAccountType
    }

    Subheader {
        text: "Other Accounts"

        // Only show if larger than one because the first user
        // is the current user and is hidden
        visible: userRepeater.count > 1
    }

    Repeater {
        id: userRepeater
        model: userModel
        delegate: UserListItem {
            iconSource: iconFileName
            text: realName
            subText: userName
            isAdminUser: accountType == UserAccount.AdministratorAccountType
            visible: userId != currentUser.uid
        }
    }
}
