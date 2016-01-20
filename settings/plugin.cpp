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

#include <QtCore/QDir>
#include <QtCore/QFileInfo>

#include "plugin.h"
#include "xdgdesktopfile.h"

/*
 * PluginPrivate
 */

class PluginPrivate
{
public:
    PluginPrivate(const QString &fileName)
    {
        entry = XdgDesktopFileCache::getFile(fileName);
    }

    ~PluginPrivate()
    {
        delete entry;
    }

    XdgDesktopFile *entry;
    Plugin::Category category;
    QString categoryName;
};

/*
 * Plugin
 */

Plugin::Plugin(const QString &fileName, QObject *parent)
    : QObject(parent)
    , d_ptr(new PluginPrivate(fileName))
{
    Q_D(Plugin);
    d->categoryName = d->entry->value(QStringLiteral("X-Hawaii-SystemPreferences-Category"),
                                      QStringLiteral("personal")).toString();
    if (d->categoryName == QStringLiteral("personal"))
        d->category = Plugin::PersonalCategory;
    else if (d->categoryName == QStringLiteral("hardware"))
        d->category = Plugin::HardwareCategory;
    else if (d->categoryName == QStringLiteral("system"))
        d->category = Plugin::SystemCategory;
    else
        d->category = Plugin::NoCategory;
}

Plugin::~Plugin()
{
    delete d_ptr;
}

Plugin::Category Plugin::category() const
{
    Q_D(const Plugin);
    return d->category;
}

QString Plugin::categoryName() const
{
    Q_D(const Plugin);
    return d->categoryName;
}

QString Plugin::name() const
{
    Q_D(const Plugin);
    return d->entry->value(QStringLiteral("X-Hawaii-SystemPreferences-InternalName")).toString();
}

QString Plugin::title() const
{
    Q_D(const Plugin);
    return d->entry->value(QStringLiteral("Name")).toString();
}

QString Plugin::comment() const
{
    Q_D(const Plugin);
    return d->entry->value(QStringLiteral("Comment")).toString();
}

QString Plugin::iconName() const
{
    Q_D(const Plugin);
    return d->entry->value(QStringLiteral("Icon")).toString();
}

QStringList Plugin::keywords() const
{
    Q_D(const Plugin);
    return d->entry->value(QStringLiteral("Keywords")).toStringList();
}

QUrl Plugin::mainScript() const
{
    Q_D(const Plugin);

    QFileInfo info(d->entry->fileName());
    return QUrl::fromLocalFile(info.absoluteDir().absoluteFilePath(QStringLiteral("Preflet.qml")));
}

#include "moc_plugin.cpp"
