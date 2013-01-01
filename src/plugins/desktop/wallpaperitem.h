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
