// SPDX-FileCopyrightText: 2021 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef LIRI_SETTINGS_UPDATES_RPMOSTREEBACKEND_H
#define LIRI_SETTINGS_UPDATES_RPMOSTREEBACKEND_H

#include <QLoggingCategory>
#include <QObject>
#include <QPointer>

class RpmDiffItem;
class RpmDiffModel;
class Transaction;

class OrgProjectatomicRpmostree1SysrootInterface;
class OrgProjectatomicRpmostree1OSInterface;

Q_DECLARE_LOGGING_CATEGORY(gLcUpdates)

class RpmOstreeBackend : public QObject
{
    Q_OBJECT
public:
    explicit RpmOstreeBackend(QObject *parent = nullptr);
    ~RpmOstreeBackend();

    bool isEnabled() const;

    QString osName() const;
    QString checksum() const;
    QString version() const;

    RpmDiffModel *model() const;
    void setModel(RpmDiffModel *model);

    void activate();

    void readCachedUpdate();

    bool registerClient();
    bool unregisterClient();

    bool reload();
    bool reloadConfig();

    Transaction *refreshMetadata();
    Transaction *checkForUpdates();
    Transaction *upgrade(bool allowDowngrade = false, bool reboot = false);

    void populateRpmDiffModel();

Q_SIGNALS:
    void cachedUpdateChanged();
    void rpmDiffChanged();

private:
    bool m_enabled = false;
    OrgProjectatomicRpmostree1SysrootInterface *m_sysRoot = nullptr;
    OrgProjectatomicRpmostree1OSInterface *m_os = nullptr;
    QString m_osName, m_checksum, m_version;
    QPointer<RpmDiffModel> m_model;
    QVector<Transaction *> m_transactions;

    void processRpmDiff(const QVariantMap &rpmDiff);
};

#endif // LIRI_SETTINGS_UPDATES_RPMOSTREEBACKEND_H
