/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (c) 2011-2012 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include <QApplication>
#include <QDesktopWidget>

#include "wallpaperitem.h"
#include "wallpapersizefinder.h"
#include "wallpapermodel.h"

WallpaperItem::WallpaperItem(const QDir &imagesDir,
                             const QString &entry,
                             const QString &previewFileName)
    : BackgroundItem(BackgroundItem::WallpaperType)
    , m_previewFileName(previewFileName)
{
    // Calculate aspect ratio
    QSize screenSize = qApp->desktop()->size();
    qreal ratio = qreal(screenSize.width() / screenSize.height());

    // Load metadata and preview image scaled down (preserving screen aspect ratio)
    m_entry = new VDesktopFile(entry);
    m_pixmap.load(previewFileName);
    m_pixmap = m_pixmap.scaled(QSize(128 * ratio, 128));

    // Find best size
    WallpaperSizeFinder *finder = new WallpaperSizeFinder(screenSize, imagesDir, this);
    connect(finder, SIGNAL(sizeFound(QSize)),
            this, SLOT(slotSizeFound(QSize)));
    finder->start(QThread::HighestPriority);
}

WallpaperItem::~WallpaperItem()
{
    delete m_entry;
}

QString WallpaperItem::previewFileName() const
{
    return m_previewFileName;
}

QVariant WallpaperItem::data(int role) const
{
    switch (role) {
        case Qt::DisplayRole:
            return m_entry->name();
        case Qt::DecorationRole:
            return QVariant::fromValue(m_pixmap);
        case Qt::ToolTipRole:
            return m_entry->comment();
        case WallpaperModel::AuthorRole:
            return m_entry->value("X-Hawaii-PluginInfo-Author");
        case WallpaperModel::ResolutionRole:
            if (m_size.isValid())
                return QString("%1x%2").arg(m_size.width()).arg(m_size.height());
            return QString();
    }

    return QVariant();
}

void WallpaperItem::slotSizeFound(const QSize &size)
{
    m_size = size;
    emit dataChanged(this);
}

#include "moc_wallpaperitem.cpp"
