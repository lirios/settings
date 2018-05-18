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

#ifndef WAYLANDCONFIG_H
#define WAYLANDCONFIG_H

#include <QtCore/QObject>
#include <QtCore/QThread>
#include <QtCore/QVector>

#include <KWayland/Client/connection_thread.h>
#include <KWayland/Client/registry.h>
#include <KWayland/Client/output.h>
#include <KWayland/Client/outputmanagement.h>

struct WaylandOutput {
    quint32 name;
    KWayland::Client::OutputDevice *output;
};

class WaylandConfig : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool configurationEnabled READ isConfigurationEnabled NOTIFY configurationEnabledChanged)
public:
    explicit WaylandConfig(QObject *parent = nullptr);
    ~WaylandConfig();

    bool isConfigurationEnabled() const;

    KWayland::Client::OutputManagement *outputManagement() const;

Q_SIGNALS:
    void outputAdded(KWayland::Client::OutputDevice *output);
    void outputRemoved(KWayland::Client::OutputDevice *output);
    void configurationEnabledChanged(bool value);

private:
    KWayland::Client::ConnectionThread *m_connection;
    KWayland::Client::Registry *m_registry;
    QThread *m_thread;
    QVector<WaylandOutput> m_outputs;
    KWayland::Client::OutputManagement *m_management;

private Q_SLOTS:
    void interfacesAnnounced();
    void outputDeviceAnnounced(quint32 name, quint32 version);
    void outputDeviceRemoved(quint32 name);
    void outputManagementAnnounced(quint32 name, quint32 version);
    void outputManagementRemoved(quint32 name);
};

#endif // WAYLANDCONFIG_H
