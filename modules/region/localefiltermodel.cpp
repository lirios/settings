/****************************************************************************
 * This file is part of Liri.
 *
 * Copyright (C) 2019 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include "localefiltermodel.h"
#include "localemodel.h"

LocaleFilterModel::LocaleFilterModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    setSourceModel(new LocaleModel(this));
}

QString LocaleFilterModel::filter() const
{
    return m_filter;
}

void LocaleFilterModel::setFilter(const QString &filter)
{
    if (m_filter == filter)
        return;

    m_filter = filter;
    Q_EMIT filterChanged();

    invalidate();
}

bool LocaleFilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (!sourceModel())
        return false;

    QModelIndex index = sourceModel()->index(source_row, 0, source_parent);
    if (index.isValid()) {
        QVariant language = index.data(LocaleModel::Language);
        if (language.isValid()) {
            if (language.toString().contains(m_filter, Qt::CaseInsensitive))
                return true;
        }

        QVariant country = index.data(LocaleModel::Country);
        if (country.isValid()) {
            if (country.toString().contains(m_filter, Qt::CaseInsensitive))
                return true;
        }
    }

    return false;
}
