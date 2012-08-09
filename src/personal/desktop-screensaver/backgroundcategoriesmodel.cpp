/****************************************************************************
 * This file is part of Preferences.
 *
 * Copyright (c) 2011-2012 Pier Luigi Fiorini
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

#include <QIcon>
#include <QDirIterator>

#include <VStandardDirectories>
#include <VDesktopFile>

#include "backgroundcategoriesmodel.h"

using namespace VStandardDirectories;

/*
 * BackgroundCategoriesItem
 */

class BackgroundCategoriesItem
{
public:
    explicit BackgroundCategoriesItem(const QString &label, BackgroundCategoriesItem *parent = 0) {
        m_parentItem = parent;
        m_label = label;
    }

    explicit BackgroundCategoriesItem(const QIcon &icon, const QString &label, BackgroundCategoriesItem *parent = 0) {
        m_parentItem = parent;
        m_icon = icon;
        m_label = label;
    }

    ~BackgroundCategoriesItem() {
        qDeleteAll(m_childItems);
    }

    void setDirectory(const QDir &dir) {
        m_dir = dir;
    }

    void appendChild(BackgroundCategoriesItem *item) {
        m_childItems.append(item);
    }

    BackgroundCategoriesItem *child(int row) {
        return m_childItems.value(row);
    }

    int childCount() const {
        return m_childItems.count();
    }

    int row() const {
        if (m_parentItem)
            return m_parentItem->m_childItems.indexOf(const_cast<BackgroundCategoriesItem *>(this));
        return 0;
    }

    QVariant data(int role) {
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

    BackgroundCategoriesItem *parent() const {
        return m_parentItem;
    }

private:
    QList<BackgroundCategoriesItem *> m_childItems;
    QIcon m_icon;
    QString m_label;
    QDir m_dir;
    BackgroundCategoriesItem *m_parentItem;
};

/*
 * BackgroundCategoriesModel
 */

BackgroundCategoriesModel::BackgroundCategoriesModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    m_rootItem = new BackgroundCategoriesItem("Root");

    m_systemItem = new BackgroundCategoriesItem(tr("System"), m_rootItem);
    populateSystem();
    m_rootItem->appendChild(m_systemItem);

    m_foldersItem = new BackgroundCategoriesItem(tr("Folders"), m_rootItem);
    populateFolders();
    m_rootItem->appendChild(m_foldersItem);
}

BackgroundCategoriesModel::~BackgroundCategoriesModel()
{
    delete m_foldersItem;
    delete m_systemItem;
    delete m_rootItem;
}

int BackgroundCategoriesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant BackgroundCategoriesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    BackgroundCategoriesItem *item  = static_cast<BackgroundCategoriesItem *>(index.internalPointer());
    return item->data(role);
}

Qt::ItemFlags BackgroundCategoriesModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QModelIndex BackgroundCategoriesModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    BackgroundCategoriesItem *parentItem;

    if (!parent.isValid())
        parentItem = m_rootItem;
    else
        parentItem = static_cast<BackgroundCategoriesItem *>(parent.internalPointer());

    BackgroundCategoriesItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex BackgroundCategoriesModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    BackgroundCategoriesItem *childItem = static_cast<BackgroundCategoriesItem *>(index.internalPointer());
    BackgroundCategoriesItem *parentItem = childItem->parent();

    if (parentItem == m_rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int BackgroundCategoriesModel::rowCount(const QModelIndex &parent) const
{
    BackgroundCategoriesItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = m_rootItem;
    else
        parentItem = static_cast<BackgroundCategoriesItem *>(parent.internalPointer());

    return parentItem->childCount();
}

void BackgroundCategoriesModel::populateSystem()
{
    QString path = QString("%1/wallpapers").arg(findDirectory(SystemThemesDirectory));
    QDirIterator it(path, QDir::Dirs | QDir::Readable | QDir::NoDotAndDotDot,
                    QDirIterator::FollowSymlinks);
    while (it.hasNext()) {
        QDir dir(it.next());
        if (dir.exists("metadata.desktop")) {
            QString file = dir.absoluteFilePath("metadata.desktop");
            VDesktopFile entry(file);

            BackgroundCategoriesItem *leaf = new BackgroundCategoriesItem(
                QIcon::fromTheme("folder"), entry.name(), m_systemItem);
            leaf->setDirectory(dir.path());
            m_systemItem->appendChild(leaf);
        }
    }
}

void BackgroundCategoriesModel::populateFolders()
{
}

#include "moc_backgroundcategoriesmodel.cpp"
