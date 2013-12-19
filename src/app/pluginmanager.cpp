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
#include <QtCore/QStandardPaths>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>

#include "pluginmanager.h"
#include "pluginmanager_p.h"
#include "plugin.h"
#include "prefletsmodel.h"
#include "xdgdesktopfile.h"

/*
 * PluginManagerPrivate
 */

PluginManagerPrivate::PluginManagerPrivate(PluginManager *manager)
    : q_ptr(manager)
{
}

PluginManagerPrivate::~PluginManagerPrivate()
{
    clear();
}

void PluginManagerPrivate::clear()
{
    QMapIterator<QString, QMap<QString, Plugin *> > iterator(plugins);
    while (iterator.hasNext()) {
        iterator.next();

        for (Plugin *plugin: iterator.value().values())
            delete plugin;
    }

    plugins.clear();
}

void PluginManagerPrivate::populate()
{
    Q_Q(PluginManager);

    // Clear plugins list
    clear();

    // Context for the plugins
    QQmlContext *context = QQmlEngine::contextForObject(q);

    // Search through the desktop entries
    QStringList directories =
            QStandardPaths::locateAll(QStandardPaths::GenericDataLocation,
                                      QStringLiteral("applications"),
                                      QStandardPaths::LocateDirectory);
    for (QString directory: directories) {
        QStringList filters;
        filters << QStringLiteral("hawaii-*-panel.desktop");

        QDir dir(directory);
        dir.setNameFilters(filters);

        for (QString fileName: dir.entryList()) {
            XdgDesktopFile entry;
            if (entry.load(dir.absoluteFilePath(fileName))) {
                // Skip desktop entries not meant for Hawaii
                QStringList onlyShowIn = entry.value(QStringLiteral("OnlyShowIn")).toString().split(";", QString::SkipEmptyParts);
                if (!onlyShowIn.contains(QStringLiteral("X-Hawaii")))
                    continue;

                // Module name
                QString moduleName = entry.value(QStringLiteral("X-Hawaii-ModuleName")).toString();

                // Append only if we haven't got any module with this name yet
                if (!plugins.contains(moduleName)) {
                    // Create a plugin instance
                    Plugin *plugin = new Plugin(entry, q);
                    QQmlEngine::setContextForObject(plugin, context);

                    // Load the plugin information
                    if (plugin->load()) {
                        // Insert plugin map
                        PluginMap &map = plugins[plugin->categoryName()];
                        map.insert(moduleName, plugin);
                    }
                }
            }
        }
    }
}

/*
 * PluginManager
 */

PluginManager::PluginManager(QObject *parent)
    : QObject(parent)
    , d_ptr(new PluginManagerPrivate(this))
{
}

PluginManager::~PluginManager()
{
    delete d_ptr;
}

PluginMap PluginManager::plugins(const QString &category) const
{
    Q_D(const PluginManager);
    return d->plugins.value(category);
}

QAbstractItemModel *PluginManager::itemModel(const QString &category)
{
    Q_D(PluginManager);

    PrefletsProxyModel *&actualModel = d->models[category];
    if (!actualModel) {
        PrefletsModel *model = new PrefletsModel(this);
        model->setPlugins(plugins(category));

        actualModel = new PrefletsProxyModel(this);
        actualModel->setSourceModel(model);
        actualModel->setFilter(category);
        actualModel->sort(0);
    }

    return actualModel;
}

QObject *PluginManager::getByName(const QString &name) const
{
    Q_D(const PluginManager);

    QMapIterator<QString, QMap<QString, Plugin *> > iterator(d->plugins);
    while (iterator.hasNext()) {
        iterator.next();

        if (iterator.value().contains(name))
            return iterator.value()[name];
    }

    return nullptr;
}

void PluginManager::classBegin()
{
    Q_D(PluginManager);
    d->populate();
}

void PluginManager::componentComplete()
{
}

#include "moc_pluginmanager.cpp"
