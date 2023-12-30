/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2018 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:GPL3+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include <QtMath>
#include <QCoreApplication>
#include <QDBusConnection>

#include "outputconfiguration1interface.h"
#include "outputdevice1interface.h"
#include "outputmanagement1interface.h"
#include "outputsmodel.h"

#define TR QCoreApplication::translate

const QString dbusService = QLatin1String("io.liri.Session");

static const qreal knownDiagonals[] = {
    12.1,
    13.3,
    15.6
};

static QString diagonalToString(qreal diagonal)
{
    int nelements = sizeof(knownDiagonals) / sizeof(knownDiagonals[0]);
    for (int i = 0; i < nelements; i++) {
        qreal delta = qFabs(knownDiagonals[i] - diagonal);
        if (delta < 0.1)
            return QString::asprintf("%0.1f\"", knownDiagonals[i]);
    }

    return QString::asprintf("%d\"", (int)(diagonal + 0.5));
}

static QString displaySizeString(const QSize &sizeMm)
{
    if (!sizeMm.isValid())
        return QString();

    qreal diagonal = qSqrt(qPow(sizeMm.width(), 2) + qPow(sizeMm.height(), 2));
    return diagonalToString(diagonal / 25.4);
}

static QString aspectRatioString(const QSize &size)
{
    if (!size.isValid())
        return QString();

    int ratio = 0;
    if (size.width() > size.height())
        ratio = size.width() * 10 / size.height();
    else
        ratio = size.height() * 10 / size.width();

    switch (ratio) {
    case 10:
        return QStringLiteral("1:1");
    case 12:
        return QStringLiteral("5:4");
    case 13:
        return QStringLiteral("4:3");
    case 15:
        return QStringLiteral("3:2");
    case 16:
        return QStringLiteral("1:6");
    case 17:
        return QStringLiteral("16:9");
    case 18:
        return QStringLiteral("9:5");
    case 23:
        return QStringLiteral("21:9");
    default:
        break;
    }

    return QString();
}

static OutputsModel::Transform stringToTransform(const QString &transform)
{
    if (transform == QLatin1String("normal"))
        return OutputsModel::TransformNormal;
    else if (transform == QLatin1String("90"))
        return OutputsModel::Transform90;
    else if (transform == QLatin1String("180"))
        return OutputsModel::Transform180;
    else if (transform == QLatin1String("270"))
        return OutputsModel::Transform270;
    else if (transform == QLatin1String("flipped"))
        return OutputsModel::TransformFlipped;
    else if (transform == QLatin1String("flipped90"))
        return OutputsModel::Transform90;
    else if (transform == QLatin1String("flipped180"))
        return OutputsModel::Transform180;
    else if (transform == QLatin1String("flipped270"))
        return OutputsModel::Transform270;

    Q_UNREACHABLE();
}

static QVariantList modesList(const QList<Mode> &modes)
{
    QVariantList list;

    for (auto mode : modes) {
        QVariantMap map;
        map[QLatin1String("name")] = mode.name;
        map[QLatin1String("size")] = mode.size;
        map[QLatin1String("refreshRate")] = mode.refreshRate;
        list.append(map);
    }

    return list;
}

OutputsModel::OutputsModel(QObject *parent)
    : QAbstractListModel(parent)
{
    qDBusRegisterMetaType<Mode>();
    qDBusRegisterMetaType<QList<Mode> >();

    auto path = QLatin1String("/io/liri/Shell/OutputManagement1");
    auto bus = QDBusConnection::sessionBus();
    m_outputManagement = new IoLiriShellOutputManagement1Interface(
                dbusService, path, bus, this);
    Q_EMIT configurationEnabledChanged(m_outputManagement->isValid());

    for (auto path : m_outputManagement->outputDevices())
        handleOutputDeviceAdded(path);

    connect(m_outputManagement, &IoLiriShellOutputManagement1Interface::OutputDeviceAdded,
            this, &OutputsModel::handleOutputDeviceAdded);
    connect(m_outputManagement, &IoLiriShellOutputManagement1Interface::OutputDeviceRemoved,
            this, &OutputsModel::handleOutputDeviceRemoved);
}

OutputsModel::~OutputsModel()
{
}

bool OutputsModel::isConfigurationEnabled() const
{
    return m_outputManagement->isValid();
}

