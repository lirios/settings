/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2012 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 * Copyright (C) 2009 Rafael Fernández López <ereslibre@kde.org>
 *
 * Author(s):
 *    Pier Luigi Fiorini
 *    Rafael Fernández López
 *
 * $BEGIN_LICENSE:GPL2+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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

#ifndef CATEGORYDRAWER_H
#define CATEGORYDRAWER_H

#include <VCategoryDrawer>

class CategoryDrawer : public VCategoryDrawer
{
public:
    explicit CategoryDrawer(VCategorizedView *view = 0);

    virtual void drawCategory(const QModelIndex &index, int sortRole,
                              const QStyleOption &option,
                              QPainter *painter) const;

    virtual int categoryHeight(const QModelIndex &index,
                               const QStyleOption &option) const;
};

#endif // CATEGORYDRAWER_H
