/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2018 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include <QtGui/QColor>

#include "colorsmodel.h"

/*
 * ColorsModelPrivate
 */

class ColorsModelPrivate
{
public:
    ColorsModelPrivate();

    void addDefaultColors();

    QList<QColor> colors;
};

ColorsModelPrivate::ColorsModelPrivate()
{
    addDefaultColors();
}

void ColorsModelPrivate::addDefaultColors()
{
    colors.append(QColor(Qt::transparent));
    colors.append(QColor(0xdb, 0x5d, 0x33));
    colors.append(QColor(0x00, 0x80, 0x94));
    colors.append(QColor(0x5d, 0x47, 0x9d));
    colors.append(QColor(0xab, 0x28, 0x76));
    colors.append(QColor(0xfa, 0xd1, 0x66));
    colors.append(QColor(0x43, 0x77, 0x40));
    colors.append(QColor(0xd2, 0x72, 0xc4));
    colors.append(QColor(0xed, 0x91, 0x16));
    colors.append(QColor(0xff, 0x89, 0xa9));
    colors.append(QColor(0x7a, 0x8a, 0xa2));
    colors.append(QColor(0x88, 0x88, 0x88));
    colors.append(QColor(0x47, 0x5b, 0x52));
    colors.append(QColor(0x42, 0x52, 0x65));
    colors.append(QColor(0x7a, 0x63, 0x4b));
    colors.append(QColor(Qt::black));
}

/*
 * ColorsModel
 */

ColorsModel::ColorsModel(QObject *parent)
    : QAbstractListModel(parent)
    , d_ptr(new ColorsModelPrivate())
{
}

QHash<int, QByteArray> ColorsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ColorRole] = "color";
    return roles;
}

int ColorsModel::rowCount(const QModelIndex &parent) const
{
    Q_D(const ColorsModel);
    Q_UNUSED(parent);
    return d->colors.size();
}

QVariant ColorsModel::data(const QModelIndex &index, int role) const
{
    Q_D(const ColorsModel);

    if (!index.isValid())
        return QVariant();

    QColor color = d->colors.at(index.row());
    if (!color.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        return QString::number(color.value());
    case ColorRole:
        return QVariant::fromValue(color);
    default:
        break;
    }

    return QVariant();
}

QColor ColorsModel::get(int index) const
{
    Q_D(const ColorsModel);

    if (index < 0 || index > d->colors.size())
        return QColor();
    return d->colors.at(index);
}

void ColorsModel::addCustomColor(const QColor &color)
{
    Q_D(ColorsModel);

    beginInsertRows(QModelIndex(), d->colors.size(), d->colors.size());
    d->colors.append(color);
    endInsertRows();
}

void ColorsModel::clear()
{
    Q_D(ColorsModel);

    beginRemoveRows(QModelIndex(), 0, d->colors.size() - 1);
    d->colors.clear();
    endRemoveRows();

    beginInsertRows(QModelIndex(), d->colors.size(), d->colors.size());
    d->addDefaultColors();
    endInsertRows();
}

#include "moc_colorsmodel.cpp"
