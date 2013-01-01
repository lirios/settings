/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2011-2013 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include "categoryitem.h"

CategoryItem::CategoryItem(const QString &label, CategoryItem *parent)
{
    m_parentItem = parent;
    m_label = label;
}

CategoryItem::CategoryItem(const QIcon &icon, const QString &label, CategoryItem *parent)
{
    m_parentItem = parent;
    m_icon = icon;
    m_label = label;
}

CategoryItem::~CategoryItem()
{
    qDeleteAll(m_childItems);
}

void CategoryItem::setDirectory(const QDir &dir)
{
    m_dir = dir;
}

void CategoryItem::appendChild(CategoryItem *item)
{
    m_childItems.append(item);
}

CategoryItem *CategoryItem::child(int row)
{
    return m_childItems.value(row);
}

int CategoryItem::childCount() const
{
    return m_childItems.count();
}

int CategoryItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<BackgroundCategoriesItem *>(this));
    return 0;
}

QVariant CategoryItem::data(int role)
{
    switch (role) {
        case Qt::DecorationRole:
            return m_icon;
        case Qt::DisplayRole:
            return m_label;
        case BackgroundCategoriesModel::AbsolutePath:
            return m_dir.absolutePath();
    }

    return QVariant();
}

CategoryItem *CategoryItem::parent() const
{
    return m_parentItem;
}
