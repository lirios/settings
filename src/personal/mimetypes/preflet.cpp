/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (c) 2011-2012 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:GPL$
 *
 * System Preferences is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * System Preferences is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with System Preferences.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include "preflet.h"
#include "ui_mimetypespreflet.h"
#include "typesmodel.h"

Preflet::Preflet(QWidget *parent) :
    VPreferencesModule(parent),
    ui(new Ui::MimeTypesPreflet)
{
    ui->setupUi(this);

    // Set icons
    ui->addButton->setIcon(QIcon::fromTheme("list-add"));
    ui->removeButton->setIcon(QIcon::fromTheme("list-remove"));
    ui->addExtensionButton->setIcon(QIcon::fromTheme("list-add"));
    ui->removeExtensionButton->setIcon(QIcon::fromTheme("list-remove"));

    // Model
    m_model = new TypesModel(this);
    ui->treeView->setModel(m_model);
}

Preflet::~Preflet()
{
    delete ui;
    delete m_model;
}

QString Preflet::name() const
{
    return tr("MIME Types");
}

QString Preflet::comment() const
{
    return tr("Configure the association between MIME types and programs.");
}

QString Preflet::iconName() const
{
    return "preferences-desktop-wallpaper";
}

QStringList Preflet::keywords() const
{
    return tr("mime;types;association;program").split(";");
}

VPreferencesModule::Category Preflet::category() const
{
    return VPreferencesModule::PersonalCategory;
}

int Preflet::weight() const
{
    return 50;
}

#include "moc_preflet.cpp"
