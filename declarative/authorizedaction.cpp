/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2017 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>

#include "authorizedaction.h"

AuthorizedAction::AuthorizedAction(QObject *parent)
    : QObject(parent)
    , m_authorized(false)
{
}

QString AuthorizedAction::actionId() const
{
    return m_actionId;
}

void AuthorizedAction::setActionId(const QString &actionId)
{
    if (m_actionId == actionId)
        return;

    m_actionId = actionId;
    Q_EMIT actionIdChanged();
}

bool AuthorizedAction::isAuthorized() const
{
    return m_authorized;
}

void AuthorizedAction::authorize()
{
    // Ignore if permission is already acquired
    if (m_authorized)
        return;

    GError *error = nullptr;

    auto subject = polkit_unix_process_new_for_owner(QCoreApplication::applicationPid(), 0, -1);
    auto p = polkit_permission_new_sync(m_actionId.toLatin1().constData(), subject, nullptr, &error);
    if (p) {
        g_signal_connect(p, "notify", G_CALLBACK(&AuthorizedAction::on_permission_changed), this);

        if (g_permission_get_can_acquire(p)) {
            if (g_permission_acquire(p, nullptr, &error)) {
                m_authorized = true;
                Q_EMIT authorizedChanged();
            } else {
                qWarning("Cannot acquire permission \"%s\": %s", m_actionId.toLatin1().constData(), error->message);
            }
        } else {
            qWarning("Permission \"%s\" cannot be acquired", m_actionId.toLatin1().constData());
        }
    } else {
        qWarning("Cannot ask permission \"%s\": %s", m_actionId.toLatin1().constData(), error->message);
        g_error_free(error);
    }
}

void AuthorizedAction::on_permission_changed(GPermission *perm, GParamSpec *pspec, gpointer data)
{
    Q_UNUSED(pspec);

    AuthorizedAction *action = static_cast<AuthorizedAction *>(data);
    const bool isAuthorized = g_permission_get_allowed(G_PERMISSION(perm));
    if (action->isAuthorized() && !isAuthorized) {
        action->m_authorized = isAuthorized;
        Q_EMIT action->authorizedChanged();
    }
}
