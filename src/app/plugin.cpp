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

#include <HawaiiShell/QmlObject>

#include "plugin.h"

using namespace Hawaii::Shell;

/*
 * PluginPrivate
 */

class PluginPrivate
{
public:
    PluginPrivate()
        : qmlObject(nullptr)
    {
    }

    Package package;
    QmlObject *qmlObject;
};

/*
 * Plugin
 */

Plugin::Plugin(Package package, QObject *parent)
    : QObject(parent)
    , d_ptr(new PluginPrivate())
{
    Q_D(Plugin);
    d->package = package;
    d->qmlObject = new QmlObject(this);
    d->qmlObject->setInitializationDelayed(true);
    d->qmlObject->setSource(mainScript());
    d->qmlObject->completeInitialization();
}

Plugin::~Plugin()
{
    delete d_ptr;
}

Plugin::Category Plugin::category() const
{
    Q_D(const Plugin);

    QVariantMap map = d->package.metadata().value(QStringLiteral("HawaiiSystemPreferences")).toMap();

    QString category = map.value(QStringLiteral("Category")).toString();
    if (category == QStringLiteral("Personal"))
        return Plugin::PersonalCategory;
    else if (category == QStringLiteral("Hardware"))
        return Plugin::HardwareCategory;
    else if (category == QStringLiteral("System"))
        return Plugin::SystemCategory;

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
    return d->package.metadata().internalName();
}

QString Plugin::title() const
{
    Q_D(const Plugin);
    return d->package.metadata().name();
}

QString Plugin::comment() const
{
    Q_D(const Plugin);
    return d->package.metadata().comment();
}

QString Plugin::iconName() const
{
    Q_D(const Plugin);
    return d->package.metadata().iconName();
}

QStringList Plugin::keywords() const
{
    Q_D(const Plugin);
    return d->package.metadata().keywords();
}

QStringList Plugin::platformHints() const
{
    Q_D(const Plugin);

    QVariantMap map = d->package.metadata().value(QStringLiteral("HawaiiSystemPreferences")).toMap();
    return map.value(QStringLiteral("PlatformHints")).toStringList();
}

QUrl Plugin::mainScript() const
{
    Q_D(const Plugin);
    QString path = d->package.filePath(nullptr, d->package.metadata().mainScript());
    return QUrl::fromLocalFile(path);
}

QQuickItem *Plugin::item()
{
    Q_D(Plugin);
    return qobject_cast<QQuickItem *>(d->qmlObject->rootObject());
}

#include "moc_plugin.cpp"
