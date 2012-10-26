/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (c) 2011-2012 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:GPL3+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#include "preflet.h"
#include "ui_preflet.h"

Preflet::Preflet(QWidget *parent) :
    VPreferencesModule(parent),
    ui(new Ui::Preflet)
{
    ui->setupUi(this);

    ui->addButton->setIcon(QIcon::fromTheme("list-add"));
    ui->removeButton->setIcon(QIcon::fromTheme("list-remove"));
    ui->pictureButton->setIcon(QIcon::fromTheme("list-add"));
}

Preflet::~Preflet()
{
    delete ui;
}

QString Preflet::name() const
{
    return tr("User Accounts");
}

QString Preflet::comment() const
{
    return tr("Create new users, change users' details such as real name and " \
              "icon, manage administrators and groups.");
}

QString Preflet::iconName() const
{
    return "preferences-desktop-user";
}

QStringList Preflet::keywords() const
{
    return tr("user;account;password;administrator;real name").split(";");
}

VPreferencesModule::Category Preflet::category() const
{
    return VPreferencesModule::SystemCategory;
}

int Preflet::weight() const
{
    return 50;
}

#include "moc_preflet.cpp"
