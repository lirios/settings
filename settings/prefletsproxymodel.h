/****************************************************************************
 * This file is part of Hawaii.
 *
 * Copyright (C) 2013-2016 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#ifndef PREFLETSPROXYMODEL_H
#define PREFLETSPROXYMODEL_H

#include <QtCore/QSortFilterProxyModel>
#include <QtQuick/QQuickItem>

class PrefletsProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString filter READ filter WRITE setFilter NOTIFY filterChanged)
public:
    explicit PrefletsProxyModel(QObject *parent = 0);

    QString filter() const;
    void setFilter(const QString &val);

Q_SIGNALS:
    void filterChanged();

private:
    QString m_filter;
};

#endif // PREFLETSPROXYMODEL_H
