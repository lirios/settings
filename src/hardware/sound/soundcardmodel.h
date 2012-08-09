#ifndef SOUNDCARDMODEL_H
#define SOUNDCARDMODEL_H

#include <QAbstractListModel>

#include <VDevice>

class VDeviceNotifier;

class SoundCardModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SoundCardModel(QObject *parent = 0);

    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual int rowCount(const QModelIndex &parent) const;

private:
    VDeviceNotifier *m_notifier;
    QList<VDevice> m_list;
};

#endif // SOUNDCARDMODEL_H
