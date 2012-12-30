/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2011-2012 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
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

#include <QPixmap>

#include "usersmodel.h"
#include "usersmodel_p.h"

/*
 * UsersModelPrivate
 */

UsersModelPrivate::UsersModelPrivate(UsersModel *self)
    : q_ptr(self)
{
    manager = new VAccountsManager();
    list = manager->listCachedUsers();
}

UsersModelPrivate::~UsersModelPrivate()
{
    delete manager;
}

/*
 * UsersModel
 */

UsersModel::UsersModel(QObject *parent)
    : QAbstractListModel(parent)
    , d_ptr(new UsersModelPrivate(this))
{
}

QHash<int, QByteArray> UsersModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles[UserIdRole] = "userId";
    roles[UserNameRole] = "userName";
    roles[RealNameRole] = "realName";
    roles[IconFileNameRole] = "iconFileName";
    roles[AccountTypeRole] = "accountType";
    roles[LanguageRole] = "language";
    return roles;
}

int UsersModel::rowCount(const QModelIndex &parent) const
{
    Q_D(const UsersModel);

    if (parent == QModelIndex())
        return d->list.size();

    return 0;
}

QVariant UsersModel::data(const QModelIndex &index, int role) const
{
    Q_D(const UsersModel);

    if (!index.isValid())
        return QVariant();

    int row = index.row();

    switch (role) {
    case Qt::DisplayRole:
        return d->list[row]->displayName();
    case Qt::DecorationRole:
        return QPixmap(d->list[row]->iconFileName());
    case UsersModel::UserIdRole:
        return d->list[row]->userId();
    case UsersModel::UserNameRole:
        return d->list[row]->userName();
    case UsersModel::RealNameRole:
        return d->list[row]->realName();
    case UsersModel::IconFileNameRole:
        return d->list[row]->iconFileName();
    case UsersModel::AccountTypeRole:
        return d->list[row]->accountType();
    case UsersModel::LanguageRole:
        return d->list[row]->language();
    }

    return QVariant();
}

bool UsersModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_D(UsersModel);

    if (!index.isValid())
        return false;

    VUserAccount *user = d->list[index.row()];

    switch (role) {
    case UsersModel::UserNameRole:
        user->setUserName(value.toString());
        break;
    case UsersModel::RealNameRole:
        user->setRealName(value.toString());
        break;
    case UsersModel::IconFileNameRole:
        user->setIconFileName(value.toString());
        break;
    case UsersModel::AccountTypeRole:
        user->setAccountType((VUserAccount::AccountType) value.toInt());
        break;
    case UsersModel::LanguageRole:
        user->setLanguage(value.toString());
        break;
    default:
        return false;
    }

    return true;
}

#include "moc_usersmodel.cpp"
