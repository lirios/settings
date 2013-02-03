/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2011-2013 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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
#include <QFileInfo>
#include <QMessageBox>
#include <QPushButton>
#include <QSortFilterProxyModel>
#include <QStandardPaths>
#include <QTranslator>

#include <QtAccountsService/AccountsManager>
#include <QtAccountsService/UserAccount>

#include "preflet.h"
#include "ui_userspreflet.h"
#include "useritemdelegate.h"
#include "addaccountdialog.h"
#include "changepassworddialog.h"

using namespace Hawaii::SystemPreferences;

Preflet::Preflet()
    : PreferencesModule()
    , ui(new Ui::UsersPreflet)
    , m_translator(0)
    , m_currentAccount(0)
{
    ui->setupUi(this);

    // Load translations
    loadTranslations();

    // Setup users list
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    m_model = new UsersModel(this);
    proxyModel->setSourceModel(m_model);
    proxyModel->setSortRole(UsersModel::UserIdRole);
    ui->listView->setModel(proxyModel);
    ui->listView->setItemDelegate(new UserItemDelegate(this));

    // Connect signals
    connect(ui->listView, SIGNAL(clicked(QModelIndex)),
            ui->listView, SIGNAL(activated(QModelIndex)));
    connect(ui->listView, SIGNAL(clicked(QModelIndex)),
            this, SLOT(userSelected(QModelIndex)));
    connect(m_model, SIGNAL(rowsRemoved(QModelIndex,int,int)),
            this, SLOT(modelRowsRemoved(QModelIndex,int,int)));
    connect(ui->realNameButton, SIGNAL(clicked()),
            this, SLOT(realNameClicked()));
    connect(ui->realName, SIGNAL(returnPressed()),
            this, SLOT(realNameChanged()));
    connect(ui->realName, SIGNAL(editingFinished()),
            this, SLOT(realNameEditingFinished()));
    connect(ui->passwordButton, SIGNAL(clicked()),
            this, SLOT(changePasswordClicked()));
    connect(ui->autologin, SIGNAL(clicked(bool)),
            this, SLOT(toggleAutologin(bool)));
    connect(ui->addButton, SIGNAL(clicked()),
            this, SLOT(addUser()));
    connect(ui->removeButton, SIGNAL(clicked()),
            this, SLOT(removeUser()));
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

bool Preflet::requiresAdministrativePrivileges() const
{
    return true;
}

QString Preflet::administrativeActionId() const
{
    return QStringLiteral("org.freedesktop.accounts.user-administration");
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

void Preflet::setUiEnabled(bool enabled)
{
    ui->pictureButton->setEnabled(enabled);
    ui->realNameStack->setEnabled(enabled);
    ui->accountTypeLabel->setEnabled(enabled);
    ui->languageLabel->setEnabled(enabled);
    ui->accountType->setEnabled(enabled);
    ui->language->setEnabled(enabled);
    ui->groupBox->setEnabled(enabled);
}

void Preflet::clearUserSelection()
{
    ui->listView->clearSelection();
    ui->pictureButton->setIcon(QIcon());
    ui->realNameButton->setText(QStringLiteral(""));
    ui->realName->setText(QStringLiteral(""));
    ui->accountType->setCurrentIndex(0);
    ui->language->setCurrentIndex(0);
    ui->passwordButton->setText(QStringLiteral(""));
    setUiEnabled(false);
}

void Preflet::populateUi(UserAccount *account)
{
    // Change password button text, if the account is not locked set it to
    // some circles to fake a password field
    if (account->isLocked())
        ui->passwordButton->setText(tr("Account disabled"));
    else
        ui->passwordButton->setText(QStringLiteral("●●●●"));

    // Set picture and other information
    QFileInfo fileInfo(account->iconFileName());
    QIcon userIcon;
    if (fileInfo.exists())
        userIcon = QIcon(account->iconFileName());
    else
        userIcon = QIcon::fromTheme("avatar-default");
    ui->pictureButton->setIcon(userIcon);
    ui->realNameButton->setText(account->realName());
    ui->realName->setText(ui->realNameButton->text());
    ui->accountType->setCurrentIndex((int)account->accountType());
    ui->autologin->setChecked(account->automaticLogin());
}

void Preflet::userSelected(const QModelIndex &index)
{
    // Currently selected account
    UserAccount *account = m_model->userAccount(index);
    if (!account) {
        qWarning() << "Couldn't get selected user account!";
        m_currentIndex = QModelIndex();
        m_currentAccount = 0;
        return;
    }

    // Save current index and account
    m_currentIndex = index;
    m_currentAccount = account;

    // Enable and populate UI
    setUiEnabled(true);
    populateUi(account);

    // Keep in sync
    connect(account, SIGNAL(accountChanged()), this, SLOT(accountChanged()));

    // Add and remove buttons can now be enabled
    ui->addButton->setEnabled(true);
    ui->removeButton->setEnabled(true);
}

void Preflet::modelRowsRemoved(const QModelIndex &parent, int first, int last)
{
    Q_UNUSED(parent);

    // When an item is removed we clear the selection
    if (m_currentIndex.isValid() &&
            m_currentIndex.row() >= first &&
            m_currentIndex.row() <= last)
        clearUserSelection();
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

void Preflet::toggleAutologin(bool enabled)
{
    if (m_currentAccount)
        m_currentAccount->setAutomaticLogin(enabled);
}

void Preflet::addUser()
{
    AddAccountDialog dialog(this);
    dialog.exec();
}

void Preflet::removeUser()
{
    if (!m_currentAccount)
        return;

    QMessageBox dialog(this);
    dialog.setIcon(QMessageBox::Question);
    dialog.setText(tr("<b>Do you want to keep %1's files?</b>")
                   .arg(m_currentAccount->realName()));
    dialog.setInformativeText(tr("It is possible to keep the home directory, "
                                 "mail spool and temporary files around when "
                                 "deleting a user account."));
    QPushButton *removeFilesButton =
            dialog.addButton(tr("Delete Files"), QMessageBox::NoRole);
    QPushButton *keepFilesButton =
            dialog.addButton(tr("Keep Files"), QMessageBox::YesRole);
    dialog.addButton(QMessageBox::Cancel);
    dialog.exec();

    QAbstractButton *button = dialog.clickedButton();

    if (button == removeFilesButton || button == keepFilesButton) {
        AccountsManager *manager = new AccountsManager();
        manager->deleteUser(m_currentAccount, button == removeFilesButton);
        return;
    }
}

void Preflet::accountChanged()
{
    UserAccount *account = qobject_cast<UserAccount *>(sender());

    // If this is not the selected account we can't change the UI
    if (m_currentAccount != account)
        return;

    // Let's popule the UI
    populateUi(account);
}

#include "moc_preflet.cpp"
