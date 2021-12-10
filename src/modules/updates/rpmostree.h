// SPDX-FileCopyrightText: 2021 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef LIRI_RPMOSTREE_H
#define LIRI_RPMOSTREE_H

#include <QDBusArgument>
#include <QDBusObjectPath>

typedef QList<QVariantMap> QVariantMapList;

namespace RpmOstree {

/*
 * Transaction
 */

struct Transaction
{
    QString methodName;
    QString senderName;
    QDBusObjectPath objectPath;
};

inline QDBusArgument &operator<<(QDBusArgument &argument, const Transaction &transaction)
{
    argument.beginStructure();
    argument << transaction.methodName;
    argument << transaction.senderName;
    argument << transaction.objectPath;
    argument.endStructure();
    return argument;
}

inline const QDBusArgument &operator>>(const QDBusArgument &argument, Transaction &transaction)
{
    argument.beginStructure();
    argument >> transaction.methodName;
    argument >> transaction.senderName;
    argument >> transaction.objectPath;
    argument.endStructure();
    return argument;
}

/*
 * RpmDiff
 */

struct RpmDiff
{
    QString s;
    quint32 u;
    QVariantMap details;
};

inline QDBusArgument &operator<<(QDBusArgument &argument, const RpmDiff &diff)
{
    argument.beginStructure();
    argument << diff.s;
    argument << diff.u;
    argument << diff.details;
    argument.endStructure();
    return argument;
}

inline const QDBusArgument &operator>>(const QDBusArgument &argument, RpmDiff &diff)
{
    argument.beginStructure();
    argument >> diff.s;
    argument >> diff.u;
    argument >> diff.details;
    argument.endStructure();
    return argument;
}

typedef QList<RpmDiff> RpmDiffList;

/*
 * VersionArch
 */

struct VersionArch {
    QString evr;
    QString arch;
};

inline QDBusArgument &operator<<(QDBusArgument &argument, const VersionArch &value)
{
    argument.beginStructure();
    argument << value.evr;
    argument << value.arch;
    argument.endStructure();
    return argument;
}

inline const QDBusArgument &operator>>(const QDBusArgument &argument, VersionArch &value)
{
    argument.beginStructure();
    argument >> value.evr;
    argument >> value.arch;
    argument.endStructure();
    return argument;
}

/*
 * RpmDiffPackagesChange
 */

struct RpmDiffPackagesChange {
    quint32 num;
    QString name;
    QString evr;
    QString arch;
};

inline QDBusArgument &operator<<(QDBusArgument &argument, const RpmDiffPackagesChange &diff)
{
    argument.beginStructure();
    argument << diff.num;
    argument << diff.name;
    argument << diff.evr;
    argument << diff.arch;
    argument.endStructure();
    return argument;
}

inline const QDBusArgument &operator>>(const QDBusArgument &argument, RpmDiffPackagesChange &diff)
{
    argument.beginStructure();
    argument >> diff.num;
    argument >> diff.name;
    argument >> diff.evr;
    argument >> diff.arch;
    argument.endStructure();
    return argument;
}

typedef QList<RpmDiffPackagesChange> RpmDiffPackagesChangeList;

/*
 * RpmDiffVersionChange
 */

struct RpmDiffVersionChange {
    quint32 num;
    QString name;
    VersionArch previousVersion;
    VersionArch newVersion;
};

inline QDBusArgument &operator<<(QDBusArgument &argument, const RpmDiffVersionChange &diff)
{
    argument.beginStructure();
    argument << diff.num;
    argument << diff.name;
    argument << diff.previousVersion;
    argument << diff.newVersion;
    argument.endStructure();
    return argument;
}

inline const QDBusArgument &operator>>(const QDBusArgument &argument, RpmDiffVersionChange &diff)
{
    argument.beginStructure();
    argument >> diff.num;
    argument >> diff.name;
    argument >> diff.previousVersion;
    argument >> diff.newVersion;
    argument.endStructure();
    return argument;
}

typedef QList<RpmDiffVersionChange> RpmDiffVersionChangeList;

/*
 * TimeData
 */

struct TimeData
{
    quint64 startTime;
    quint64 elapsedSeconds;
};

inline QDBusArgument &operator<<(QDBusArgument &argument, const TimeData &data)
{
    argument.beginStructure();
    argument << data.startTime;
    argument << data.elapsedSeconds;
    argument.endStructure();
    return argument;
}

inline const QDBusArgument &operator>>(const QDBusArgument &argument, TimeData &data)
{
    argument.beginStructure();
    argument >> data.startTime;
    argument >> data.elapsedSeconds;
    argument.endStructure();
    return argument;
}

/*
 * OutstandingDataCounts
 */

struct OutstandingDataCounts
{
    quint32 fetches;
    quint32 writes;
};

inline QDBusArgument &operator<<(QDBusArgument &argument, const OutstandingDataCounts &data)
{
    argument.beginStructure();
    argument << data.fetches;
    argument << data.writes;
    argument.endStructure();
    return argument;
}

inline const QDBusArgument &operator>>(const QDBusArgument &argument, OutstandingDataCounts &data)
{
    argument.beginStructure();
    argument >> data.fetches;
    argument >> data.writes;
    argument.endStructure();
    return argument;
}

/*
 * MetadataCounts
 */

struct MetadataCounts
{
    quint32 scanned;
    quint32 fetched;
    quint32 outstanding;
};

inline QDBusArgument &operator<<(QDBusArgument &argument, const MetadataCounts &data)
{
    argument.beginStructure();
    argument << data.scanned;
    argument << data.fetched;
    argument << data.outstanding;
    argument.endStructure();
    return argument;
}

inline const QDBusArgument &operator>>(const QDBusArgument &argument, MetadataCounts &data)
{
    argument.beginStructure();
    argument >> data.scanned;
    argument >> data.fetched;
    argument >> data.outstanding;
    argument.endStructure();
    return argument;
}

/*
 * DeltaData
 */

struct DeltaData
{
    quint32 totalParts;
    quint32 fetchedParts;
    quint32 totalSuperBlocks;
    quint64 totalSize;
};

inline QDBusArgument &operator<<(QDBusArgument &argument, const DeltaData &data)
{
    argument.beginStructure();
    argument << data.totalParts;
    argument << data.fetchedParts;
    argument << data.totalSuperBlocks;
    argument << data.totalSize;
    argument.endStructure();
    return argument;
}

inline const QDBusArgument &operator>>(const QDBusArgument &argument, DeltaData &data)
{
    argument.beginStructure();
    argument >> data.totalParts;
    argument >> data.fetchedParts;
    argument >> data.totalSuperBlocks;
    argument >> data.totalSize;
    argument.endStructure();
    return argument;
}

/*
 * ContentData
 */

struct ContentData
{
    quint32 fetched;
    quint32 requested;
};

inline QDBusArgument &operator<<(QDBusArgument &argument, const ContentData &data)
{
    argument.beginStructure();
    argument << data.fetched;
    argument << data.requested;
    argument.endStructure();
    return argument;
}

inline const QDBusArgument &operator>>(const QDBusArgument &argument, ContentData &data)
{
    argument.beginStructure();
    argument >> data.fetched;
    argument >> data.requested;
    argument.endStructure();
    return argument;
}

/*
 * TransferData
 */

struct TransferData
{
    quint64 transfered;
    quint64 bytesPerSecond;
};

inline QDBusArgument &operator<<(QDBusArgument &argument, const TransferData &data)
{
    argument.beginStructure();
    argument << data.transfered;
    argument << data.bytesPerSecond;
    argument.endStructure();
    return argument;
}

inline const QDBusArgument &operator>>(const QDBusArgument &argument, TransferData &data)
{
    argument.beginStructure();
    argument >> data.transfered;
    argument >> data.bytesPerSecond;
    argument.endStructure();
    return argument;
}

} // namespace RpmOstree

Q_DECLARE_METATYPE(RpmOstree::Transaction)
Q_DECLARE_METATYPE(RpmOstree::RpmDiff)
Q_DECLARE_METATYPE(RpmOstree::RpmDiffList)
Q_DECLARE_METATYPE(RpmOstree::VersionArch)
Q_DECLARE_METATYPE(RpmOstree::RpmDiffPackagesChange)
Q_DECLARE_METATYPE(RpmOstree::RpmDiffPackagesChangeList)
Q_DECLARE_METATYPE(RpmOstree::RpmDiffVersionChange)
Q_DECLARE_METATYPE(RpmOstree::RpmDiffVersionChangeList)
Q_DECLARE_METATYPE(RpmOstree::TimeData)
Q_DECLARE_METATYPE(RpmOstree::OutstandingDataCounts)
Q_DECLARE_METATYPE(RpmOstree::MetadataCounts)
Q_DECLARE_METATYPE(RpmOstree::DeltaData)
Q_DECLARE_METATYPE(RpmOstree::ContentData)
Q_DECLARE_METATYPE(RpmOstree::TransferData)

#endif // LIRI_RPMOSTREE_H
