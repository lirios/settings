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

#include "categoriesmodel.h"

CategoriesModel::CategoriesModel(QObject *parent)
    : QAbstractListModel(parent)
{
    appendCategory(PreferencesModule::PersonalCategory);
    appendCategory(PreferencesModule::HardwareCategory);
    appendCategory(PreferencesModule::SystemCategory);
    appendCategory(PreferencesModule::OtherCategory);
}

QHash<int, QByteArray> CategoriesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TypeRole] = "type";
    roles[NameRole] = "name";
    roles[LabelRole] = "label";
    return roles;
}

QVariant CategoriesModel::data(const QModelIndex &index, int role) const
{
    CategoryItem item = m_categories.at(index.row());

    switch (role) {
    case Qt::DisplayRole:
    case LabelRole:
        return item.label;
    case TypeRole:
        return item.type;
    case NameRole:
        return item.name;
    default:
        break;
    }

    return QVariant();
}

int CategoriesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_categories.size();
}

void CategoriesModel::appendCategory(PreferencesModule::Category type)
{
    CategoryItem item;
    item.type = type;

    switch (type) {
    case PreferencesModule::PersonalCategory:
        item.name = QStringLiteral("personal");
        item.label = tr("Personal");
        break;
    case PreferencesModule::HardwareCategory:
        item.name = QStringLiteral("hardware");
        item.label = tr("Hardware");
        break;
    case PreferencesModule::SystemCategory:
        item.name = QStringLiteral("system");
        item.label = tr("System");
        break;
    case PreferencesModule::OtherCategory:
        item.name = QStringLiteral("other");
        item.label = tr("Other");
        break;
    }

    m_categories.append(item);
}

#include "moc_categoriesmodel.cpp"
