// SPDX-FileCopyrightText: 2021 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <QDBusConnection>
#include <QDBusError>
#include <QDBusPendingCallWatcher>
#include <QFile>

#include "rpmdiffmodel.h"
#include "rpmostreebackend.h"
#include "rpmostree1_interface.h"
#include "transaction.h"

Q_LOGGING_CATEGORY(gLcUpdates, "liri.settings.updates")

RpmOstreeBackend::RpmOstreeBackend(QObject *parent)
    : QObject(parent)
{
    qDBusRegisterMetaType<QList<QVariantMap>>();
    qDBusRegisterMetaType<RpmOstree::Transaction>();
    qDBusRegisterMetaType<RpmOstree::RpmDiff>();
    qDBusRegisterMetaType<RpmOstree::RpmDiffList>();
    qDBusRegisterMetaType<RpmOstree::VersionArch>();
    qDBusRegisterMetaType<RpmOstree::RpmDiffPackagesChange>();
    qDBusRegisterMetaType<RpmOstree::RpmDiffPackagesChangeList>();
    qDBusRegisterMetaType<RpmOstree::RpmDiffVersionChange>();
    qDBusRegisterMetaType<RpmOstree::RpmDiffVersionChangeList>();
    qDBusRegisterMetaType<RpmOstree::TimeData>();
    qDBusRegisterMetaType<RpmOstree::OutstandingDataCounts>();
    qDBusRegisterMetaType<RpmOstree::MetadataCounts>();
    qDBusRegisterMetaType<RpmOstree::DeltaData>();
    qDBusRegisterMetaType<RpmOstree::ContentData>();
    qDBusRegisterMetaType<RpmOstree::TransferData>();

    m_enabled = QFile::exists(QStringLiteral("/run/ostree-booted"));
}

RpmOstreeBackend::~RpmOstreeBackend()
{
    for (const auto &transaction : qAsConst(m_transactions))
        transaction->deleteLater();
    m_transactions.clear();

    if (m_os) {
        m_os->deleteLater();
        m_os = nullptr;
    }

    if (m_sysRoot) {
        m_sysRoot->deleteLater();
        m_sysRoot = nullptr;
    }
}

bool RpmOstreeBackend::isEnabled() const
{
    return m_enabled;
}

QString RpmOstreeBackend::osName() const
{
    return m_osName;
}

QString RpmOstreeBackend::checksum() const
{
    return m_checksum;
}

QString RpmOstreeBackend::version() const
{
    return m_version;
}

RpmDiffModel *RpmOstreeBackend::model() const
{
    return m_model;
}

void RpmOstreeBackend::setModel(RpmDiffModel *model)
{
    m_model = model;
}

void RpmOstreeBackend::activate()
{
    // Make sure the daemon is properly started
    // FIXME: Replace with proper D-Bus activation
    QProcess process(this);
    process.start(QStringLiteral("rpm-ostree"), {QStringLiteral("status")});
    process.waitForFinished();

    // Sysroot and OS
    m_sysRoot = new OrgProjectatomicRpmostree1SysrootInterface(
                QStringLiteral("org.projectatomic.rpmostree1"),
                QStringLiteral("/org/projectatomic/rpmostree1/Sysroot"),
                QDBusConnection::systemBus());
    m_os = new OrgProjectatomicRpmostree1OSInterface(
                QStringLiteral("org.projectatomic.rpmostree1"),
                m_sysRoot->booted().path(),
                QDBusConnection::systemBus());
}

void RpmOstreeBackend::readCachedUpdate()
{
    qCInfo(gLcUpdates, "Read cached update...");

    const auto cachedUpdate = m_os->cachedUpdate();
    m_osName = cachedUpdate.value(QStringLiteral("osname")).toString();
    m_checksum = cachedUpdate.value(QStringLiteral("checksum")).toString();
    m_version = cachedUpdate.value(QStringLiteral("version")).toString();

    qCDebug(gLcUpdates, "Got OS '%s', version '%s', checksum '%s'",
            qPrintable(m_osName), qPrintable(m_checksum), qPrintable(m_version));

    Q_EMIT cachedUpdateChanged();
}

