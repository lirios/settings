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

#include <QtGui/QGuiApplication>

#include "waylandconfig.h"

WaylandConfig::WaylandConfig(QObject *parent)
    : QObject(parent)
    , m_connection(ClientConnection::fromQt())
    , m_registry(new Registry())
    , m_thread(new QThread())
    , m_management(Q_NULLPTR)
{
    if (m_connection) {
        m_connection->moveToThread(m_thread);
        m_thread->start();

        connect(m_registry, &Registry::interfacesAnnounced,
                this, &WaylandConfig::interfacesAnnounced);
        connect(m_registry, &Registry::outputAnnounced,
                this, &WaylandConfig::waylandOutputAnnounced);
        connect(m_registry, &Registry::outputRemoved,
                this, &WaylandConfig::waylandOutputRemoved);
        connect(m_registry, &Registry::outputManagementAnnounced,
                this, &WaylandConfig::outputManagementAnnounced);
        connect(m_registry, &Registry::outputManagementRemoved,
                this, &WaylandConfig::outputManagementRemoved);

        m_registry->create(m_connection->display());
        m_registry->setup();
    }
}

WaylandConfig::~WaylandConfig()
{
    delete m_registry;
    delete m_connection;

    m_thread->quit();
    m_thread->wait();
}

bool WaylandConfig::isConfigurationEnabled() const
{
    return m_management != Q_NULLPTR;
}

OutputManagement *WaylandConfig::outputManagement() const
{
    return m_management;
}

void WaylandConfig::interfacesAnnounced()
{
}

void WaylandConfig::waylandOutputAnnounced(quint32 name, quint32 version)
{
    Output *output = m_registry->createOutput(name, version, this);
    m_outputs.append({name, output});

    m_connection->flushRequests();
    m_connection->forceRoundTrip();

    Q_EMIT outputAdded(output);
}

void WaylandConfig::waylandOutputRemoved(quint32 name)
{
    auto it = m_outputs.begin();
    while (it++ != m_outputs.end()) {
        if (it->name == name) {
            Output *output = it->output;
            it = m_outputs.erase(it);
            Q_EMIT outputRemoved(output);
            break;
        }
    }
}

void WaylandConfig::outputManagementAnnounced(quint32 name, quint32 version)
{
    m_management = m_registry->createOutputManagement(name, version, this);
    Q_EMIT configurationEnabledChanged(true);
}

void WaylandConfig::outputManagementRemoved(quint32 name)
{
    Q_UNUSED(name);

    delete m_management;
    m_management = Q_NULLPTR;

    Q_EMIT configurationEnabledChanged(false);
}

#include "moc_waylandconfig.cpp"
