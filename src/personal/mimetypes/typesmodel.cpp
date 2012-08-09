/****************************************************************************
 * This file is part of Preferences.
 *
 * Copyright (c) 2012 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Preferences is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Preferences is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Preferences.  If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "typesmodel.h"

TypesModel::TypesModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

int TypesModel::rowCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant TypesModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

#include "moc_typesmodel.cpp"
