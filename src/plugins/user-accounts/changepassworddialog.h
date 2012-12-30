/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2012 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#ifndef CHANGEPASSWORDDIALOG_H
#define CHANGEPASSWORDDIALOG_H

#include <QDialog>

#include <VUserAccount>

namespace Ui
{
    class ChangePasswordDialog;
}

class ChangePasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePasswordDialog(QWidget *parent = 0);
    ~ChangePasswordDialog();

    void setUserAccount(VUserAccount *account);

private:
    Ui::ChangePasswordDialog *ui;
    VUserAccount *m_account;

private slots:
    void changeClicked();
};

#endif // CHANGEPASSWORDDIALOG_H
