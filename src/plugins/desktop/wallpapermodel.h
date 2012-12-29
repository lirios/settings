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

#ifndef WALLPAPERMODEL_H
#define WALLPAPERMODEL_H

#include <QAbstractListModel>
#include <QDir>
#include <QAtomicInt>

class BackgroundItem;
class WallpaperItem;

class WallpaperModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(AdditionalRoles)
public:
    enum AdditionalRoles {
        TypeRole = Qt::UserRole + 1,
        AuthorRole = Qt::UserRole + 2,
        ResolutionRole = Qt::UserRole + 3,
        AbsoluteContainerPathRole = Qt::UserRole + 4,
        AbsolutePathRole = Qt::UserRole + 5,
        AbsoluteFilePathRole = Qt::UserRole + 6
    };

    explicit WallpaperModel(QObject *parent = 0);
    ~WallpaperModel();

    void empty();

    QStringList paths() const;
    void addPath(const QString &path);

    QModelIndex indexOf(const QString &path) const;

    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual int rowCount(const QModelIndex &parent) const;

signals:
    void wallpapersAdded();

private:
    QStringList m_paths;
    QAtomicInt m_wallpapersCount;
    QList<BackgroundItem *> m_list;

    BackgroundItem *getItem(const QModelIndex &index) const;

private slots:
    void slotBackgroundFound(const QString &wallpaperDir,
                             const QString &desktopEntry, const QString &previewImage);
    void slotItemDataChanged(WallpaperItem *item);
};

#endif // WALLPAPERMODEL_H
