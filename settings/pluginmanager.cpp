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

#include <QtCore/QCoreApplication>
#include <QtCore/QTimer>
#include <QtCore/QStandardPaths>
#include <QtCore/QDir>
#include <QtGui/QIcon>
#include <QDebug>

#include "pluginmanager.h"
#include "pluginmanager_p.h"

/*
 * PluginManagerPrivate
 */

PluginManagerPrivate::PluginManagerPrivate(PluginManager *parent)
    : vendor(QStringLiteral("hawaii"))
    , populated(false)
    , populateTimer(new QTimer(parent))
{
}

/*
 * PluginManager
 */

PluginManager::PluginManager(QObject *parent)
    : QObject(parent)
    , d_ptr(new PluginManagerPrivate(this))
{
    Q_D(PluginManager);
    d->populateTimer->setInterval(0);
    d->populateTimer->setSingleShot(true);
    connect(d->populateTimer, SIGNAL(timeout()), this, SLOT(populate()));
    d->populateTimer->start();
}

PluginManager::~PluginManager()
{
    delete d_ptr;
}

QString PluginManager::vendor() const
{
    Q_D(const PluginManager);
    return d->vendor;
}

void PluginManager::setVendor(const QString &vendor)
{
    Q_D(PluginManager);

    if (d->vendor == vendor)
        return;

    d->vendor = vendor;
    Q_EMIT vendorChanged();

    qDeleteAll(d->personal);
    d->personal.clear();
    Q_EMIT personalPluginsChanged();

    qDeleteAll(d->hardware);
    d->hardware.clear();
    Q_EMIT hardwarePluginsChanged();

    qDeleteAll(d->system);
    d->system.clear();
    Q_EMIT systemPluginsChanged();

    d->populated = false;
    d->populateTimer->start();
}

QQmlListProperty<Plugin> PluginManager::personalPlugins()
{
    auto countFunc = [](QQmlListProperty<Plugin> *prop) {
        return static_cast<PluginManager *>(prop->object)->d_func()->personal.count();
    };
    auto atFunc = [](QQmlListProperty<Plugin> *prop, int index) {
        return static_cast<PluginManager *>(prop->object)->d_func()->personal.at(index);
    };
    return QQmlListProperty<Plugin>(this, 0, countFunc, atFunc);
}

QQmlListProperty<Plugin> PluginManager::hardwarePlugins()
{
    auto countFunc = [](QQmlListProperty<Plugin> *prop) {
        return static_cast<PluginManager *>(prop->object)->d_func()->hardware.count();
    };
    auto atFunc = [](QQmlListProperty<Plugin> *prop, int index) {
        return static_cast<PluginManager *>(prop->object)->d_func()->hardware.at(index);
    };
    return QQmlListProperty<Plugin>(this, 0, countFunc, atFunc);
}

QQmlListProperty<Plugin> PluginManager::systemPlugins()
{
    auto countFunc = [](QQmlListProperty<Plugin> *prop) {
        return static_cast<PluginManager *>(prop->object)->d_func()->system.count();
    };
    auto atFunc = [](QQmlListProperty<Plugin> *prop, int index) {
        return static_cast<PluginManager *>(prop->object)->d_func()->system.at(index);
    };
    return QQmlListProperty<Plugin>(this, 0, countFunc, atFunc);
}

void PluginManager::populate()
{
    Q_D(PluginManager);

    if (d->populated)
        return;

    QStringList list = QStandardPaths::locateAll(QStandardPaths::GenericDataLocation,
                                                 QStringLiteral("hawaii-settings/modules/%1").arg(d->vendor),
                                                 QStandardPaths::LocateDirectory);
    Q_FOREACH (const QString &location, list) {
        QDir dir(location);
        QStringList modules = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
        Q_FOREACH (const QString &module, modules) {
            QDir moduleDir(dir.absoluteFilePath(module));
            QStringList files = moduleDir.entryList(QDir::Files);
            Q_FOREACH (const QString &fileName, files) {
                if (fileName != QStringLiteral("metadata.desktop"))
                    continue;

                Plugin *plugin = new Plugin(moduleDir.absoluteFilePath(fileName));
                switch (plugin->category()) {
                case Plugin::PersonalCategory:
                    d->personal.append(plugin);
                    Q_EMIT personalPluginsChanged();
                    break;
                case Plugin::HardwareCategory:
                    d->hardware.append(plugin);
                    Q_EMIT hardwarePluginsChanged();
                    break;
                case Plugin::SystemCategory:
                    d->system.append(plugin);
                    Q_EMIT systemPluginsChanged();
                    break;
                default:
                    break;
                }
            }
        }
    }

    d->populated = true;
}

#include "moc_pluginmanager.cpp"
