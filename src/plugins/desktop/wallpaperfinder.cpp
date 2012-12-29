/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2011-2012 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include <QDir>
#include <QSet>

#include "wallpaperfinder.h"

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

#include "moc_wallpaperfinder.cpp"
