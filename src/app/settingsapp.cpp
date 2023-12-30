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

#include <QDebug>
#include <QQmlApplicationEngine>

#include "settingsapp.h"

SettingsApp::SettingsApp(bool isService, QObject *parent)
    : QObject(parent)
{
    if (isService) {
        auto dbusService = new Liri::DBusService(Liri::DBusService::Single, this);
        connect(dbusService, &Liri::DBusService::activationRequested,
                this, &SettingsApp::handleActivationRequested);
        connect(dbusService, &Liri::DBusService::openRequested,
                this, &SettingsApp::handleOpenRequested);
    }
}

void SettingsApp::load(const QString &moduleName)
{
    auto engine = new QQmlApplicationEngine(this);
    connect(engine, &QQmlApplicationEngine::warnings, this, [](const QList<QQmlError> &warnings) {
        for (auto &error : warnings)
            qWarning() << error.toString();
    });
    connect(engine, &QQmlApplicationEngine::objectCreated, this, [moduleName](QObject *object, const QUrl) {
        if (!moduleName.isEmpty())
            QMetaObject::invokeMethod(object, "loadModuleByName",
                                      Q_ARG(QVariant, moduleName));
    });

    engine->load(QUrl(QLatin1String("qrc:/qt/qml/settings/qml/main.qml")));
}

void SettingsApp::handleActivationRequested(const QVariantMap &data)
{
    Q_UNUSED(data)

    load();
}

void SettingsApp::handleOpenRequested(const QList<QUrl> &urls, const QVariantMap &data)
{
    Q_UNUSED(data)

    load(urls.count() > 0 ? urls[0].toString() : QString());
}
