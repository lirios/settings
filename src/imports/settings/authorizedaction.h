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

#ifndef LIRI_SETTINGS_AUTHORIZEDACTION_H
#define LIRI_SETTINGS_AUTHORIZEDACTION_H

#include <QObject>

class AuthorizedActionPrivate;

class AuthorizedAction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString actionId READ actionId WRITE setActionId NOTIFY actionIdChanged)
    Q_PROPERTY(bool authorized READ isAuthorized NOTIFY authorizedChanged)
    Q_DECLARE_PRIVATE(AuthorizedAction)
public:
    explicit AuthorizedAction(QObject *parent = nullptr);

    QString actionId() const;
    void setActionId(const QString &actionId);

    bool isAuthorized() const;

    Q_INVOKABLE void authorize();

Q_SIGNALS:
    void actionIdChanged();
    void authorizedChanged();

private:
    AuthorizedActionPrivate *const d_ptr;
};

#endif // LIRI_SETTINGS_AUTHORIZEDACTION_H
