// SPDX-FileCopyrightText: 2021 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "rpmdiffmodel.h"

RpmDiffModel::RpmDiffModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

RpmDiffModel::~RpmDiffModel()
{
    qDeleteAll(m_items);
}

QHash<int, QByteArray> RpmDiffModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles.insert(Qt::DisplayRole, "display");
    roles.insert(NameRole, "name");
    roles.insert(DescriptionRole, "description");
    roles.insert(CategoryRole, "category");
    return roles;
}

int RpmDiffModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_items.size();
}

QVariant RpmDiffModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto *item = m_items.at(index.row());
    if (!item)
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        return QStringLiteral("%1 (%2)").arg(item->name, item->description);
    case NameRole:
        return item->name;
    case DescriptionRole:
        return item->description;
    case CategoryRole:
        return item->category;
    default:
        break;
    }

    return QVariant();
}

void RpmDiffModel::addItem(RpmDiffItem *item)
{
    auto nextIndex = m_items.size();

    beginInsertRows(QModelIndex(), nextIndex, nextIndex);
    m_items.append(item);
    endInsertRows();

    Q_EMIT countChanged();
}

void RpmDiffModel::removeItem(RpmDiffItem *item)
{
    auto index = m_items.indexOf(item);

    if (index >= 0) {
        beginRemoveRows(QModelIndex(), index, index);
        m_items.removeOne(item);
        endRemoveRows();

        Q_EMIT countChanged();
    }
}

void RpmDiffModel::clearItems()
{
    if (m_items.size() > 0) {
        beginResetModel();
        qDeleteAll(m_items);
        endResetModel();

        Q_EMIT countChanged();
    }
}
