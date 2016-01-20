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

#ifndef ADDACCOUNTDIALOG_H
#define ADDACCOUNTDIALOG_H

#include <QDialog>

namespace Ui {
    class AddAccountDialog;
}

class AddAccountDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddAccountDialog(QWidget *parent = 0);
    ~AddAccountDialog();

private:
    Ui::AddAccountDialog *ui;

private slots:
    void realNameEdited(const QString &text);
    void createAccount();
};

#endif // ADDACCOUNTDIALOG_H