QHash<int, QByteArray> OutputsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(NameRole, QByteArrayLiteral("name"));
    roles.insert(NumberRole, QByteArrayLiteral("number"));
    roles.insert(ManufacturerRole, QByteArrayLiteral("manufacturer"));
    roles.insert(ModelRole, QByteArrayLiteral("modelName"));
    roles.insert(PrimaryRole, QByteArrayLiteral("primary"));
    roles.insert(EnabledRole, QByteArrayLiteral("enabled"));
    roles.insert(AspectRatioRole, QByteArrayLiteral("aspectRatio"));
    roles.insert(AspectRatioStringRole, QByteArrayLiteral("aspectRatioString"));
    roles.insert(PositionRole, QByteArrayLiteral("position"));
    roles.insert(DiagonalSizeRole, QByteArrayLiteral("diagonalSize"));
    roles.insert(ResolutionRole, QByteArrayLiteral("resolution"));
    roles.insert(CurrentModeRole, QByteArrayLiteral("currentMode"));
    roles.insert(ModesRole, QByteArrayLiteral("modes"));
    roles.insert(TransformRole, QByteArrayLiteral("transform"));
    return roles;
}

int OutputsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_list.size();
}

QVariant OutputsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() < 0 && index.row() > m_list.size())
        return QVariant();

    IoLiriShellOutputDevice1Interface *output = m_list.at(index.row());

    switch (role) {
    case Qt::DisplayRole:
    case NameRole:
        return QStringLiteral("%1 - %2").arg(output->manufacturer(), output->model());
    case NumberRole:
        return index.row() + 1;
    case ManufacturerRole:
        return output->manufacturer();
    case ModelRole:
        return output->model();
    case PrimaryRole:
        return m_outputManagement->primaryOutput().path() == output->path();
    case EnabledRole:
        return output->enabled();
    case AspectRatioRole:
        if (output->physicalSize().width() > output->physicalSize().height())
            return (qreal)output->physicalSize().width() / (qreal)output->physicalSize().height();
        return (qreal)output->physicalSize().height() / (qreal)output->physicalSize().width();
    case AspectRatioStringRole:
        return aspectRatioString(output->physicalSize());
    case PositionRole:
        return output->position();
    case DiagonalSizeRole:
        return displaySizeString(output->physicalSize());
    case ResolutionRole: {
        if (output->currentModeIndex() >= 0 && output->currentModeIndex() <= output->modes().size()) {
            Mode mode = output->modes().at(output->currentModeIndex());
            return mode.size;
        }
        return QSize(0, 0);
    }
    case CurrentModeRole:
        return output->currentModeIndex();
    case ModesRole:
        return modesList(output->modes());
    case TransformRole:
        return stringToTransform(output->transform());
    default:
        break;
    }

    return QVariant();
}

void OutputsModel::applyConfiguration(int outputNumber, int modeId, const Transform &transform)
{
    Q_UNUSED(transform)

    auto pending = m_outputManagement->CreateConfiguration();
    auto watcher = new QDBusPendingCallWatcher(pending, this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this, [this, outputNumber, modeId](QDBusPendingCallWatcher *call) {
        QDBusPendingReply<QDBusObjectPath> reply = *call;
        if (!reply.isError()) {
            QDBusObjectPath path = reply.argumentAt<0>();
            auto config = new IoLiriShellOutputConfiguration1Interface(
                        dbusService, path.path(), QDBusConnection::sessionBus(), this);

            auto device = m_list.at(outputNumber - 1);
            auto handle = QDBusObjectPath(device->path());

            config->SetEnabled(handle, true);
            config->SetMode(handle, modeId);
            config->SetPosition(handle, device->position());
            config->SetScaleFactor(handle, device->scaleFactor());
            config->SetTransform(handle, device->transform());
            config->Apply();
        }
        call->deleteLater();
    });
}

void OutputsModel::handleOutputDeviceAdded(const QDBusObjectPath &handle)
{
    auto bus = QDBusConnection::sessionBus();
    auto device = new IoLiriShellOutputDevice1Interface(dbusService, handle.path(), bus, this);

    beginInsertRows(QModelIndex(), m_list.size(), m_list.size());
    m_list.append(device);
    endInsertRows();

    connect(device, &IoLiriShellOutputDevice1Interface::Changed, this, [this] {
        beginResetModel();
        endResetModel();
    });
}

void OutputsModel::handleOutputDeviceRemoved(const QDBusObjectPath &handle)
{
    IoLiriShellOutputDevice1Interface *found = nullptr;
    for (auto device : m_list) {
        if (device->path() == handle.path()) {
            found = device;
            break;
        }
    }

    if (found) {
        beginRemoveRows(QModelIndex(), m_list.indexOf(found), m_list.indexOf(found));
        m_list.removeOne(found);
        endRemoveRows();
    }
}
