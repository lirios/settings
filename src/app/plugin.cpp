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

#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>

#include "plugin.h"
#include "plugin_p.h"

using namespace Hawaii::SystemPreferences;

/*
 * PluginPrivate
 */

PluginPrivate::PluginPrivate(Plugin *plugin)
    : loader(new QPluginLoader())
    , plugin(nullptr)
    , module(nullptr)
    , component(nullptr)
    , item(nullptr)
    , q_ptr(plugin)
{
}

PluginPrivate::~PluginPrivate()
{
    delete component;
    delete module;
    delete plugin;
    delete loader;
}

void PluginPrivate::load()
{
    Q_Q(Plugin);

    QString fileName = entry.value(QStringLiteral("X-Hawaii-ModulePath")).toString();
    loader->setFileName(fileName);

    plugin = qobject_cast<PreferencesModulePlugin *>(loader->instance());
    if (!plugin) {
        qWarning() << "Couldn't load" << fileName << loader->errorString();
        return;
    }

    QString moduleName = entry.value(QStringLiteral("X-Hawaii-ModuleName")).toString();
    module = plugin->create(moduleName);
    if (!module) {
        delete plugin;
        plugin = nullptr;
        return;
    }

    QQmlContext *context = QQmlEngine::contextForObject(q);
    component = module->createComponent(context->engine(), q);
    if (component->isError()) {
        qDebug() << "Errors loading" << moduleName;
        for (QQmlError error: component->errors())
            qWarning("\t\%s", qPrintable(error.toString()));
    }
}

/*
 * Plugin
 */

Plugin::Plugin(const XdgDesktopFile &entry, QObject *parent)
    : QObject(parent)
    , d_ptr(new PluginPrivate(this))
{
    Q_D(Plugin);
    d->entry = entry;
}

Plugin::~Plugin()
{
    delete d_ptr;
}

bool Plugin::load()
{
    Q_D(Plugin);
    d->load();
    return d->plugin != nullptr;
}

Plugin::Category Plugin::category() const
{
    Q_D(const Plugin);

    QStringList categories = d->entry.value("Categories").toString().split(";", QString::SkipEmptyParts);
    for (QString categoryString: categories) {
        if (categoryString == QStringLiteral("X-Hawaii-PersonalSettings"))
            return Plugin::PersonalCategory;
        if (categoryString == QStringLiteral("HardwareSettings"))
            return Plugin::HardwareCategory;
        if (categoryString == QStringLiteral("X-Hawaii-SystemSettings"))
            return Plugin::SystemCategory;
    }

    return Plugin::NoCategory;
}

QString Plugin::categoryName() const
{
    switch (category()) {
    case Plugin::PersonalCategory:
        return QStringLiteral("personal");
    case Plugin::HardwareCategory:
        return QStringLiteral("hardware");
    case Plugin::SystemCategory:
        return QStringLiteral("system");
    default:
        break;
    }

    return QString();
}

QString Plugin::name() const
{
    Q_D(const Plugin);
    return d->entry.value("X-Hawaii-ModuleName").toString();
}

QString Plugin::title() const
{
    Q_D(const Plugin);
    return d->entry.localizedValue("Name").toString();
}

QString Plugin::comment() const
{
    Q_D(const Plugin);
    return d->entry.localizedValue("Comment").toString();
}

QString Plugin::iconName() const
{
    Q_D(const Plugin);
    return d->entry.value("Icon").toString();
}

QStringList Plugin::keywords() const
{
    Q_D(const Plugin);
    return d->entry.localizedValue("Keywords").toString().split(";", QString::SkipEmptyParts);
}

QStringList Plugin::formFactors() const
{
    Q_D(const Plugin);
    return d->entry.value("X-Hawaii-Settings-Panel/FormFactors").toString().split(";", QString::SkipEmptyParts);
}

QQmlComponent *Plugin::component() const
{
    Q_D(const Plugin);
    return d->component;
}

QQuickItem *Plugin::item()
{
    Q_D(Plugin);

    if (!d->plugin)
        return nullptr;

    if (!d->item)
        d->item = qobject_cast<QQuickItem *>(d->component->create());
    return d->item;
}

#include "moc_plugin.cpp"
