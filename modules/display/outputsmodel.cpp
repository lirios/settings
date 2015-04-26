/****************************************************************************
 * This file is part of Hawaii.
 *
 * Copyright (C) 2015 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include <QtMath>

#include <KScreen/ConfigMonitor>
#include <KScreen/EDID>
#include <KScreen/GetConfigOperation>
#include <KScreen/Output>

#include "outputsmodel.h"

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
            return QString().sprintf("%0.1f\"", knownDiagonals[i]);
    }

    return QString().sprintf("%d\"", (int)(diagonal + 0.5));
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

static QVariantList modesList(const KScreen::ModeList &list)
{
    QVariantList result;
    return result;

    Q_FOREACH (const KScreen::ModePtr &mode, list) {
        QVariantMap map;
        map.insert(QStringLiteral("name"), mode->name());
        map.insert(QStringLiteral("id"), mode->id());
        map.insert(QStringLiteral("size"), mode->size());
        map.insert(QStringLiteral("refreshRate"), mode->refreshRate());
        result.append(map);
    }

    return result;
}

OutputsModel::OutputsModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_config(Q_NULLPTR)
{
    connect(new KScreen::GetConfigOperation, &KScreen::GetConfigOperation::finished,
            this, [this](KScreen::ConfigOperation *op) {
        // Handle errors
        if (op->hasError()) {
            Q_EMIT error(op->errorString());
            return;
        }

        // Acquire configuration
        m_config = qobject_cast<KScreen::GetConfigOperation *>(op)->config();

        // Clear and add the new monitor configuration
        beginResetModel();
        m_list.clear();
        KScreen::ConfigMonitor::instance()->addConfig(m_config);
        Q_FOREACH (const KScreen::OutputPtr &output, m_config->outputs()) {
            if (output->isEnabled())
                m_list.append(output);
        }
        endResetModel();
    });
}

OutputsModel::~OutputsModel()
{
    disconnect(m_config.data());
    KScreen::ConfigMonitor::instance()->removeConfig(m_config);
}

QHash<int, QByteArray> OutputsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(NameRole, QByteArray("name"));
    roles.insert(NumberRole, QByteArray("number"));
    roles.insert(DeviceIdRole, QByteArray("deviceId"));
    roles.insert(VendorRole, QByteArray("vendor"));
    roles.insert(ModelRole, QByteArray("model"));
    roles.insert(SerialRole, QByteArray("serial"));
    roles.insert(PrimaryRole, QByteArray("primary"));
    roles.insert(ConnectedRole, QByteArray("connected"));
    roles.insert(EnabledRole, QByteArray("enabled"));
    roles.insert(AspectRatioRole, QByteArray("aspectRatio"));
    roles.insert(AspectRatioStringRole, QByteArray("aspectRatioString"));
    roles.insert(PositionRole, QByteArray("position"));
    roles.insert(DiagonalSizeRole, QByteArray("diagonalSize"));
    roles.insert(ResolutionRole, QByteArray("resolution"));
    roles.insert(ModesRole, QByteArray("modes"));
    return roles;
}

int OutputsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    if (m_config.isNull())
        return 0;
    return m_list.size();
}

QVariant OutputsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() < 0 && index.row() > m_list.size())
        return QVariant();

    KScreen::OutputPtr output = m_list.at(index.row());
    if (output.isNull())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
    case NameRole:
        return output->name();
    case NumberRole:
        return index.row() + 1;
    case DeviceIdRole:
        return output->edid() ? output->edid()->deviceId() : QString();
    case VendorRole:
        return output->edid() ? output->edid()->vendor() : QString();
    case ModelRole:
        return output->edid() ? output->edid()->name() : QString();
    case SerialRole:
        return output->edid() ? output->edid()->serial() : QString();
    case PrimaryRole:
        return output->isPrimary();
    case ConnectedRole:
        return output->isConnected();
    case EnabledRole:
        return output->isEnabled();
    case AspectRatioRole:
        if (output->sizeMm().width() > output->sizeMm().height())
            return (qreal)output->sizeMm().width() / (qreal)output->sizeMm().height();
        return (qreal)output->sizeMm().height() / (qreal)output->sizeMm().width();
    case AspectRatioStringRole:
        return aspectRatioString(output->sizeMm());
    case PositionRole:
        return output->pos();
    case DiagonalSizeRole:
        return displaySizeString(output->sizeMm());
    case ResolutionRole:
        return output->currentMode()->size();
    case ModesRole:
        return modesList(output->modes());
    default:
        break;
    }

    return QVariant();
}

#include "moc_outputsmodel.cpp"
