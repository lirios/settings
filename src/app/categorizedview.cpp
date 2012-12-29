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

#include "categorizedview.h"

CategorizedView::CategorizedView(QWidget *parent)
    : VCategorizedView(parent)
{
    setWordWrap(true);
}

void CategorizedView::setModel(QAbstractItemModel *model)
{
    VCategorizedView::setModel(model);

    int maxWidth = -1, maxHeight = -1;
    for (int i = 0; i < model->rowCount(); ++i) {
        const QModelIndex index = model->index(i, modelColumn(), rootIndex());
        const QSize size = sizeHintForIndex(index);
        maxWidth = qMax(maxWidth, size.width());
        maxHeight = qMax(maxHeight, size.height());
    }

    setGridSize(QSize(maxWidth, maxHeight));
}
