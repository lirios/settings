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

#ifndef WALLPAPERSMODEL_H
#define WALLPAPERSMODEL_H

#include <QtCore/QAbstractListModel>

#include "abstractitem.h"

class WallpapersModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(Roles)
public:
    enum Roles {
        FileNameRole = Qt::UserRole + 1,
        ThumbnailFileNameRole,
        ChangesThroughoutDayRole,
        HasMetadataRole,
        NameRole,
        AuthorNameRole,
        AuthorEmailRole,
        LicenseRole,
        ResolutionRole
    };

    explicit WallpapersModel(QObject *parent = 0);
    ~WallpapersModel();

    QHash<int, QByteArray> roleNames() const;

    int rowCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;

    Q_INVOKABLE AbstractItem *get(int index) const;

public Q_SLOTS:
    void addStandardPaths();
    void addUserPaths();

    void addFolder(const QString &path);
    void addWallpapersFolder(const QString &path);

private:
    QList<AbstractItem *> m_items;
};

#endif // WALLPAPERSMODEL_H
