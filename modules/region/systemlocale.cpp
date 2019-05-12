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

#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QLocale>

#include "systemlocale.h"

const QString interfaceName = QStringLiteral("org.freedesktop.locale1");
const QString objectPath = QStringLiteral("/org/freedesktop/locale1");

SystemLocale::SystemLocale(QObject *parent)
    : QObject(parent)
{
    m_interface = new QDBusInterface(interfaceName, objectPath, interfaceName,
                                     QDBusConnection::systemBus(), this);

   QStringList locale = qvariant_cast<QStringList>(m_interface->property("Locale"));
   for (const QString &entry : locale) {
       QStringList nameValue = entry.split(QLatin1Char('='));
       if (nameValue.length() == 2)
           m_localeCache[nameValue.at(0)] = nameValue.at(1);
   }

   updateLanguage();
   updateCountry();
}

QString SystemLocale::language() const
{
    return m_language;
}

QString SystemLocale::country() const
{
    return m_country;
}

QString SystemLocale::code() const
{
    return m_localeCache[QStringLiteral("LANG")];
}

void SystemLocale::setCode(const QString &code)
{
    QStringList newLocale;
    QMapIterator<QString, QString> i(m_localeCache);
    while (i.hasNext()) {
        i.next();

        QString newValue = i.key() + QLatin1String("=") + i.value();
        newLocale.append(newValue);
    }

    auto pcall = m_interface->asyncCall(QStringLiteral("SetLocale"), newLocale, true);
    auto watcher = new QDBusPendingCallWatcher(pcall, this);
    connect(watcher, &QDBusPendingCallWatcher::finished, this, [this, code](QDBusPendingCallWatcher *self) {
        QDBusPendingReply<> reply = *self;
        if (!reply.isError()) {
            m_localeCache[QStringLiteral("LANG")] = code;
            Q_EMIT codeChanged();
            updateLanguage();
            updateCountry();
        }
        self->deleteLater();
    });
}

void SystemLocale::updateLanguage()
{
    QLocale locale(code());

    m_language = locale.nativeLanguageName();
    if (m_language.isEmpty())
        m_language = locale.languageToString(locale.language());

    Q_EMIT languageChanged();
}

void SystemLocale::updateCountry()
{
    QLocale locale(code());

    m_country = locale.nativeCountryName();
    if (m_country.isEmpty())
        m_country = locale.countryToString(locale.country());

    Q_EMIT countryChanged();
}
