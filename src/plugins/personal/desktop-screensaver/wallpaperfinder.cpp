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

#include <QSet>
#include <QImage>

#include "wallpaperfinder.h"

static bool sizeGreaterThan(const QSize &s1, const QSize &s2)
{
    return (s1.width() > s2.width()) || (s1.height() > s2.height());
}

/*
 * WallpaperFinder
 */

WallpaperFinder::WallpaperFinder(const QString &path, QObject *parent)
    : QThread(parent)
    , m_path(path)
{
}

WallpaperFinder::~WallpaperFinder()
{
    wait();
}

void WallpaperFinder::run()
{
    QSet<QString> suffixes;
    suffixes << "png" << "jpg" << "jpeg" << "svg" << "svgz";

    QDir dir(m_path);
    dir.setFilter(QDir::Dirs | QDir::Readable | QDir::NoDotAndDotDot);

    // Loop over all directories under the current category
    QFileInfoList list = dir.entryInfoList();
    foreach(QFileInfo fileInfo, list) {
        // Look for the metadata and preview files
        QDir subDir(fileInfo.absoluteFilePath());
        if (subDir.exists("metadata.desktop")) {
            subDir = QDir(fileInfo.absoluteFilePath() + "/contents");
            subDir.setNameFilters(QStringList() << "screenshot.*");
            subDir.setFilter(QDir::Files | QDir::Readable);
            foreach(QString previewFileName, subDir.entryList()) {
                // Can continue only if preview has the right extension and wallpaper set has images
                QFileInfo preview(subDir.absoluteFilePath(previewFileName));
                if (preview.exists() && suffixes.contains(preview.suffix().toLower())) {
                    QDir imagesDir(subDir.absolutePath() + "/images");
                    imagesDir.setFilter(QDir::Files | QDir::Readable | QDir::NoDotAndDotDot);

                    if (imagesDir.entryList().size() > 0)
                        emit backgroundFound(imagesDir.absolutePath(),
                                             fileInfo.absoluteFilePath() + "/metadata.desktop",
                                             preview.absoluteFilePath());
                }
            }
        }
    }
}

/*
 * WallpaperSizeFinder
 */

WallpaperSizeFinder::WallpaperSizeFinder(const QSize &resolution,
                                         const QDir &imagesDir, QObject *parent) :
    QThread(parent),
    m_resolution(resolution),
    m_imagesDir(imagesDir)
{
}

WallpaperSizeFinder::~WallpaperSizeFinder()
{
    wait();
}

void WallpaperSizeFinder::run()
{
    // Check for available resolutions
    QList<QSize> resolutions;
    QSet<QString> suffixes;
    suffixes << "png" << "jpg" << "jpeg" << "svg" << "svgz";
    QFileInfoList fileInfoList = m_imagesDir.entryInfoList(QDir::Files | QDir::Readable);
    foreach(QFileInfo fileInfo, fileInfoList) {
        if (suffixes.contains(fileInfo.suffix().toLower())) {
            // Save resolutions
            QImage image(fileInfo.absoluteFilePath());
            resolutions.append(image.size());
        }
    }

    // Sort resolutions list
    qSort(resolutions.begin(), resolutions.end(), sizeGreaterThan);

    // Find the resolution closest to the screen size
    QSize closestSize;
    for (int i = 0; i < resolutions.size(); i++) {
        QSize currentSize = resolutions.at(i);
        QSize size1(qAbs(currentSize.width() - m_resolution.width()),
                    qAbs(currentSize.height() - m_resolution.height()));
        QSize size2(qAbs(closestSize.width() - m_resolution.width()),
                    qAbs(closestSize.height() - m_resolution.height()));
        if ((size1.width() < size2.width()) && (size1.height() < size2.height()))
            closestSize = currentSize;
    }

    if (closestSize.isValid())
        emit sizeFound(closestSize);
}

#include "moc_wallpaperfinder.cpp"
