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

#ifndef WALLPAPERFINDER_H
#define WALLPAPERFINDER_H

#include <QThread>
#include <QDir>
#include <QSize>

class WallpaperFinder : public QThread
{
    Q_OBJECT
public:
    explicit WallpaperFinder(const QString &path, QObject *parent = 0);
    ~WallpaperFinder();

    QString path() const {
        return m_path;
    }

signals:
    void backgroundFound(const QString &wallpaperDir,
                         const QString &desktopEntry, const QString &previewImage);

protected:
    void run();

private:
    QString m_path;
};

class WallpaperSizeFinder : public QThread
{
    Q_OBJECT
public:
    explicit WallpaperSizeFinder(const QSize &resolution,
                                 const QDir &imagesDir, QObject *parent = 0);
    ~WallpaperSizeFinder();

signals:
    void sizeFound(const QSize &size);

protected:
    void run();

private:
    QSize m_resolution;
    QDir m_imagesDir;
};

#endif // WALLPAPERFINDER_H
