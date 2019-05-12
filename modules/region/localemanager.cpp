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

#include <QLocale>

#include "localemanager.h"

LocaleManager::LocaleManager(QObject *parent)
    : QObject(parent)
{
}

QString LocaleManager::languageFromCode(const QString &code)
{
    QLocale locale(code);

    QString language = locale.nativeLanguageName();
    if (language.isEmpty())
        language = locale.languageToString(locale.language());

    return language;
}

QString LocaleManager::countryFromCode(const QString &code)
{
    QLocale locale(code);

    QString country = locale.nativeCountryName();
    if (country.isEmpty())
        country = locale.countryToString(locale.country());

    return country;
}
