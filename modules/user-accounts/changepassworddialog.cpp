/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2012-2016 Pier Luigi Fiorini
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

#include <QPushButton>

#include "changepassworddialog.h"
#include "ui_changepassworddialog.h"

ChangePasswordDialog::ChangePasswordDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChangePasswordDialog)
    , m_account(0)
{
    ui->setupUi(this);

    // Change button label
    QPushButton *button = ui->buttonBox->button(QDialogButtonBox::Ok);
    button->setText(tr("Change"));

    // Connect signals
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()),
            this, SIGNAL(rejected()));
    connect(button, SIGNAL(clicked()), this, SLOT(changeClicked()));
}

ChangePasswordDialog::~ChangePasswordDialog()
{
    delete ui;
}

void ChangePasswordDialog::setUserAccount(QtAddOn::AccountsService::UserAccount *account)
{
    m_account = account;

    ui->avatar->setPixmap(QPixmap(m_account->iconFileName()).scaled(32, 32));
    ui->realName->setText(m_account->realName());
    ui->strongnessLabel->setText(tr("Not good enough"));
    ui->action->setCurrentIndex(m_account->passwordMode());
    ui->hint->setText(m_account->passwordHint());
}

void ChangePasswordDialog::changeClicked()
{
    m_account->setPasswordMode((QtAddOn::AccountsService::UserAccount::PasswordMode) ui->action->currentIndex());

    accept();
}
