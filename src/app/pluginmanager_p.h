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

#ifndef PLUGINMANAGER_P_H
#define PLUGINMANAGER_P_H

class Plugin;
class PluginManager;

class PluginManagerPrivate
{
    Q_DECLARE_PUBLIC(PluginManager)
public:
    PluginManagerPrivate(PluginManager *manager);
    ~PluginManagerPrivate();

    PluginsCollection plugins;
    ModelHash models;

    void clear();
    void populate();

protected:
    PluginManager *const q_ptr;
};

#endif // PLUGINMANAGER_P_H
