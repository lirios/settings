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

#ifndef LOCALEMANAGER_H
#define LOCALEMANAGER_H

#include <QObject>

class LocaleManager : public QObject
{
    Q_OBJECT
public:
    explicit LocaleManager(QObject *parent = nullptr);

    Q_INVOKABLE QString languageFromCode(const QString &code);
    Q_INVOKABLE QString countryFromCode(const QString &code);
};

#endif // LOCALEMANAGER_H
