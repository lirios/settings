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

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QPluginLoader>
#include <QtGui/QIcon>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>

#include <Hawaii/SystemPreferences/PreferencesModulePlugin>

#include "prefletsmodel.h"
#include "prefletsmodel_p.h"
#include "plugin.h"
#include "cmakedirs.h"

/*
 * PrefletsModelPrivate
 */

PrefletsModelPrivate::PrefletsModelPrivate()
{
}

/*
 * PrefletsModel
 */

PrefletsModel::PrefletsModel(QObject *parent)
    : QAbstractListModel(parent)
    , d_ptr(new PrefletsModelPrivate())
{
}

QHash<int, QByteArray> PrefletsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[IconNameRole] = "iconName";
    roles[CommentRole] = "comment";
    roles[CategoryRole] = "category";
    roles[CategoryNameRole] = "categoryName";
    roles[ItemRole] = "item";
    return roles;
}

QVariant PrefletsModel::data(const QModelIndex &index, int role) const
{
    Q_D(const PrefletsModel);

    if (index.row() >= d->plugins.size())
        return QVariant();

    const Plugin *plugin = d->plugins.at(index.row());

    switch (role) {
    case Qt::DecorationRole:
        return QIcon::fromTheme(plugin->iconName());
    case Qt::DisplayRole:
    case TitleRole:
        return plugin->title();
    case IconNameRole:
        return plugin->iconName();
    case CommentRole:
        return plugin->comment();
    case CategoryRole:
        return plugin->category();
    case CategoryNameRole:
        return plugin->categoryName();
    case ItemRole:
        return QVariant::fromValue(const_cast<Plugin *>(plugin)->item());
    default:
        break;
    }

    return QVariant();
}

int PrefletsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    Q_D(const PrefletsModel);
    return d->plugins.size();
}

void PrefletsModel::setPlugins(const PluginMap &plugins)
{
    Q_D(PrefletsModel);

    beginResetModel();
    d->plugins.clear();
    for (Plugin *plugin: plugins.values())
        d->plugins.append(plugin);
    endResetModel();
}

#include "moc_prefletsmodel.cpp"
