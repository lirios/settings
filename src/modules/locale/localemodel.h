/****************************************************************************
 * This file is part of Liri.
 *
 * Copyright (C) 2019 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#ifndef LOCALEMODEL_H
#define LOCALEMODEL_H

#include <QAbstractListModel>
#include <QLocale>

class LocaleItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString language READ language CONSTANT)
    Q_PROPERTY(QString country READ country CONSTANT)
    Q_PROPERTY(QString code READ code CONSTANT)
public:
    explicit LocaleItem(const QLocale &locale, QObject *parent = nullptr);

    QString language() const;
    QString country() const;
    QString code() const;

private:
    QString m_language;
    QString m_country;
    QString m_code;
};

class LocaleModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        Language = Qt::UserRole + 1,
        Country,
        Code
    };

    explicit LocaleModel(QObject *parent = nullptr);
    ~LocaleModel();

    QHash<int, QByteArray> roleNames() const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    static void populate(LocaleModel *model);

private:
    QVector<LocaleItem *> m_list;

private Q_SLOTS:
    void appendItem(LocaleItem *item);
};

#endif // LOCALEMODEL_H
