/****************************************************************************
 * This file is part of Preferences.
 *
 * Copyright (c) 2011-2012 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Preferences is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Preferences is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Preferences.  If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include <QDir>
#include <QPluginLoader>
#include <QIcon>

#include <VStandardDirectories>

#include "categoriesmodel.h"

using namespace VStandardDirectories;

CategoriesModel::CategoriesModel(VPreferencesModulePlugin::Category category) :
    QAbstractListModel(),
    m_category(category)
{
    populate();
}

QVariant CategoriesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    VPreferencesModulePlugin *plugin = m_list.at(index.row());

    switch (role) {
        case Qt::DisplayRole:
            return plugin->name();
        case Qt::DecorationRole:
            return QIcon::fromTheme(plugin->iconName());
        case Qt::ToolTipRole:
            return plugin->comment();
    }

    return QVariant();
}

int CategoriesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_list.size();
}

VPreferencesModulePlugin *CategoriesModel::pluginAt(int row) const
{
    return m_list.at(row);
}

void CategoriesModel::populate()
{
    QStringList dirs;
    dirs << QString("%1/preferences").arg(findDirectory(SystemPluginsDirectory))
         << QString("%1/preferences").arg(findDirectory(CommonPluginsDirectory));
    foreach(QString dir, dirs) {
        QDir pluginsDir(dir);
        foreach(QString fileName, pluginsDir.entryList(QDir::Files)) {
            QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
            VPreferencesModulePlugin *plugin = qobject_cast<VPreferencesModulePlugin *>(loader.instance());
            if (plugin) {
                if (plugin->category() == category()) {
                    beginInsertRows(QModelIndex(), m_list.size(), m_list.size());
                    m_list.append(plugin);
                    endInsertRows();
                }
            }
        }
    }
}

#include "moc_categoriesmodel.cpp"
