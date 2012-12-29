/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2011-2012 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
 *
 * $BEGIN_LICENSE:LGPL2.1+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include "preflet.h"
#include "ui_screenpreflet.h"

using namespace Hawaii::SystemPreferences;

Preflet::Preflet()
    : PreferencesModule()
    , ui(new Ui::ScreenPreflet)
{
    ui->setupUi(this);
}

Preflet::~Preflet()
{
    delete ui;
}

QString Preflet::name() const
{
    return tr("Brightness & Lock");
}

QString Preflet::comment() const
{
    return tr("Screen brightness and lock settings");
}

QString Preflet::iconName() const
{
    return "system-lock-screen";
}

QStringList Preflet::keywords() const
{
    return tr("brightness;lock;dim;blank;monitor").split(";");
}

PreferencesModule::Category Preflet::category() const
{
    return PreferencesModule::PersonalCategory;
}

#include "moc_preflet.cpp"
