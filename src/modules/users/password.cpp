/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2018 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include <QRandomGenerator>

#include "password.h"

#include <crypt.h>
#include <unistd.h>

Password::Password(QObject *parent)
    : QObject(parent)
{
}

QString Password::cryptPassword(const QString &password) const
{
    QByteArray alpha = "0123456789ABCDEFGHIJKLMNOPQRSTUVXYZ"
                       "abcdefghijklmnopqrstuvxyz./";
    QByteArray salt("$6$");
    int len = alpha.count();
    for (int i = 0; i < 16; i++)
        salt.append(alpha.at((QRandomGenerator::global()->generate() % len)));

    return QString::fromLatin1(::crypt(password.toUtf8().constData(), salt.constData()));
}
