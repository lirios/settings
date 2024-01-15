// SPDX-FileCopyrightText: 2021 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <QDBusConnection>

#include "rpmostreebackend.h"
#include "rpmostree1_interface.h"
#include "transaction.h"

Transaction::Transaction(Type type, const QString &address,
                         const QString &name, QObject *parent)
    : QObject(parent)
    , m_type(type)
    , m_name(name)
{
    auto connection = QDBusConnection::connectToPeer(address, m_name);

    m_interface = new OrgProjectatomicRpmostree1TransactionInterface(
                QStringLiteral("org.projectatomic.rpmostree1"),
                QStringLiteral("/"),
                connection);
    connect(m_interface, &OrgProjectatomicRpmostree1TransactionInterface::DownloadProgress,
            this, &Transaction::handleDownloadProgress);
    connect(m_interface, &OrgProjectatomicRpmostree1TransactionInterface::Finished,
            this, &Transaction::handleFinished);
    connect(m_interface, &OrgProjectatomicRpmostree1TransactionInterface::Message,
            this, &Transaction::handleMessage);
    connect(m_interface, &OrgProjectatomicRpmostree1TransactionInterface::PercentProgress,
            this, &Transaction::handlePercentProgress);
    connect(m_interface, &OrgProjectatomicRpmostree1TransactionInterface::ProgressEnd,
            this, &Transaction::handleProgressEnd);
    connect(m_interface, &OrgProjectatomicRpmostree1TransactionInterface::SignatureProgress,
            this, &Transaction::handleSignatureProgress);
    connect(m_interface, &OrgProjectatomicRpmostree1TransactionInterface::TaskBegin,
            this, &Transaction::handleTaskBegin);
    connect(m_interface, &OrgProjectatomicRpmostree1TransactionInterface::TaskEnd,
            this, &Transaction::handleTaskEnd);
}

Transaction::~Transaction()
{
    if (m_interface) {
        cancel();

        m_interface->deleteLater();
        m_interface = nullptr;
    }

    QDBusConnection::disconnectFromPeer(m_name);
}

Transaction::Type Transaction::type() const
{
    return m_type;
}

QString Transaction::name() const
{
    return m_name;
}

QString Transaction::title() const
{
    return m_interface->title();
}

Transaction::Status Transaction::status() const
{
    return m_status;
}

QString Transaction::lastErrorMessage() const
{
    return m_lastErrorMessage;
}

void Transaction::start()
{
    auto reply = m_interface->Start();
    reply.waitForFinished();

    if (reply.isError()) {
        qCWarning(gLcUpdates, "An error has occurred while starting the transaction \"%s\": %s",
                  qPrintable(m_name), qPrintable(reply.error().message()));
        setStatus(FailedStatus);
    }

    if (reply.value()) {
        setStatus(QueuedStatus);
    } else {
        qCWarning(gLcUpdates, "Failed to start transaction \"%s\": %s",
                  qPrintable(m_name), qPrintable(reply.error().message()));
        setStatus(FailedStatus);
    }
}

void Transaction::cancel()
{
    m_interface->Cancel().waitForFinished();
    setStatus(CancelledStatus);
}

void Transaction::setStatus(Status status)
{
    if (m_status != status) {
        m_status = status;
        Q_EMIT statusChanged(status);
    }
}

void Transaction::setLastErrorMessage(const QString &message)
{
    m_lastErrorMessage = message;
    Q_EMIT lastErrorMessageChanged(message);
}

void Transaction::handleDownloadProgress(RpmOstree::TimeData time,
                                         RpmOstree::OutstandingDataCounts outstanding,
                                         RpmOstree::MetadataCounts metadata,
                                         RpmOstree::DeltaData delta,
                                         RpmOstree::ContentData content,
                                         RpmOstree::TransferData transfer)
{
    Q_UNUSED(time)
    Q_UNUSED(outstanding)
    Q_UNUSED(metadata)
    Q_UNUSED(delta)
    Q_UNUSED(content)

    qCInfo(gLcUpdates, "Transaction \"%s\" download progress: %lld bytes/s",
           qPrintable(m_name), transfer.bytesPerSecond);
    setStatus(DownloadingStatus);
}

void Transaction::handleFinished(bool success, const QString &errorMessage)
{
    if (success) {
        setStatus(CompletedStatus);
    } else {
        setLastErrorMessage(errorMessage);
        setStatus(CompletedWithErrorStatus);
    }
}

void Transaction::handleMessage(const QString &text)
{
    qCInfo(gLcUpdates, "Transaction \"%s\": %s",
           qPrintable(m_name), qPrintable(text));
    Q_EMIT passiveMessage(text);
}

void Transaction::handlePercentProgress(const QString &text, uint percentage)
{
    qCInfo(gLcUpdates, "Transaction \"%s\" progress %d %%: %s",
           qPrintable(m_name), percentage, qPrintable(text));
    Q_EMIT progressChanged(percentage);
}

void Transaction::handleProgressEnd()
{
    qCInfo(gLcUpdates, "Transaction \"%s\" progress end",
           qPrintable(m_name));
}

void Transaction::handleSignatureProgress(const QVariantList &signature, const QString &commit)
{
    Q_UNUSED(signature)
    Q_UNUSED(commit)

    qCInfo(gLcUpdates, "Transaction \"%s\" signature progress",
           qPrintable(m_name));
}

void Transaction::handleTaskBegin(const QString &text)
{
    qCInfo(gLcUpdates, "Transaction \"%s\" task begin: %s",
           qPrintable(m_name), qPrintable(text));
}

void Transaction::handleTaskEnd(const QString &text)
{
    qCInfo(gLcUpdates, "Transaction \"%s\" task end: %s",
           qPrintable(m_name), qPrintable(text));
}
