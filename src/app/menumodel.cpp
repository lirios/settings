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

#include <QIcon>

#include <VPreferencesModule>
#include <VCategorizedSortFilterProxyModel>

#include "menuitem.h"
#include "menumodel.h"

const int MenuModel::UserFilterRole = 0x015D1AE6;
const int MenuModel::UserSortRole = 0x03A8CC00;

class MenuModel::Private
{
public:
    Private() {}

    MenuItem *rootItem;
    QList<MenuItem *> exceptions;
};

MenuModel::MenuModel(MenuItem *menuRoot, QObject *parent)
    : QAbstractItemModel(parent)
    , d(new Private())
{
    d->rootItem = menuRoot;
}

MenuModel::~MenuModel()
{
    d->exceptions.clear();
    delete d;
}

int MenuModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

int MenuModel::rowCount(const QModelIndex &parent) const
{
    MenuItem *mi;
    if (parent.isValid())
        mi = static_cast<MenuItem *>(parent.internalPointer());
    else
        mi = d->rootItem;

    return childrenList(mi).count();
}

QVariant MenuModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    MenuItem *mi = static_cast<MenuItem *>(index.internalPointer());

    switch (role) {
        case Qt::DisplayRole:
            return mi->name();
        case Qt::ToolTipRole:
            return mi->comment();
        case Qt::DecorationRole:
            return mi->icon();
        case VCategorizedSortFilterProxyModel::CategorySortRole:
            if (mi->parent())
                return QString("%1%2").arg(QString::number(mi->parent()->weight()), 5, '0').arg(mi->parent()->name());
            break;
        case VCategorizedSortFilterProxyModel::CategoryDisplayRole:
            if (mi->parent())
                return mi->parent()->name();
            break;
        case Qt::UserRole:
            return QVariant::fromValue(mi);
        case MenuModel::UserFilterRole:
            return mi->keywords().join(QString());
        case MenuModel::UserSortRole:
            return QString("%1").arg(QString::number(mi->weight()), 5, '0');
        default:
            break;
    }

    return QVariant();
}

Qt::ItemFlags MenuModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QModelIndex MenuModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    MenuItem *parentItem;
    if (!parent.isValid())
        parentItem = d->rootItem;
    else
        parentItem = static_cast<MenuItem *>(parent.internalPointer());

    MenuItem *childItem = childrenList(parentItem).value(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

QModelIndex MenuModel::parent(const QModelIndex &index) const
{
    MenuItem *childItem = static_cast<MenuItem *>(index.internalPointer());
    if (!childItem)
        return QModelIndex();

    MenuItem *parent = parentItem(childItem);
    MenuItem *grandParent = parentItem(parent);

    int childRow = 0;
    if (grandParent)
        childRow = childrenList(grandParent).indexOf(parent);

    if (parent == d->rootItem)
        return QModelIndex();
    return createIndex(childRow, 0, parent);
}

QList<MenuItem *> MenuModel::childrenList(MenuItem *parent) const
{
    if (!parent)
        return QList<MenuItem *>();

    QList<MenuItem *> children = parent->children();
    foreach(MenuItem * child, children) {
        if (d->exceptions.contains(child)) {
            children.removeOne(child);
            children.append(child->children());
        }
    }
    return children;
}

MenuItem *MenuModel::parentItem(MenuItem *child) const
{
    if (!child)
        return 0;

    MenuItem *parent = child->parent();
    if (d->exceptions.contains(parent))
        parent = parentItem(parent);
    return parent;
}

MenuItem *MenuModel::rootItem() const
{
    return d->rootItem;
}

void MenuModel::addException(MenuItem *exception)
{
    if (exception == d->rootItem)
        return;
    d->exceptions.append(exception);
}

void MenuModel::removeException(MenuItem *exception)
{
    d->exceptions.removeAll(exception);
}

#include "moc_menumodel.cpp"
