/****************************************************************************
 * This file is part of Preferences.
 *
 * Copyright (c) 2011 Pier Luigi Fiorini
 *
 * Author(s):
 *	Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include "plugin.h"
#include "preflet.h"

UserAccountsPlugin::UserAccountsPlugin() :
    VPreferencesModulePlugin()
{
}

QString UserAccountsPlugin::name() const
{
    return tr("User Accounts");
}

QString UserAccountsPlugin::comment() const
{
    return tr("Create new users, change users' details such as real name and " \
              "icon, manage administrators and groups.");
}

QString UserAccountsPlugin::iconName() const
{
    return "preferences-desktop-user";
}

QStringList UserAccountsPlugin::keywords() const
{
    return tr("user;account;password;administrator;real name").split(";");
}

VPreferencesModulePlugin::Category UserAccountsPlugin::category() const
{
    return VPreferencesModulePlugin::SystemCategory;
}

int UserAccountsPlugin::weight() const
{
    return 50;
}

VPreferencesModule *UserAccountsPlugin::module() const
{
    return new Preflet();
}

Q_EXPORT_PLUGIN2(user_accounts, UserAccountsPlugin)

#include "moc_plugin.cpp"
