/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2013 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include <QtCore/QCoreApplication>
#include <QtCore/QStandardPaths>
#include <QtCore/QTranslator>
#include <QtCore/QUrl>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>

#include "networkpreflet.h"

using namespace Hawaii::SystemPreferences;

NetworkPreflet::NetworkPreflet()
    : PreferencesModule(QStringLiteral("network"))
    , m_item(0)
{
}

NetworkPreflet::~NetworkPreflet()
{
    delete m_item;
}

QString NetworkPreflet::title() const
{
    return tr("Network");
}

QString NetworkPreflet::comment() const
{
    return tr("Control how you connect to the Internet");
}

QString NetworkPreflet::iconName() const
{
    return "preferences-system-network";
}

QStringList NetworkPreflet::keywords() const
{
    return tr("net;network;ethernet;wifi;wired;wireless").split(";");
}

PreferencesModule::Category NetworkPreflet::category() const
{
    return PreferencesModule::HardwareCategory;
}

QQuickItem *NetworkPreflet::item()
{
    // Return QtQuick item immediately if it was already created
    if (m_item)
        return m_item;

    // Create the QtQuick item
    QQmlEngine *engine = new QQmlEngine(this);
    QQmlComponent component(engine, QUrl("qrc:/qml/NetworkPreflet.qml"));
    QObject *object = component.create();
    m_item = qobject_cast<QQuickItem*>(object);
    return m_item;
}

#include "moc_networkpreflet.cpp"
