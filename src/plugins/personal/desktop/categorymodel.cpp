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

#include <QIcon>
#include <QDirIterator>

#include <VStandardDirectories>
#include <VDesktopFile>

#include "backgroundcategoriesmodel.h"

using namespace VStandardDirectories;

CategoryModel::CategoryModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    m_rootItem = new CategoryItem("Root");

    m_coatingsItem = new CategoryItem(tr("Coatings"), m_rootItem);
    populateCoatings();
    m_rootItem->appendChild(m_coatingsItem);

    m_foldersItem = new CategoryItem(tr("Folders"), m_rootItem);
    populateFolders();
    m_rootItem->appendChild(m_foldersItem);

    m_colorsItem = new CategoryItem(tr("Colors and gradients"), m_rootItem);
    populateColors();
    m_rootItem->appendChild(m_colorsItem);
}

CategoryModel::~BackgroundCategoriesModel()
{
    delete m_foldersItem;
    delete m_coatingsItem;
    delete m_rootItem;
}

int CategoryModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant CategoryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    CategoryItem *item  = static_cast<CategoryItem *>(index.internalPointer());
    return item->data(role);
}

Qt::ItemFlags CategoryModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QModelIndex CategoryModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    CategoryItem *parentItem;

    if (!parent.isValid())
        parentItem = m_rootItem;
    else
        parentItem = static_cast<CategoryItem *>(parent.internalPointer());

    CategoryItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex CategoryModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    CategoryItem *childItem = static_cast<CategoryItem *>(index.internalPointer());
    CategoryItem *parentItem = childItem->parent();

    if (parentItem == m_rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int CategoryModel::rowCount(const QModelIndex &parent) const
{
    CategoryItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = m_rootItem;
    else
        parentItem = static_cast<CategoryItem *>(parent.internalPointer());

    return parentItem->childCount();
}

void CategoryModel::populateCoatings()
{
    QString path = QString("%1/wallpapers").arg(findDirectory(SystemDataDirectory));
    QDirIterator it(path, QDir::Dirs | QDir::Readable | QDir::NoDotAndDotDot,
                    QDirIterator::FollowSymlinks);
    while (it.hasNext()) {
        QDir dir(it.next());
        if (dir.exists("metadata.desktop")) {
            QString file = dir.absoluteFilePath("metadata.desktop");
            VDesktopFile entry(file);

            CategoryItem *leaf = new CategoryItem(
                QIcon::fromTheme("folder"), entry.name(), m_coatingsItem);
            leaf->setDirectory(dir.path());
            m_coatingsItem->appendChild(leaf);
        }
    }
}

void CategoryModel::populateFolders()
{
}

void CategoryModel::populateColors()
{
}

#include "moc_backgroundcategoriesmodel.cpp"
