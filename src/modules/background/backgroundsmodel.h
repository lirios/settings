/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2018 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:GPL3+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#ifndef BACKGROUNDSMODEL_H
#define BACKGROUNDSMODEL_H

#include <QtCore/QAbstractListModel>

class BackgroundsModelPrivate;

class BackgroundsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(Roles)
public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        FileNameRole
    };

    explicit BackgroundsModel(QObject *parent = 0);

    QHash<int, QByteArray> roleNames() const;

    int rowCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;

    Q_INVOKABLE QString get(int index) const;

public Q_SLOTS:
    void addStandardPaths();
    void addUserPaths();

    void addFolder(const QString &path);

    void clear();

private:
    Q_DECLARE_PRIVATE(BackgroundsModel)
    BackgroundsModelPrivate *const d_ptr;
};

#endif // BACKGROUNDSMODEL_H
