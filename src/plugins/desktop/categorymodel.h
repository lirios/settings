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

#ifndef BACKGROUNDCATEGORIESMODEL_H
#define BACKGROUNDCATEGORIESMODEL_H

#include <QAbstractListModel>

class CategoryItem;

class CategoryModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_ENUMS(AdditionalRoles)
public:
    enum AdditionalRoles {
        AbsolutePath = Qt::UserRole + 1
    };

    explicit CategoryModel(QObject *parent = 0);
    ~CategoryModel();

    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual int rowCount(const QModelIndex &parent) const;

private:
    CategoryItem *m_rootItem;
    CategoryItem *m_coatingsItem;
    CategoryItem *m_foldersItem;
    CategoryItem *m_colorsItem;

    void populateCoatings();
    void populateFolders();
    void populateColors();
};

#endif // BACKGROUNDCATEGORIESMODEL_H
