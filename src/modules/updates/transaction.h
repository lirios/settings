// SPDX-FileCopyrightText: 2021 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef LIRI_SETTINGS_UPDATES_TRANSACTION_H
#define LIRI_SETTINGS_UPDATES_TRANSACTION_H

#include <QObject>

#include "rpmostree.h"

class OrgProjectatomicRpmostree1TransactionInterface;

class Transaction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Type type READ type CONSTANT FINAL)
    Q_PROPERTY(QString name READ name CONSTANT FINAL)
    Q_PROPERTY(QString title READ title CONSTANT FINAL)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged FINAL)
    Q_PROPERTY(QString lastErrorMessage READ lastErrorMessage NOTIFY lastErrorMessageChanged FINAL)
public:
    enum Type {
        UnknownType = 0,
        RefreshMetadataType,
        CheckForUpdatesType,
        UpgradeType,
    };
    Q_ENUM(Type);

    enum Status {
        UnknownStatus = 0,
        QueuedStatus,
        DownloadingStatus,
        CompletedStatus,
        CompletedWithErrorStatus,
        FailedStatus,
        CancelledStatus,
    };
    Q_ENUM(Status);

    explicit Transaction(Type typem, const QString &address,
                         const QString &name, QObject *parent = nullptr);
    ~Transaction();

    Type type() const;
    QString name() const;
    QString title() const;
    Status status() const;
    QString lastErrorMessage() const;

    Q_INVOKABLE void start();
    Q_INVOKABLE void cancel();

signals:
    void statusChanged(Transaction::Status status);
    void lastErrorMessageChanged(const QString &message);
    void passiveMessage(const QString &text);
    void progressChanged(uint percentage);

private:
    Type m_type = UnknownType;
    Status m_status = UnknownStatus;
    QString m_name;
    QString m_lastErrorMessage;
    OrgProjectatomicRpmostree1TransactionInterface *m_interface = nullptr;

    void setStatus(Status status);
    void setLastErrorMessage(const QString &message);

private slots:
    void handleDownloadProgress(RpmOstree::TimeData time,
                                RpmOstree::OutstandingDataCounts outstanding,
                                RpmOstree::MetadataCounts metadata,
                                RpmOstree::DeltaData delta,
                                RpmOstree::ContentData content,
                                RpmOstree::TransferData transfer);
    void handleFinished(bool success, const QString &errorMessage);
    void handleMessage(const QString &text);
    void handlePercentProgress(const QString &text, uint percentage);
    void handleProgressEnd();
    void handleSignatureProgress(const QVariantList &signature, const QString &commit);
    void handleTaskBegin(const QString &text);
    void handleTaskEnd(const QString &text);
};

#endif // LIRI_SETTINGS_UPDATES_TRANSACTION_H
