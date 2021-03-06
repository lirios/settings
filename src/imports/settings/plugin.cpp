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

#include <QQmlComponent>
#include <QQmlExtensionPlugin>

#include "authorizedaction.h"
#include "module.h"
#include "modulesmodel.h"

class SettingsPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")
public:
    void registerTypes(const char *uri)
    {
        Q_ASSERT(QByteArray("Liri.Settings") == QByteArray(uri));

        // @uri Liri.Settings
        qmlRegisterType<AuthorizedAction>(uri, 1, 0, "AuthorizedAction");
        qmlRegisterUncreatableType<Module>(uri, 1, 0, "Module", QLatin1String("Cannot instantiate Module"));
        qmlRegisterType<ModulesModel>(uri, 1, 0, "ModulesModel");
        qmlRegisterType<ModulesProxyModel>(uri, 1, 0, "ModulesProxyModel");
    }
};

#include "plugin.moc"
