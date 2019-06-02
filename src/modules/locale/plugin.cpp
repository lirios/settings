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

#include <QQmlExtensionPlugin>
#include <QQmlComponent>

#include "localefiltermodel.h"
#include "localemanager.h"
#include "localemodel.h"
#include "systemlocale.h"

template<typename T>
static QObject *instance(QQmlEngine *, QJSEngine *)
{
    return new T();
}

class LocaleSettingsPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface/1.0")
public:
    void registerTypes(const char *uri)
    {
        Q_ASSERT(strcmp(uri, "Liri.Settings.Locale") == 0);

        // @uri Liri.Settings.Locale
        qmlRegisterSingletonType<LocaleManager>(uri, 1, 0, "LocaleManager", &instance<LocaleManager>);
        qmlRegisterSingletonType<SystemLocale>(uri, 1, 0, "SystemLocale", &instance<SystemLocale>);
        qmlRegisterType<LocaleFilterModel>(uri, 1, 0, "LocaleFilterModel");
        qmlRegisterType<LocaleModel>(uri, 1, 0, "LocaleModel");
    }
};

#include "plugin.moc"
