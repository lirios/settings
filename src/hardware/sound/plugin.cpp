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

SoundPlugin::SoundPlugin() :
    VPreferencesModulePlugin()
{
}

QString SoundPlugin::name() const
{
    return tr("Sound");
}

QString SoundPlugin::comment() const
{
    return tr("Configure sound.");
}

QString SoundPlugin::iconName() const
{
    return "preferences-desktop-sound";
}

QStringList SoundPlugin::keywords() const
{
    return tr("sound;audio").split(";");
}

VPreferencesModulePlugin::Category SoundPlugin::category() const
{
    return VPreferencesModulePlugin::HardwareCategory;
}

int SoundPlugin::weight() const
{
    return 50;
}

VPreferencesModule *SoundPlugin::module() const
{
    return new Preflet();
}

Q_EXPORT_PLUGIN2(audio, SoundPlugin)

#include "moc_plugin.cpp"
