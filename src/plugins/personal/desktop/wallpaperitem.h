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

#ifndef WALLPAPERITEM_H
#define WALLPAPERITEM_H

#include <QDir>
#include <QPixmap>

#include <VDesktopFile>

#include "backgrounditem.h"

class WallpaperItem : public BackgroundItem
{
    Q_OBJECT
public:
    explicit WallpaperItem(const QDir &imagesDir, const QString &entry,
                           const QString &previewFileName);
    ~WallpaperItem();

    QString previewFileName() const;

    QVariant data(int role) const;

signals:
    void dataChanged(WallpaperItem *);

private:
    QDir m_imagesDir;
    VDesktopFile *m_entry;
    QString m_previewFileName;
    QPixmap m_pixmap;
    QSize m_size;

private slots:
    void slotSizeFound(const QSize &size);
};

#endif // WALLPAPERITEM_H
