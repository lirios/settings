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

#ifndef WALLPAPERMODEL_H
#define WALLPAPERMODEL_H

#include <QAbstractListModel>
#include <QDir>

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
        AbsolutePathRole = Qt::UserRole + 4
    };

    explicit WallpaperModel(QObject *parent = 0);
    ~WallpaperModel();

    void empty();

    QStringList paths() const;
    void addPath(const QString &path);

    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual int rowCount(const QModelIndex &parent) const;

private:
    QStringList m_paths;
    QList<BackgroundItem *> m_list;

    BackgroundItem *getItem(const QModelIndex &index) const;

private slots:
    void slotBackgroundFound(const QString &wallpaperDir,
                             const QString &desktopEntry, const QString &previewImage);
    void slotItemDataChanged(WallpaperItem *item);
};

#endif // WALLPAPERMODEL_H
