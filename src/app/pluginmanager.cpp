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
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>

#include <HawaiiShell/PluginLoader>

#include "pluginmanager.h"
#include "pluginmanager_p.h"
#include "plugin.h"
#include "prefletsmodel.h"

using namespace Hawaii::Shell;

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

    // Search preference plugins
    QStringList pluginList = PluginLoader::instance()->listPlugins(
                PluginLoader::PreferencesPlugin);
    for (QString plugin: pluginList) {
        // Load its package
        Package package = PluginLoader::instance()->loadPackage(
                    PluginLoader::PreferencesPlugin);
        package.setPath(plugin);

        if (!package.isValid())
            continue;

        // Append only if we haven't got any plugin with this name yet
        QString internalName = package.metadata().internalName();
        if (!plugins.contains(internalName)) {
            // Create a plugin instance
            Plugin *plugin = new Plugin(package, q);
            QQmlEngine::setContextForObject(plugin, context);

            // Insert the plugin map
            PluginMap &map = plugins[plugin->categoryName()];
            map.insert(internalName, plugin);
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
