// SPDX-FileCopyrightText: 2021 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "rpmdiffmodel.h"
#include "rpmostreebackend.h"
#include "softwareupdate.h"
#include "transaction.h"

SoftwareUpdate::SoftwareUpdate(QObject *parent)
    : QObject(parent)
    , m_backend(new RpmOstreeBackend(this))
    , m_model(new RpmDiffModel(this))
{
    connect(m_backend, &RpmOstreeBackend::rpmDiffChanged, this, [this] {
        auto n = m_backend->model()->rowCount();
        m_information = tr("%n package(s) added, removed or updated", "", n);
        Q_EMIT informationChanged();
    });
    connect(m_backend, &RpmOstreeBackend::cachedUpdateChanged, this, &SoftwareUpdate::versionChanged);

    m_backend->setModel(m_model);
}

bool SoftwareUpdate::isEnabled() const
{
    return m_backend->isEnabled();
}

QString SoftwareUpdate::information() const
{
    return m_information;
}

QString SoftwareUpdate::version() const
{
    return m_backend->version();
}

RpmDiffModel *SoftwareUpdate::model() const
{
    return m_model;
}

Transaction *SoftwareUpdate::currentTransaction() const
{
    return m_transaction;
}

void SoftwareUpdate::classBegin()
{
}

void SoftwareUpdate::componentComplete()
{
    if (!isEnabled())
        return;

    // Activate the backend
    m_backend->activate();

    // Register client
    if (!m_backend->registerClient())
        return;

    // Save cached update information
    m_backend->readCachedUpdate();

    // Get rpm-diff from cached updates
    m_backend->populateRpmDiffModel();
}

Transaction *SoftwareUpdate::refreshMetadata()
{
    if (!isEnabled())
        return nullptr;

    if (!m_transaction.isNull()) {
        qCWarning(gLcUpdates, "Cannot refresh metadata: another transaction is running");
        return nullptr;
    }

    auto *transaction = m_backend->refreshMetadata();
    setTransaction(transaction);
    return transaction;

}

Transaction *SoftwareUpdate::checkForUpdates()
{
    if (!isEnabled())
        return nullptr;

    if (!m_transaction.isNull()) {
        qCWarning(gLcUpdates, "Cannot check for updates: another transaction is running");
        return nullptr;
    }

    auto *transaction = m_backend->checkForUpdates();
    setTransaction(transaction);
    return transaction;
}

Transaction *SoftwareUpdate::upgrade(bool allowDowngrade, bool reboot)
{
    if (!isEnabled())
        return nullptr;

    if (!m_transaction.isNull()) {
        qCWarning(gLcUpdates, "Cannot upgrade: another transaction is running");
        return nullptr;
    }

    auto *transaction = m_backend->upgrade(allowDowngrade, reboot);
    setTransaction(transaction);
    return transaction;
}

void SoftwareUpdate::setTransaction(Transaction *transaction)
{
    m_transaction = transaction;

    m_transactionConnection = connect(transaction, &Transaction::statusChanged,
                                      this, [this](Transaction::Status status) {
        switch (status) {
        case Transaction::CompletedStatus:
        case Transaction::CompletedWithErrorStatus:
        case Transaction::CancelledStatus:
        case Transaction::FailedStatus:
            unsetTransaction();
            break;
        default:
            break;
        }
    });

    Q_EMIT currentTransactionChanged();
}

void SoftwareUpdate::unsetTransaction()
{
    if (m_transaction) {
        disconnect(m_transactionConnection);
        m_transaction.clear();
        Q_EMIT currentTransactionChanged();
    }
}
