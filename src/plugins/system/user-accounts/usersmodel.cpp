/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (c) 2011-2012 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include "usersmodel.h"
#include "vusersmodel_p.h"

#include <sys/types.h>
#include <pwd.h>

/*
 * VUserItem
 */

QString VUserItem::displayName() const
{
    if (realName.isEmpty())
        return name;

    return realName;
}

/*
 * VUsersModelPrivate
 */

VUsersModelPrivate::VUsersModelPrivate(VUsersModel *parent) :
    q_ptr(parent)
{
}

void VUsersModelPrivate::populate()
{
    Q_Q(VUsersModel);

    struct passwd *pwent = 0;

    while ((pwent = getpwent()) != 0) {
        VUserItem item;
        item.uid = pwent->pw_uid;
        item.gid = pwent->pw_gid;
        item.name = QLatin1String(pwent->pw_name);
        item.realName = QLatin1String(pwent->pw_gecos);
        item.homeDirectory = QLatin1String(pwent->pw_dir);
        item.shell = QLatin1String(pwent->pw_shell);
    }

    endpwent();

    int rowCount =
}

    /*
     * VUsersModel
     */

    VUsersModel::VUsersModel(QObject *parent) :
        QAbstractListModel(parent)
{
    // Extended roles, might also be useful for QML
    QHash<int, QByteArray> roles = roleNames();
    roles[NameRole] = "name";
    roles[LoggedInRole] = "loggedIn";
    setRoleNames(roles);
}
