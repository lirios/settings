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

#ifndef LOCALEFILTERMODEL_H
#define LOCALEFILTERMODEL_H

#include <QSortFilterProxyModel>

class LocaleFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString filter READ filter WRITE setFilter NOTIFY filterStringChanged)
public:
    explicit LocaleFilterModel(QObject *parent = nullptr);

    QString filter() const;
    void setFilter(const QString &filter);

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

Q_SIGNALS:
    void filterStringChanged();

private:
    QString m_filter;
};

#endif // LOCALEFILTERMODEL_H