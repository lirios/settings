/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (c) 2012 Pier Luigi Fiorini
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
    //static_cast<VFileItemDelegate *>(itemDelegate())->setMaximumSize(QSize(maxWidth, maxHeight));
}
