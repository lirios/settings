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

#ifndef CATEGORYITEM_H
#define CATEGORYITEM_H

class CategoryItem
{
public:
    explicit CategoryItem(const QString &label, CategoryItem *parent = 0);
    CategoryItem(const QIcon &icon, const QString &label, CategoryItem *parent = 0);

    ~CategoryItem();

    void setDirectory(const QDir &dir);

    void appendChild(CategoryItem *item);

    CategoryItem *child(int row);

    int childCount() const;

    int row() const;

    QVariant data(int role);

    CategoryItem *parent() const;

private:
    QList<CategoryItem *> m_childItems;
    QIcon m_icon;
    QString m_label;
    QDir m_dir;
    CategoryItem *m_parentItem;
};

#endif // CATEGORYITEM_H
