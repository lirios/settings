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

#include "wallpaperitem.h"
#include "wallpapersmodel.h"
#include "xdgdesktopfile.h"

WallpaperItem::WallpaperItem(const QString &path, QObject *parent)
    : AbstractItem(parent)
    , m_dir(path)
{
    m_dir.cdUp();

    QStringList glob;
    glob << "screenshot.png" << "screenshot.jpg" << "screenshot.jpeg";

    QDir::Filters filters =
            QDir::NoDotAndDotDot | QDir::Readable | QDir::Files;
    QDirIterator::IteratorFlags flags = QDirIterator::FollowSymlinks;

    QDirIterator it(m_dir.absoluteFilePath("contents"), glob, filters, flags);
    while (it.hasNext()) {
        m_screenshotFileName = it.next();
        break;
    }

    m_metadata = XdgDesktopFileCache::getFile(m_dir.absoluteFilePath("metadata.desktop"));
}

WallpaperItem::~WallpaperItem()
{
}

QVariant WallpaperItem::data(int role) const
{
    switch (role) {
    case WallpapersModel::FileNameRole:
        return m_dir.absoluteFilePath("metadata.desktop");
    case WallpapersModel::ThumbnailFileNameRole:
        return m_screenshotFileName;
    case WallpapersModel::ChangesThroughoutDayRole:
        return false;
    case WallpapersModel::HasMetadataRole:
        return true;
    case Qt::DisplayRole:
    case WallpapersModel::NameRole:
        return m_metadata->name();
    case WallpapersModel::AuthorNameRole:
        return m_metadata->value("X-KDE-PluginInfo-Author");
    case WallpapersModel::AuthorEmailRole:
        return m_metadata->value("X-KDE-PluginInfo-Email");
    case WallpapersModel::LicenseRole:
        return m_metadata->value("X-KDE-PluginInfo-License");
    case WallpapersModel::ResolutionRole:
        // TODO: Detect resolution
        return "1920x1080";
    }

    return QVariant();
}

#include "moc_wallpaperitem.cpp"