bool RpmOstreeBackend::registerClient()
{
    if (!m_enabled) {
        qCWarning(gLcUpdates, "Unable to register client: rpm-ostree is not available");
        return false;
    }

    if (!m_sysRoot) {
        qCWarning(gLcUpdates, "Unable to register client: sysroot not available");
        return false;
    }

    qInfo(gLcUpdates, "Registering client with rpm-ostree...");

    QVariantMap clientOptions = { {QStringLiteral("id"), QStringLiteral("liri-settings")} };
    auto reply = m_sysRoot->RegisterClient(clientOptions);
    reply.waitForFinished();

    if (reply.isError()) {
        qCWarning(gLcUpdates) << "Failed to register as a client with rpm-ostree:" << reply.error().message();
        return false;
    }

    qCDebug(gLcUpdates, "Client successfully registered with rpm-ostree");
    return true;
}

bool RpmOstreeBackend::unregisterClient()
{
    if (!m_enabled) {
        qCWarning(gLcUpdates, "Unable to unregister client: rpm-ostree is not available");
        return false;
    }

    if (!m_sysRoot) {
        qCWarning(gLcUpdates, "Unable to unregister client: sysroot not available");
        return false;
    }

    qInfo(gLcUpdates, "Unregistering client from rpm-ostree...");

    QVariantMap clientOptions = { {QStringLiteral("id"), QStringLiteral("liri-settings")} };
    auto reply = m_sysRoot->UnregisterClient(clientOptions);
    reply.waitForFinished();

    if (reply.isError()) {
        qCWarning(gLcUpdates) << "Failed to unregister as a client with rpm-ostree:" << reply.error().message();
        return false;
    }

    qCDebug(gLcUpdates, "Client successfully unregistered with rpm-ostree");
    return true;
}

bool RpmOstreeBackend::reload()
{
    if (!m_enabled) {
        qCWarning(gLcUpdates, "Unable to reload: rpm-ostree is not available");
        return false;
    }

    if (!m_sysRoot) {
        qCWarning(gLcUpdates, "Unable to unregister client: sysroot not available");
        return false;
    }

    qInfo(gLcUpdates, "Reloading rpm-ostree...");

    auto reply = m_sysRoot->Reload();
    reply.waitForFinished();

    if (reply.isError()) {
        qCWarning(gLcUpdates) << "Failed to reload rpm-ostree:" << reply.error().message();
        return false;
    }

    qCDebug(gLcUpdates, "Successfully reloaded rpm-ostree");
    return true;
}

bool RpmOstreeBackend::reloadConfig()
{
    if (!m_enabled) {
        qCWarning(gLcUpdates, "Unable to reload configuration: rpm-ostree is not available");
        return false;
    }

    if (!m_sysRoot) {
        qCWarning(gLcUpdates, "Unable to unregister client: sysroot not available");
        return false;
    }

    qInfo(gLcUpdates, "Reloading rpm-ostree configuration...");

    auto reply = m_sysRoot->ReloadConfig();
    reply.waitForFinished();

    if (reply.isError()) {
        qCWarning(gLcUpdates) << "Failed to reload rpm-ostree config:" << reply.error().message();
        return false;
    }

    qCDebug(gLcUpdates, "Successfully reloaded rpm-ostree config");
    return true;
}

Transaction *RpmOstreeBackend::refreshMetadata()
{
    if (!m_enabled) {
        qCWarning(gLcUpdates, "Unable to refresh metadata: rpm-ostree is not available");
        return nullptr;
    }

    if (!m_os) {
        qCWarning(gLcUpdates, "Unable to refresh metadata: OS not available");
        return nullptr;
    }

    qInfo(gLcUpdates, "Refreshing metadata...");

    auto reply = m_os->RefreshMd({ {QStringLiteral("force"), false} });
    reply.waitForFinished();

    if (reply.isError()) {
        qCWarning(gLcUpdates) << "Failed to refresh metadata:" << reply.error().message();
        return nullptr;
    }

    auto *transaction = new Transaction(
                Transaction::RefreshMetadataType,
                reply.value(), QStringLiteral("liri_refreshmd"));
    m_transactions.append(transaction);
    return transaction;
}

