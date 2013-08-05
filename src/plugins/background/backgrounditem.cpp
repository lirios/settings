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

#include <QtCore/QCryptographicHash>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtCore/QStandardPaths>
#include <QtGui/QImage>

#include "backgrounditem.h"
#include "wallpapersmodel.h"

BackgroundItem::BackgroundItem(const QString &fileName, QObject *parent)
    : AbstractItem(parent)
    , m_fileName(fileName)
{
    // Thumbnail file name is based on a hash of the source background file name
    QByteArray hash = QCryptographicHash::hash(fileName.toUtf8(),
                                               QCryptographicHash::Sha1);

    // Determine thumbnail file name
    m_thumbnailFileName = QString("%1/backgrounds/%2.jpg")
            .arg(QStandardPaths::writableLocation(QStandardPaths::CacheLocation))
            .arg(hash.toHex().constData());
    QFileInfo fileInfo(m_thumbnailFileName);
    fileInfo.dir().mkpath(".");

    // Check whether we already has a thumbnail file
    if (!fileInfo.exists()) {
        // Create a thumbnail, first resize 4 times the target size and
        // then resize again with a smooth transformation to the
        // target size (faster than resizing one time with a smooth
        // transformation)
        QImage img(m_fileName);
        QImage result = img.scaled(1600, 1000).scaled(400, 250,
                                                      Qt::IgnoreAspectRatio,
                                                      Qt::SmoothTransformation);

        // Save the thumbnail to the cache directory
        result.save(m_thumbnailFileName);
    }
}

QString BackgroundItem::fileName() const
{
    return m_fileName;
}

QVariant BackgroundItem::data(int role) const
{
    switch (role) {
    case WallpapersModel::FileNameRole:
        return m_fileName;
    case WallpapersModel::ThumbnailFileNameRole:
        return m_thumbnailFileName;
    case WallpapersModel::ChangesThroughoutDayRole:
        return false;
    case WallpapersModel::HasMetadataRole:
        return false;
    case Qt::DisplayRole:
    case WallpapersModel::NameRole:
        return m_fileName;
    }

    return QVariant();
}

#include "moc_backgrounditem.cpp"
