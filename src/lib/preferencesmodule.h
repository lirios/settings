/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2012-2013 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#ifndef SYSTEMPREFERENCES_PREFERENCESMODULE_H
#define SYSTEMPREFERENCES_PREFERENCESMODULE_H

#include <QtQuick/QQuickItem>

#include <Hawaii/SystemPreferences/SystemPreferencesExport>

QT_BEGIN_NAMESPACE

namespace Hawaii
{
    namespace SystemPreferences
    {
        class PreferencesModulePrivate;

        /**
         * \brief Base class for all preferences modules.
         *
         * Preferences modules are realized as plugins that are loaded by the
         * the System Preferences application.
         *
         * To write a preferences module you have to create two classes, one that
         * inherits from PreferencesPlugin and another that implements the
         * module user interface and inherits from PreferencesModule.
         *
         * Plugin header file:
         *
         * @code
         * #include <Hawaii/SystemPreferences/PreferencesPlugin>
         *
         * using namespace Hawaii::SystemPreferences;
         *
         * class MyPreferencesPlugin : public PreferencesModulePlugin
         * {
         *     Q_OBJECT
         *     Q_PLUGIN_METADATA(IID "org.hawaii.SystemPreferences.PreferencesModuleFactoryInterface" FILE "mypreferences.json")
         * public:
         *     explicit MyPreferencesPlugin(QObject *parent = 0);
         *
         *     QStringList keys() const;
         *     PreferencesModule *create(const QString &key) const;
         * };
         * @endcode
         *
         * Module header file:
         *
         * @code
         * #include <Hawaii/SystemPreferences/PreferencesModule>
         *
         * using namespace Hawaii::SystemPreferences;
         *
         * class MyPreferences : public PreferencesModule
         * {
         *     Q_OBJECT
         *     Q_INTERFACES(PreferencesModule)
         * public:
         *     explicit MyPreferences();
         * };
         * @endcode
         *
         * Plugin C++ source code file:
         *
         * @code
         * MyPreferencesPlugin::MyPreferencesPlugin(QObject *parent)
         *     : PreferencesModulePlugin(parent)
         * {
         * }
         *
         * QStringList MyPreferencesPlugin::keys() const
         * {
         *     return QStringList() << "mypreferences";
         * }
         *
         * PreferencesModule *MyPreferencesPlugin::create(const QString &key) const
         * {
         *     if (key.toLower() == "mypreferences")
         *         return new MyPreferences();
         *     return 0;
         * }
         * @endcode
         *
         * Module C++ source code file:
         *
         * @code
         * #include "mypreferences.h"
         *
         * MyPreferences::MyPreferences()
         *     : PreferencesModule(parent)
         * {
         *     // ... Create the UI here ...
         * }
         * @endcode
         *
         * \author Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
         */
        class SYSTEMPREFERENCES_EXPORT PreferencesModule : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(bool requiresAdministrativePrivileges READ requiresAdministrativePrivileges)
        public:
            /**
             * Constructs a PreferencesModule object.
             */
            explicit PreferencesModule(const QString &name, QObject *parent = 0);

            /**
             * Destructs a PreferencesModule object.
             */
            ~PreferencesModule();

            /**
             * @returns the module's name.
             */
            QString name() const;

            /**
             * Some preference modules requires administrative privileges
             * to configure their settings.  If your preferences modules
             * requires administrative privileges this returns true.
             * This method returns false by default.
             */
            virtual bool requiresAdministrativePrivileges() const;

            /**
             * @returns the identifier for the action that requires
             * administrative privileges.
             *
             * If this module doesn't require administrative privileges, this
             * methods returns an empty string.
             */
            virtual QString administrativeActionId() const;

            /**
             * Creates a QQmlComponent object for this module.
             */
            virtual QQmlComponent *createComponent(QQmlEngine *engine, QObject *parent = 0) = 0;

        private:
            Q_DECLARE_PRIVATE(PreferencesModule)
            PreferencesModulePrivate *const d_ptr;
        };
    }
}

QT_END_NAMESPACE

#endif // SYSTEMPREFERENCES_PREFERENCESMODULE_H
