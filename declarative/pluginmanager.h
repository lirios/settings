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

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QtCore/QObject>
#include <QtQml/QQmlListProperty>

#include "plugin.h"

class PluginManagerPrivate;

class PluginManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString vendor READ vendor WRITE setVendor NOTIFY vendorChanged)
    Q_PROPERTY(QQmlListProperty<Plugin> personalPlugins READ personalPlugins NOTIFY personalPluginsChanged)
    Q_PROPERTY(QQmlListProperty<Plugin> hardwarePlugins READ hardwarePlugins NOTIFY hardwarePluginsChanged)
    Q_PROPERTY(QQmlListProperty<Plugin> systemPlugins READ systemPlugins NOTIFY systemPluginsChanged)
    Q_ENUMS(Roles)
public:
    enum Roles {
        TitleRole = Qt::UserRole,
        CommentRole,
        IconNameRole,
        CategoryRole,
        CategoryNameRole,
        MainScriptRole
    };

    PluginManager(QObject *parent = 0);
    ~PluginManager();

    QString vendor() const;
    void setVendor(const QString &vendor);

    QQmlListProperty<Plugin> personalPlugins();
    QQmlListProperty<Plugin> hardwarePlugins();
    QQmlListProperty<Plugin> systemPlugins();

Q_SIGNALS:
    void vendorChanged();
    void personalPluginsChanged();
    void hardwarePluginsChanged();
    void systemPluginsChanged();

public Q_SLOTS:
    void populate();

private:
    Q_DECLARE_PRIVATE(PluginManager)
    PluginManagerPrivate *const d_ptr;
};

#endif // PLUGINMANAGER_H
