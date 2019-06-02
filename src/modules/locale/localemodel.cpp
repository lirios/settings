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

#include <QtConcurrent/QtConcurrent>
#include <QDebug>

#include "localemodel.h"

LocaleItem::LocaleItem(const QLocale &locale, QObject *parent)
    : QObject(parent)
{
    m_language = locale.nativeLanguageName();
    if (m_language.isEmpty())
        m_language = locale.languageToString(locale.language());

    m_country = locale.nativeCountryName();
    if (m_country.isEmpty())
        m_country = locale.countryToString(locale.country());

    m_code = locale.name();

    if (!m_code.endsWith(QStringLiteral(".UTF-8"), Qt::CaseInsensitive))
        m_code += QStringLiteral(".UTF-8");
}

QString LocaleItem::language() const
{
    return m_language;
}

QString LocaleItem::country() const
{
    return m_country;
}

QString LocaleItem::code() const
{
    return m_code;
}

LocaleModel::LocaleModel(QObject *parent)
    : QAbstractListModel(parent)
{
    QtConcurrent::run(LocaleModel::populate, this);
}

LocaleModel::~LocaleModel()
{
    qDeleteAll(m_list);
}

QHash<int, QByteArray> LocaleModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(Language, QByteArrayLiteral("language"));
    roles.insert(Country, QByteArrayLiteral("country"));
    roles.insert(Code, QByteArrayLiteral("code"));
    return roles;
}

int LocaleModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_list.size();
}

QVariant LocaleModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    LocaleItem *item = m_list.at(index.row());

    switch (role) {
    case Language:
        return item->language();
    case Country:
        return item->country();
    case Code:
        return item->code();
    default:
        break;
    }

    return QVariant();
}

void LocaleModel::populate(LocaleModel *model)
{
    QList<QLocale> allLocales = QLocale::matchingLocales(QLocale::AnyLanguage, QLocale::AnyScript, QLocale::AnyCountry);

    for (const auto locale : allLocales) {
        if (locale.name() == QLatin1String("C"))
            continue;

        auto item = new LocaleItem(locale);
        item->moveToThread(model->thread());

        QMetaObject::invokeMethod(model, "appendItem", Q_ARG(LocaleItem *, item));
    }
}

void LocaleModel::appendItem(LocaleItem *item)
{
    beginInsertRows(QModelIndex(), m_list.count(), m_list.count());
    m_list.append(item);
    endInsertRows();
}
