/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2013-2016 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include <QtAccountsService/AccountsManager>

#include "addaccountdialog.h"
#include "ui_addaccountdialog.h"

QT_USE_NAMESPACE_ACCOUNTSSERVICE

AddAccountDialog::AddAccountDialog(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::AddAccountDialog)
{
    ui->setupUi(this);

    ui->realName->setFocus();

    connect(ui->realName, SIGNAL(textEdited(QString)),
            this, SLOT(realNameEdited(QString)));
    connect(ui->buttonBox, SIGNAL(accepted()),
            this, SLOT(createAccount()));
}

AddAccountDialog::~AddAccountDialog()
{
    delete ui;
}

void AddAccountDialog::realNameEdited(const QString &text)
{
    ui->userName->setText(text.toLower()
                          .replace(QLatin1Char(' '), QStringLiteral("")));
}

void AddAccountDialog::createAccount()
{
    AccountsManager *manager = new AccountsManager();
    manager->createUser(ui->userName->text(), ui->realName->text(),
                        static_cast<UserAccount::AccountType>(ui->accountType->currentIndex()));
}

#include "moc_addaccountdialog.cpp"
