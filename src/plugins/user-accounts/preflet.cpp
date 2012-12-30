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

#include <QCoreApplication>
#include <QDebug>
#include <QSortFilterProxyModel>
#include <QStandardPaths>
#include <QTranslator>

#include <VUserAccount>

#include "preflet.h"
#include "ui_userspreflet.h"
#include "usersmodel.h"
#include "changepassworddialog.h"

using namespace Hawaii::SystemPreferences;

Preflet::Preflet()
    : PreferencesModule()
    , ui(new Ui::UsersPreflet)
    , m_translator(0)
{
    ui->setupUi(this);

    // Load translations
    loadTranslations();

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
    connect(ui->passwordButton, SIGNAL(clicked()),
            this, SLOT(changePasswordClicked()));
}

Preflet::~Preflet()
{
    delete ui;
    delete m_translator;
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

void Preflet::changeEvent(QEvent *event)
{
    switch (event->type()) {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        case QEvent::LocaleChange:
            loadTranslations();
            break;
        default:
            break;
    }

    QWidget::changeEvent(event);
}

void Preflet::loadTranslations()
{
    // Current locale
    const QString locale = QLocale::system().name();

    // Remove translation of the previously loaded locale
    if (m_translator) {
        QCoreApplication::instance()->removeTranslator(m_translator);
        delete m_translator;
    }

    // Load translations
    m_translator = new QTranslator(this);
    QString localeDir = QStandardPaths::locate(
                            QStandardPaths::GenericDataLocation,
                            QLatin1String("hawaii-system-preferences/plugins/user-accounts/translations"),
                            QStandardPaths::LocateDirectory);
    m_translator->load(locale, localeDir);
    QCoreApplication::instance()->installTranslator(m_translator);
}

void Preflet::userSelected(const QModelIndex &index)
{
    VUserAccount *account = m_model->userAccount(index);
    if (!account) {
        qWarning() << "Couldn't get selected user account!";
        m_currentIndex = QModelIndex();
        return;
    }

    m_currentIndex = index;

    ui->pictureButton->setIcon(QIcon(account->iconFileName()));
    ui->realNameButton->setText(account->realName());
    ui->realName->setText(ui->realNameButton->text());
    ui->accountType->setCurrentIndex(account->accountType());
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

void Preflet::changePasswordClicked()
{
    ChangePasswordDialog dialog(this);
    dialog.setUserAccount(m_model->userAccount(m_currentIndex));
    dialog.exec();
}

#include "moc_preflet.cpp"
