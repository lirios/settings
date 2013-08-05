/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2013 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include <QtCore/QDirIterator>
#include <QtCore/QStandardPaths>
#include <QDebug>

#include "wallpapersmodel.h"
#include "backgrounditem.h"
#include "wallpaperitem.h"

WallpapersModel::WallpapersModel(QObject *parent)
    : QAbstractListModel(parent)
{
    QStringList paths;

    paths = QStandardPaths::locateAll(
                QStandardPaths::GenericDataLocation,
                "backgrounds", QStandardPaths::LocateDirectory);
    foreach (QString path, paths)
        addFolder(path);

    paths = QStandardPaths::locateAll(
                QStandardPaths::GenericDataLocation,
                "wallpapers", QStandardPaths::LocateDirectory);
    foreach (QString path, paths)
        addWallpapersFolder(path);
}

WallpapersModel::~WallpapersModel()
{
    qDeleteAll(m_items);
}

QHash<int, QByteArray> WallpapersModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[FileNameRole] = "fileName";
    roles[ThumbnailFileNameRole] = "thumbnailFileName";
    roles[ChangesThroughoutDayRole] = "changesThroughoutDay";
    roles[HasMetadataRole] = "hasMetadata";
    roles[NameRole] = "name";
    roles[AuthorNameRole] = "authorName";
    roles[AuthorEmailRole] = "authorEmail";
    roles[LicenseRole] = "license";
    roles[ResolutionRole] = "resolution";
    return roles;
}

int WallpapersModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_items.size();
}

QVariant WallpapersModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    AbstractItem *item = m_items.at(index.row());
    if (!item)
        return QVariant();

    return item->data(role);
}

AbstractItem *WallpapersModel::get(int index) const
{
    if (index < 0 || index > m_items.size())
        return 0;
    return m_items.at(index);
}

void WallpapersModel::addFolder(const QString &path)
{
    QStringList glob;
    glob << "*.png" << "*.jpg" << "*.jpeg" << "*.svg" << "*.svgz";

    QDir::Filters filters =
            QDir::NoDotAndDotDot | QDir::Readable | QDir::Files;
    QDirIterator::IteratorFlags flags =
            QDirIterator::Subdirectories | QDirIterator::FollowSymlinks;

    QDirIterator it(path, glob, filters, flags);
    while (it.hasNext()) {
        BackgroundItem *item = new BackgroundItem(it.next(), this);
        m_items.append(item);
    }
}

void WallpapersModel::addWallpapersFolder(const QString &path)
{
    QStringList glob;
    glob << "*.desktop";

    QDir::Filters filters =
            QDir::NoDotAndDotDot | QDir::Readable | QDir::Files;
    QDirIterator::IteratorFlags flags =
            QDirIterator::Subdirectories | QDirIterator::FollowSymlinks;

    QDirIterator it(path, glob, filters, flags);
    while (it.hasNext()) {
        WallpaperItem *item = new WallpaperItem(it.next(), this);
        m_items.append(item);
    }
}

#include "moc_wallpapersmodel.cpp"
