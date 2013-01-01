/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2011-2013 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include <QDebug>
#include <QIcon>

#include <solid/devicenotifier.h>
#include <solid/audiointerface.h>

#include "soundcardmodel.h"

SoundCardModel::SoundCardModel(QObject *parent) :
    QAbstractListModel(parent)
{
    m_notifier = Solid::DeviceNotifier::instance();
    m_list = Solid::Device::listFromType(Solid::DeviceInterface::AudioInterface);
}

QVariant SoundCardModel::data(const QModelIndex &index, int role) const
{
    // Sanity check
    if (!index.isValid())
        return QVariant();

    // Check if role is supported
    if (role != Qt::DisplayRole && role != Qt::DecorationRole)
        return QVariant();

    Solid::Device device = m_list.at(index.row());
    Solid::AudioInterface *audio = device.as<Solid::AudioInterface>();

    if (audio->deviceType() == Solid::AudioInterface::AudioOutput) {
        qDebug() << device.udi() << device.product() << device.parentUdi();
        switch (role) {
            case Qt::DisplayRole:
                return audio->name();
            case Qt::DecorationRole:
                switch (audio->soundcardType()) {
                    case Solid::AudioInterface::Headset:
                        return QIcon::fromTheme("audio-headset");
                    default:
                        return QIcon::fromTheme("audio-card");
                }
        }
    }

    return QVariant();
}

int SoundCardModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_list.size();
}

#include "moc_soundcardmodel.cpp"
