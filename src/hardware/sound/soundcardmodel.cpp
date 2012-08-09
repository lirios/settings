
#include <QDebug>
#include <QIcon>

#include <VDeviceNotifier>
#include <VAudioInterface>

#include "soundcardmodel.h"

SoundCardModel::SoundCardModel(QObject *parent) :
    QAbstractListModel(parent)
{
    m_notifier = VDeviceNotifier::instance();
    m_list = VDevice::listFromType(VDeviceInterface::AudioInterface);
}

QVariant SoundCardModel::data(const QModelIndex &index, int role) const
{
    // Sanity check
    if (!index.isValid())
        return QVariant();

    // Check if role is supported
    if (role != Qt::DisplayRole && role != Qt::DecorationRole)
        return QVariant();

    VDevice device = m_list.at(index.row());
    VAudioInterface *audio = device.as<VAudioInterface>();

    if (audio->deviceType() == VAudioInterface::AudioOutput) {
        qDebug() << device.udi() << device.product() << device.parentUdi();
        switch (role) {
            case Qt::DisplayRole:
                return audio->name();
            case Qt::DecorationRole:
                switch (audio->soundcardType()) {
                    case VAudioInterface::Headset:
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