Transaction *RpmOstreeBackend::checkForUpdates()
{
    if (!m_enabled) {
        qCWarning(gLcUpdates, "Unable to check for updates: rpm-ostree is not available");
        return nullptr;
    }

    if (!m_os) {
        qCWarning(gLcUpdates, "Unable to check for updates: OS not available");
        return nullptr;
    }

    qInfo(gLcUpdates, "Checking for updates...");

    QVariantMap options;
    options[QStringLiteral("mode")] = QStringLiteral("check");
    options[QStringLiteral("output-to-self")] = false;

    auto reply = m_os->AutomaticUpdateTrigger(options);
    reply.waitForFinished();

    if (reply.isError()) {
        qCWarning(gLcUpdates, "An error has occurred while checking for updates: %s",
                  qPrintable(reply.error().message()));
        return nullptr;
    }

    if (!reply.argumentAt(0).toBool()) {
        qCWarning(gLcUpdates, "Failed to check for updates");
        return nullptr;
    }

    auto address = reply.argumentAt(1).toString();
    auto *transaction = new Transaction(
                Transaction::CheckForUpdatesType, address,
                QStringLiteral("liri_check"));
    m_transactions.append(transaction);
    return transaction;
}

Transaction *RpmOstreeBackend::upgrade(bool allowDowngrade, bool reboot)
{
    if (!m_enabled) {
        qCWarning(gLcUpdates, "Unable to upgrade: rpm-ostree is not available");
        return nullptr;
    }

    if (!m_os) {
        qCWarning(gLcUpdates, "Unable to upgrade: OS not available");
        return nullptr;
    }

    qInfo(gLcUpdates, "Updating...");

    QVariantMap refreshOptions;
    refreshOptions[QStringLiteral("reboot")] = reboot;
    refreshOptions[QStringLiteral("allow-downgrade")] = allowDowngrade;

    auto reply = m_os->Upgrade(refreshOptions);
    reply.waitForFinished();

    if (reply.isError()) {
        qCWarning(gLcUpdates, "An error has occurred during the update: %s",
                  qPrintable(reply.error().message()));
        return nullptr;
    }

    auto address = reply.argumentAt(0).toString();
    auto *transaction = new Transaction(
                Transaction::UpgradeType, address,
                QStringLiteral("liri_upgrade"));
    m_transactions.append(transaction);
    return transaction;
}

void RpmOstreeBackend::populateRpmDiffModel()
{
    if (!m_enabled) {
        qCWarning(gLcUpdates, "Unable to acquire rpm-diff list: rpm-ostree is not available");
        return;
    }

    if (!m_os) {
        qCWarning(gLcUpdates, "Unable to acquire rpm-diff: OS not available");
        return;
    }

    if (m_os->hasCachedUpdateRpmDiff()) {
        const auto cachedUpdate = m_os->cachedUpdate();
        const auto rpmDiffVariant = cachedUpdate.value(QStringLiteral("rpm-diff"));
        const auto rpmDiff = qdbus_cast<QVariantMap>(rpmDiffVariant.value<QDBusArgument>());
        processRpmDiff(rpmDiff);
    }
}

void RpmOstreeBackend::processRpmDiff(const QVariantMap &rpmDiff)
{
    Q_ASSERT(!m_model.isNull());

    m_model->clearItems();

    const auto rpmDiffKeys = rpmDiff.keys();
    for (const auto &key : rpmDiffKeys) {
        if (rpmDiff[key].isValid() && !rpmDiff[key].isNull()) {
            if (key == QStringLiteral("added") || key == QStringLiteral("removed")) {
                const auto category = key == QStringLiteral("added") ? tr("Added") : tr("Removed");

                RpmOstree::RpmDiffPackagesChangeList diffList;
                rpmDiff[key].value<QDBusArgument>() >> diffList;

                for (const auto &diff : qAsConst(diffList))
                    m_model->addItem(new RpmDiffItem(diff.name, diff.evr, category));
            } else if (key == QStringLiteral("downgraded") || key == QStringLiteral("upgraded")) {
                const auto category = key == QStringLiteral("downgraded") ? tr("Downgraded") : tr("Upgraded");

                RpmOstree::RpmDiffVersionChangeList diffList;
                rpmDiff[key].value<QDBusArgument>() >> diffList;

                for (const auto &diff : qAsConst(diffList)) {
                    const auto descr = tr("%1 → %2").arg(diff.previousVersion.evr, diff.newVersion.evr);
                    m_model->addItem(new RpmDiffItem(diff.name, descr, category));
                }
            }
        }
    }

    Q_EMIT rpmDiffChanged();
}
