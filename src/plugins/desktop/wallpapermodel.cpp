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

#include "wallpapermodel.h"
#include "wallpaperfinder.h"
#include "wallpaperitem.h"

WallpaperModel::WallpaperModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_wallpapersCount(0)
{
}

WallpaperModel::~WallpaperModel()
{
    qDeleteAll(m_list);
}

void WallpaperModel::empty()
{
    if (m_list.size() > 0) {
        beginRemoveRows(QModelIndex(), 0, m_list.size() - 1);
        qDeleteAll(m_list);
        endRemoveRows();
    }
}

QStringList WallpaperModel::paths() const
{
    return m_paths;
}

void WallpaperModel::addPath(const QString &path)
{
    // Don't add a path we already know
    if (m_paths.contains(path))
        return;

    // Store it so that we won't enter the same path again
    m_paths.append(path);

    // Find backgrounds in another thread
    WallpaperFinder *finder = new WallpaperFinder(path, this);
    connect(finder, SIGNAL(backgroundFound(QString, QString, QString)),
            this, SLOT(slotBackgroundFound(QString, QString, QString)));
    finder->start(QThread::HighPriority);
}

QModelIndex WallpaperModel::indexOf(const QString &path) const
{
    for (int i = 0; i < m_list.size(); i++) {
        WallpaperItem *item = static_cast<WallpaperItem *>(m_list.at(i));
        if (!item)
            continue;

        if (item->data(AbsolutePathRole).toString() == QFileInfo(path).canonicalPath())
            return index(i);
    }

    return QModelIndex();
}

QVariant WallpaperModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    BackgroundItem *item = getItem(index);
    if (!item)
        return QVariant();
    return item->data(role);
}

int WallpaperModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_list.size();
}

BackgroundItem *WallpaperModel::getItem(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return m_list.at(index.row());
}

void WallpaperModel::slotBackgroundFound(const QString &wallpaperDir,
                                         const QString &desktopEntry,
                                         const QString &previewImage)
{
    // Increment a counter of added wallpaper items, once we retrieved
    // all its information the counter will be decremented and once
    // it reaches 0 we'll inform the world that the population is done
    m_wallpapersCount.ref();

    // Add the wallpaper
    beginInsertRows(QModelIndex(), m_list.size(), m_list.size());
    WallpaperItem *item = new WallpaperItem(QDir(wallpaperDir), desktopEntry, previewImage);
    connect(item, SIGNAL(dataChanged(WallpaperItem *)),
            this, SLOT(slotItemDataChanged(WallpaperItem *)));
    m_list.append(item);
    endInsertRows();
}

void WallpaperModel::slotItemDataChanged(WallpaperItem *item)
{
    for (int i = 0; i < m_list.size(); i++) {
        if (item->type() != BackgroundItem::WallpaperType)
            continue;

        WallpaperItem *reqItem = qobject_cast<WallpaperItem *>(item);
        WallpaperItem *curItem = qobject_cast<WallpaperItem *>(m_list.at(i));

        if (!reqItem || !curItem)
            continue;

        if (curItem->previewFileName() == reqItem->previewFileName()) {
            QModelIndex idx = index(i, 0);
            emit dataChanged(idx, idx);
            emit layoutAboutToBeChanged();
            changePersistentIndex(idx, idx);
            emit layoutChanged();
            break;
        }
    }

    // Decrement the counter so that we'll know how many paths are not yet added,
    // if it goes to 0 it means we populated the model with all the given wallpaper
    // paths and we fire a signal
    if (!m_wallpapersCount.deref())
        emit wallpapersAdded();
}

#include "moc_wallpapermodel.cpp"
