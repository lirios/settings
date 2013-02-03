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

#include <QWidget>

#include <Hawaii/SystemPreferences/SystemPreferencesExport>

QT_BEGIN_NAMESPACE

namespace Hawaii
{
    namespace SystemPreferences
    {
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
         *
         *     QString name() const;
         *     QString comment() const;
         *     QString iconName() const;
         *     QStringList keywords() const;
         *     PreferencesModule::Category category() const;
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
         *
         * QString MyPreferences::name() const
         * {
         *     return tr("Name");
         * }
         *
         * QString MyPreferences::comment() const
         * {
         *     return tr("Configure something.");
         * }
         *
         * QString MyPreferences::iconName() const
         * {
         *     return QLatin1String("preferences-something");
         * }
         *
         * QStringList MyPreferences::keywords() const
         * {
         *     return tr("something;something else").split(QLatin1Char(';'));
         * }
         *
         * PreferencesModule::Category category() const
         * {
         *     return PreferencesModule::PersonalCategory;
         * }
         * @endcode
         *
         * \author Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
         */
        class SYSTEMPREFERENCES_EXPORT PreferencesModule : public QWidget
        {
            Q_OBJECT
            Q_PROPERTY(bool requiresAdministrativePrivileges READ requiresAdministrativePrivileges)
            Q_ENUMS(Category)
        public:
            enum Category {
                //! Personal preferences.
                PersonalCategory,
                //! Hardware preferences.
                HardwareCategory,
                //! System preferences.
                SystemCategory,
                //! Other preferences.
                OtherCategory,
            };

            /**
             * Constructs a PreferencesModule object.
             */
            explicit PreferencesModule();

            /**
             * @returns the module's name.
             */
            virtual QString name() const = 0;

            /**
             * @returns the module's comment.
             */
            virtual QString comment() const = 0;

            /**
             * @returns the module's icon name.
             */
            virtual QString iconName() const = 0;

            /**
             * @returns the keywords associated with this module.
             */
            virtual QStringList keywords() const = 0;

            /**
             * @returns the category for this module.
             */
            virtual Category category() const = 0;

            /**
             * Some preference modules requires administrative privileges
             * to configure their settings.  If your preferences modules
             * requires administrative privileges return true.
             * This method returns false by default.
             */
            virtual bool requiresAdministrativePrivileges() const;
        };
    }
}

QT_END_NAMESPACE

#endif // SYSTEMPREFERENCES_PREFERENCESMODULE_H
