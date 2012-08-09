/****************************************************************************
 * This file is part of Preferences.
 *
 * Copyright (c) 2011-2012 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Preferences is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Preferences is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Preferences.  If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#ifndef BACKGROUNDCATEGORIESMODEL_H
#define BACKGROUNDCATEGORIESMODEL_H

#include <QAbstractListModel>

class BackgroundCategoriesItem;

class BackgroundCategoriesModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_ENUMS(AdditionalRoles)
public:
    enum AdditionalRoles {
        AbsolutePath = Qt::UserRole + 1
    };

    explicit BackgroundCategoriesModel(QObject *parent = 0);
    ~BackgroundCategoriesModel();

    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual int rowCount(const QModelIndex &parent) const;

private:
    BackgroundCategoriesItem *m_rootItem;
    BackgroundCategoriesItem *m_systemItem;
    BackgroundCategoriesItem *m_foldersItem;

    void populateSystem();
    void populateFolders();
};

#endif // BACKGROUNDCATEGORIESMODEL_H
