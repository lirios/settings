/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (c) 2012 Pier Luigi Fiorini
 * Copyright (c) 2007 Will Stephenson
 * Copyright (c) 2009 Ben Cooksley
 *
 * Author(s):
 *    Ben Cooksley <bcooksley@kde.org>
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *    Will Stephenson <wstephenson@kde.org>
 *
 * $BEGIN_LICENSE:GPL$
 *
 * System Preferences is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * System Preferences is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with System Preferences.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include "menuproxymodel.h"
#include "menuitem.h"
#include "menumodel.h"

MenuProxyModel::MenuProxyModel(QObject *parent)
    : VCategorizedSortFilterProxyModel(parent)
{
    setSortRole(MenuModel::UserSortRole);
    setFilterRole(MenuModel::UserFilterRole);
    setFilterCaseSensitivity(Qt::CaseInsensitive);
}

bool MenuProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    if (isCategorizedModel())
        return VCategorizedSortFilterProxyModel::lessThan(left, right);

    QVariant leftWeight = left.data(MenuModel::UserSortRole);
    QVariant rightWeight = right.data(MenuModel::UserSortRole);

    if (leftWeight.toInt() == rightWeight.toInt())
        return left.data().toString() < right.data().toString();

    return leftWeight.toInt() < rightWeight.toInt();
}

bool MenuProxyModel::subSortLessThan(const QModelIndex &left, const QModelIndex &right) const
{
    if (isCategorizedModel()) {
        QVariant leftWeight = left.data(MenuModel::UserSortRole);
        QVariant rightWeight = right.data(MenuModel::UserSortRole);

        if (!leftWeight.isValid() || !rightWeight.isValid()) {
            return VCategorizedSortFilterProxyModel::subSortLessThan(left, right);
        } else {
            if (leftWeight.toInt() == rightWeight.toInt()) {
                return left.data().toString() < right.data().toString();
            } else {
                return leftWeight.toInt() < rightWeight.toInt();
            }
        }
    }
    return VCategorizedSortFilterProxyModel::subSortLessThan(left, right);
}

bool MenuProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    return true;
}

Qt::ItemFlags MenuProxyModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    QString matchText = index.data(MenuModel::UserFilterRole).toString();
    if (!matchText.contains(filterRegExp()))
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void MenuProxyModel::setFilterRegExp(const QString &pattern)
{
    emit layoutAboutToBeChanged();
    VCategorizedSortFilterProxyModel::setFilterRegExp(pattern);
    emit layoutChanged();
}

void MenuProxyModel::setFilterRegExp(const QRegExp &regExp)
{
    emit layoutAboutToBeChanged();
    VCategorizedSortFilterProxyModel::setFilterRegExp(regExp);
    emit layoutChanged();
}

#include "moc_menuproxymodel.cpp"
