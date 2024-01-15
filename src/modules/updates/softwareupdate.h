// SPDX-FileCopyrightText: 2021 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef LIRI_SETTINGS_UPDATES_SOFTWAREUPDATE_H
#define LIRI_SETTINGS_UPDATES_SOFTWAREUPDATE_H

#include <QObject>
#include <QPointer>
#include <QQmlParserStatus>

class RpmOstreeBackend;
class RpmDiffModel;
class Transaction;

class SoftwareUpdate : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ isEnabled CONSTANT)
    Q_PROPERTY(QString information READ information NOTIFY informationChanged)
    Q_PROPERTY(QString version READ version NOTIFY versionChanged)
    Q_PROPERTY(RpmDiffModel *model READ model CONSTANT)
    Q_PROPERTY(Transaction *currentTransaction READ currentTransaction NOTIFY currentTransactionChanged)
    Q_INTERFACES(QQmlParserStatus)
    Q_MOC_INCLUDE("transaction.h")
public:
    explicit SoftwareUpdate(QObject *parent = nullptr);

    bool isEnabled() const;

    QString information() const;
    QString version() const;

    RpmDiffModel *model() const;

    Transaction *currentTransaction() const;

    void classBegin() override;
    void componentComplete() override;

    Q_INVOKABLE Transaction *refreshMetadata();
    Q_INVOKABLE Transaction *checkForUpdates();
    Q_INVOKABLE Transaction *upgrade(bool allowDowngrade = false, bool reboot = false);

Q_SIGNALS:
    void informationChanged();
    void versionChanged();
    void currentTransactionChanged(Transaction *transaction);

private:
    RpmOstreeBackend *m_backend = nullptr;
    RpmDiffModel *m_model = nullptr;
    QPointer<Transaction> m_transaction;
    QMetaObject::Connection m_transactionConnection;
    QString m_information;

    void setTransaction(Transaction *transaction);
    void unsetTransaction();
};

#endif // LIRI_SETTINGS_UPDATES_SOFTWAREUPDATE_H
