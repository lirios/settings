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

#ifndef OUTPUTSMODEL_H
#define OUTPUTSMODEL_H

#include <QtCore/QAbstractItemModel>

#include <KScreen/Config>

class OutputsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(Roles)
public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        NumberRole,
        DeviceIdRole,
        VendorRole,
        ModelRole,
        SerialRole,
        PrimaryRole,
        ConnectedRole,
        EnabledRole,
        AspectRatioRole,
        AspectRatioStringRole,
        PositionRole,
        DiagonalSizeRole,
        ResolutionRole,
        ModesRole
    };

    OutputsModel(QObject *parent = 0);
    ~OutputsModel();

    QHash<int, QByteArray> roleNames() const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

Q_SIGNALS:
    void error(const QString &msg);

private:
    KScreen::ConfigPtr m_config;
    QList<KScreen::OutputPtr> m_list;
};

#endif // OUTPUTSMODEL_H
