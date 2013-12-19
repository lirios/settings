/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2013 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
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

#include "prefletsproxymodel.h"
#include "prefletsmodel.h"

PrefletsProxyModel::PrefletsProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    setSourceModel(new PrefletsModel(this));
    setFilterRole(PrefletsModel::CategoryNameRole);
}

QString PrefletsProxyModel::filter() const
{
    return m_filter;
}

void PrefletsProxyModel::setFilter(const QString &val)
{
    if (m_filter != val) {
        m_filter = val;
        setFilterFixedString(m_filter);
        emit filterChanged();
    }
}

QQuickItem *PrefletsProxyModel::createItem(int row)
{
    PrefletsModel *model = qobject_cast<PrefletsModel *>(sourceModel());
    if (model)
        return model->createItem(mapToSource(index(row, 0)).row());
    return nullptr;
}

#include "moc_prefletsproxymodel.cpp"
