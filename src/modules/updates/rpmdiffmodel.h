// SPDX-FileCopyrightText: 2021 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef LIRI_SETTINGS_UPDATES_RPMDIFFMODEL_H
#define LIRI_SETTINGS_UPDATES_RPMDIFFMODEL_H

#include <QAbstractListModel>

class RpmDiffItem {
public:
    RpmDiffItem(QString n, QString d, QString c)
        : name(n)
        , description(d)
        , category(c)
    {
    }

    QString name;
    QString description;
    QString category;
};

class RpmDiffModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
public:
    enum Role {
        NameRole = Qt::UserRole + 1,
        DescriptionRole,
        CategoryRole,
    };
    Q_ENUM(Role);

    explicit RpmDiffModel(QObject *parent = nullptr);
    ~RpmDiffModel();

    QHash<int,QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addItem(RpmDiffItem *item);
    void removeItem(RpmDiffItem *item);
    void clearItems();

signals:
    void countChanged();

private:
    QVector<RpmDiffItem *> m_items;
};

#endif // LIRI_SETTINGS_UPDATES_RPMDIFFMODEL_H
