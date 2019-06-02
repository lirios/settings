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

#ifndef OUTPUTDEVICE_H
#define OUTPUTDEVICE_H

#include <QDBusArgument>
#include <QSize>

struct Mode {
    QString name;
    QSize size;
    int refreshRate;
};
Q_DECLARE_METATYPE(Mode)

inline QDBusArgument &operator<<(QDBusArgument &argument, const Mode &mode)
{
    argument.beginStructure();
    argument << mode.name;
    argument << mode.size;
    argument << mode.refreshRate;
    argument.endStructure();
    return argument;
}

inline const QDBusArgument &operator>>(const QDBusArgument &argument, Mode &mode)
{
    argument.beginStructure();
    argument >> mode.name;
    argument >> mode.size;
    argument >> mode.refreshRate;
    argument.endStructure();
    return argument;
}

#endif // OUTPUTDEVICE_H
