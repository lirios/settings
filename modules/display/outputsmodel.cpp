/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2016 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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
#include <QtCore/QCoreApplication>

#include <Liri/WaylandClient/OutputConfiguration>

#include "outputsmodel.h"

#define TR QCoreApplication::translate

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

static QVariantList modesList(const QList<Output::Mode> &list)
{
    QVariantList result;

    int i = 0;
    Q_FOREACH (const Output::Mode &mode, list) {
        QVariantMap map;
        map.insert(QStringLiteral("name"),
                   TR("OutputsModel", "%1 × %2 (%3)", "Resolution combo box").arg(
                       QString::number(mode.size.width()),
                       QString::number(mode.size.height()),
                       aspectRatioString(mode.size)));
        map.insert(QStringLiteral("id"), i++);
        map.insert(QStringLiteral("size"), mode.size);
        map.insert(QStringLiteral("refreshRate"), mode.refreshRate);
        result.append(map);
    }

    return result;
}

OutputsModel::OutputsModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_config(new WaylandConfig(this))
{
    connect(m_config, &WaylandConfig::configurationEnabledChanged,
            this, &OutputsModel::configurationEnabledChanged);
    connect(m_config, &WaylandConfig::outputAdded, this, [this](Output *output) {
        beginInsertRows(QModelIndex(), m_list.size(), m_list.size());
        m_list.append(output);
        endInsertRows();
    });
    connect(m_config, &WaylandConfig::outputRemoved, this, [this](Output *output) {
        beginRemoveRows(QModelIndex(), m_list.size(), m_list.size());
        m_list.removeOne(output);
        endRemoveRows();
    });
}

OutputsModel::~OutputsModel()
{
}

bool OutputsModel::isConfigurationEnabled() const
{
    return m_config->isConfigurationEnabled();
}

QHash<int, QByteArray> OutputsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(NameRole, QByteArrayLiteral("name"));
    roles.insert(NumberRole, QByteArrayLiteral("number"));
    roles.insert(ManufacturerRole, QByteArrayLiteral("manufacturer"));
    roles.insert(ModelRole, QByteArrayLiteral("model"));
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

    Output *output = m_list.at(index.row());

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
        return false; // output->isPrimary();
    case EnabledRole:
        return true; // output->isEnabled();
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
    case ResolutionRole:
        return output->size();
    case CurrentModeRole:
        return 5; //output->currentMode();
    case ModesRole:
        return modesList(output->modes());
    case TransformRole:
        switch (output->transform()) {
        case Output::Transform90:
            return Transform90;
        case Output::Transform180:
            return Transform180;
        case Output::Transform270:
            return Transform270;
        default:
            return TransformNormal;
        }
    default:
        break;
    }

    return QVariant();
}

void OutputsModel::applyConfiguration(int outputNumber, int modeId, const Transform &transform)
{
    OutputManagement *management = m_config->outputManagement();
    if (!management)
        return;

    Output::Transform wlTransform = Output::TransformNormal;
    switch (transform) {
    case Transform90:
        wlTransform = Output::Transform90;
        break;
    case Transform180:
        wlTransform = Output::Transform180;
        break;
    case Transform270:
        wlTransform = Output::Transform270;
        break;
    default:
        break;
    }

    Output *output = m_list.at(outputNumber - 1);

    OutputConfiguration *config = management->createConfiguration(this);
    config->setEnabled(output, true);
    config->setModeId(output, modeId);
    config->setTransform(output, wlTransform);
    config->setPosition(output, output->position());
    config->setScaleFactor(output, output->scale());
    config->apply();
}

#include "moc_outputsmodel.cpp"
