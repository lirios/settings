/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2011-2013 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
 *
 * $BEGIN_LICENSE:LGPL2.1+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include <QtCore/QStandardPaths>
#include <QtCore/QUrl>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlContext>
#include <QtCore/QDebug>

#include "preflet.h"
#include "backgroundsmodel.h"
#include "colorsmodel.h"

using namespace Hawaii::SystemPreferences;

Preflet::Preflet()
    : PreferencesModule(QStringLiteral("background"))
{
    // Register QML types
    qmlRegisterType<BackgroundsModel>("Hawaii.SystemPreferences.Background",
                                      1, 0, "BackgroundsModel");
    qmlRegisterType<ColorsModel>("Hawaii.SystemPreferences.Background",
                                 1, 0, "ColorsModel");
}

QQmlComponent *Preflet::createComponent(QQmlEngine *engine, QObject *parent)
{
    return new QQmlComponent(engine,
                             QUrl("qrc:/background/qml/Preflet.qml"),
                             parent);
}

#include "moc_preflet.cpp"
