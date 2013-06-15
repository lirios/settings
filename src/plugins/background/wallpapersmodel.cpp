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

WallpapersModel::WallpapersModel(QObject *parent)
    : QAbstractListModel(parent)
{
    QStringList subfolders;
    subfolders << "backgrounds" << "wallpapers";

    foreach (QString subfolder, subfolders) {
        QStringList paths =
                QStandardPaths::locateAll(
                    QStandardPaths::GenericDataLocation,
                    subfolder, QStandardPaths::LocateDirectory);
        foreach (QString path, paths)
            addFolder(path);
    }
}

WallpapersModel::~WallpapersModel()
{
    qDeleteAll(m_items);
}

QHash<int, QByteArray> WallpapersModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[FileNameRole] = "fileName";
    roles[MiniatureFileNameRole] = "miniatureFileName";
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

    WallpaperItem *item = m_items.at(index.row());
    if (!item)
        return QVariant();

    return item->data(role);
}

void WallpapersModel::addFolder(const QString &path)
{
    QStringList glob;
    glob << "*.png" << "*.jpg" << "*.jpeg" << "*.svg" << "*.svgz";

    QDir::Filters filters =
            QDir::NoDotAndDotDot | QDir::Readable | QDir::Files;
    QDirIterator::IteratorFlags flags =
            QDirIterator::Subdirectories | QDirIterator::FollowSymlinks;

    qDebug() << "path" << path;
    QDirIterator it(path, glob, filters, flags);
    while (it.hasNext()) {
        WallpaperItem *item = new WallpaperItem(it.next(), this);
        m_items.append(item);
    }
}

#include "moc_wallpapersmodel.cpp"
