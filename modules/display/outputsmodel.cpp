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

#include <KScreen/ConfigMonitor>
#include <KScreen/EDID>
#include <KScreen/GetConfigOperation>
#include <KScreen/Output>

#include "outputsmodel.h"

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

        // Clear
        beginResetModel();
        m_list.clear();
        endResetModel();

        // Monitor configuration
        beginInsertRows(QModelIndex(), 0, m_config->outputs().size() - 1);
        KScreen::ConfigMonitor::instance()->addConfig(m_config);
        Q_FOREACH (KScreen::OutputPtr output, m_config->connectedOutputs())
            m_list.append(output);
        endInsertRows();
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
    roles.insert(VendorRole, QByteArray("vendor"));
    roles.insert(ModelRole, QByteArray("model"));
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
    case VendorRole:
        return output->edid()->vendor();
    case ModelRole:
        return output->edid()->serial();
    default:
        break;
    }

    return QVariant();
}

#include "moc_outputsmodel.cpp"
