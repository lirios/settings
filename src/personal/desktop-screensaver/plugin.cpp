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

#include "plugin.h"
#include "preflet.h"

DesktopScreenSaverPlugin::DesktopScreenSaverPlugin() :
    VPreferencesModulePlugin()
{
}

QString DesktopScreenSaverPlugin::name() const
{
    return tr("Desktop & Screen Saver");
}

QString DesktopScreenSaverPlugin::comment() const
{
    return tr("Configure the desktop and the screen saver.");
}

QString DesktopScreenSaverPlugin::iconName() const
{
    return "preferences-desktop-wallpaper";
}

QStringList DesktopScreenSaverPlugin::keywords() const
{
    return tr("desktop;background;wallpaper;screen saver").split(";");
}

VPreferencesModulePlugin::Category DesktopScreenSaverPlugin::category() const
{
    return VPreferencesModulePlugin::PersonalCategory;
}

int DesktopScreenSaverPlugin::weight() const
{
    return 50;
}

VPreferencesModule *DesktopScreenSaverPlugin::module() const
{
    return new Preflet();
}

Q_EXPORT_PLUGIN2(desktop_screensaver, DesktopScreenSaverPlugin)

#include "moc_plugin.cpp"
