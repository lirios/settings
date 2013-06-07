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

#include <QtCore/QDir>
#include <QtCore/QPluginLoader>
#include <QtGui/QIcon>

#include <Hawaii/SystemPreferences/PreferencesModulePlugin>

#include "prefletsmodel.h"
#include "cmakedirs.h"

PrefletsModel::PrefletsModel(QObject *parent)
    : QAbstractListModel(parent)
{
    QDir pluginsDir(QStringLiteral("%1/preferences").arg(INSTALL_PLUGINSDIR));
    foreach(QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        PreferencesModulePlugin *plugin = qobject_cast<PreferencesModulePlugin *>(loader.instance());
        if (!plugin)
            continue;

        foreach(QString key, plugin->keys()) {
            PreferencesModule *module = plugin->create(key);
            m_modules.append(module);
        }
    }
}

QHash<int, QByteArray> PrefletsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[IconNameRole] = "iconName";
    roles[CommentRole] = "comment";
    roles[CategoryRole] = "category";
    roles[CategoryNameRole] = "categoryName";
    return roles;
}

QVariant PrefletsModel::data(const QModelIndex &index, int role) const
{
    PreferencesModule *module = m_modules.at(index.row());

    switch (role) {
    case Qt::DecorationRole:
        return QIcon::fromTheme(module->iconName());
    case Qt::DisplayRole:
    case TitleRole:
        return module->name();
    case IconNameRole:
        return module->iconName();
    case CommentRole:
        return module->comment();
    case CategoryRole:
        return module->category();
    case CategoryNameRole: {
        switch (module->category()) {
        case PreferencesModule::PersonalCategory:
            return QStringLiteral("personal");
        case PreferencesModule::HardwareCategory:
            return QStringLiteral("hardware");
        case PreferencesModule::SystemCategory:
            return QStringLiteral("system");
        case PreferencesModule::OtherCategory:
            return QStringLiteral("other");
        }
    }
    default:
        break;
    }

    return QVariant();
}

int PrefletsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_modules.size();
}

#include "moc_prefletsmodel.cpp"
