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
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>

#include "preflet.h"
#include "launchersettings.h"

using namespace Hawaii::SystemPreferences;

Preflet::Preflet()
    : PreferencesModule(QStringLiteral("desktop"))
    , m_item(0)
{
    // Register QML types
    qmlRegisterType<LauncherSettings>("Hawaii.SystemPreferences.Desktop",
                                      0, 1, "LauncherSettings");
}

Preflet::~Preflet()
{
    delete m_item;
}

QString Preflet::title() const
{
    return tr("Desktop");
}

QString Preflet::comment() const
{
    return tr("Configure desktop preferences");
}

QString Preflet::iconName() const
{
    return "preferences-desktop";
}

QStringList Preflet::keywords() const
{
    return tr("desktop;launcher;hot;corner").split(";");
}

PreferencesModule::Category Preflet::category() const
{
    return PreferencesModule::PersonalCategory;
}

QQuickItem *Preflet::item()
{
    // Return QtQuick item immediately if it was already created
    if (m_item)
        return m_item;

    // Create the QtQuick item
    QQmlEngine *engine = new QQmlEngine(this);
    QQmlComponent component(engine, QUrl("qrc:/desktop/qml/Preflet.qml"));
    QObject *object = component.create();
    m_item = qobject_cast<QQuickItem*>(object);
    return m_item;
}

#include "moc_preflet.cpp"
