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

#include <QDebug>
#include <QSortFilterProxyModel>

#include <VUserAccount>

#include "preflet.h"
#include "ui_userspreflet.h"
#include "usersmodel.h"

using namespace Hawaii::SystemPreferences;

Preflet::Preflet()
    : PreferencesModule()
    , ui(new Ui::UsersPreflet)
{
    ui->setupUi(this);

    // Setup icons
    ui->addButton->setIcon(QIcon::fromTheme("list-add-symbolic"));
    ui->removeButton->setIcon(QIcon::fromTheme("list-remove-symbolic"));

    // Setup users list
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    m_model = new UsersModel(this);
    proxyModel->setSourceModel(m_model);
    proxyModel->setSortRole(UsersModel::UserIdRole);
    ui->listView->setModel(proxyModel);

    // Connect signals
    connect(ui->listView, SIGNAL(clicked(QModelIndex)),
            ui->listView, SIGNAL(activated(QModelIndex)));
    connect(ui->listView, SIGNAL(clicked(QModelIndex)),
            this, SLOT(userSelected(QModelIndex)));
    connect(ui->realNameButton, SIGNAL(clicked()),
            this, SLOT(realNameClicked()));
    connect(ui->realName, SIGNAL(returnPressed()),
            this, SLOT(realNameChanged()));
    connect(ui->realName, SIGNAL(editingFinished()),
            this, SLOT(realNameEditingFinished()));
}

Preflet::~Preflet()
{
    delete ui;
}

QString Preflet::name() const
{
    return tr("Users");
}

QString Preflet::comment() const
{
    return tr("Create new users, change users' details such as real name and " \
              "icon, manage administrators and groups");
}

QString Preflet::iconName() const
{
    return QLatin1String("system-users");
}

QStringList Preflet::keywords() const
{
    return tr("user;login;account;face;password;administrator;name;fingerprint").split(";");
}

PreferencesModule::Category Preflet::category() const
{
    return PreferencesModule::SystemCategory;
}

void Preflet::userSelected(const QModelIndex &index)
{
    m_currentIndex = index;

    QString avatarFileName = m_model->data(index, UsersModel::IconFileNameRole).toString();
    ui->pictureButton->setIcon(QIcon(avatarFileName));

    ui->realNameButton->setText(m_model->data(index, UsersModel::RealNameRole).toString());
    ui->realName->setText(ui->realNameButton->text());

    int accountType = m_model->data(index, UsersModel::AccountTypeRole).toInt();
    switch (accountType) {
    case VUserAccount::StandardAccountType:
        ui->accountTypeLabel->setText(tr("Standard"));
        break;
    case VUserAccount::AdministratorAccountType:
        ui->accountTypeLabel->setText(tr("Administrator"));
        break;
    default:
        break;
    }
}

void Preflet::realNameClicked()
{
    if (ui->realNameStack->currentIndex() == 0) {
        ui->realNameStack->setCurrentIndex(1);
        ui->realName->setFocus();
    } else
        ui->realNameStack->setCurrentIndex(0);
}

void Preflet::realNameChanged()
{
    if (m_currentIndex.isValid()) {
        QString name = ui->realName->text();
        m_model->setData(m_currentIndex, QVariant(name), UsersModel::RealNameRole);
        ui->realNameButton->setText(name);
    }
}

void Preflet::realNameEditingFinished()
{
    ui->realNameStack->setCurrentIndex(0);
}

#include "moc_preflet.cpp"
