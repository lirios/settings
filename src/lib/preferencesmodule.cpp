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

#include <QtCore/QCoreApplication>
#include <QtCore/QStandardPaths>
#include <QtCore/QTranslator>

#include "preferencesmodule.h"
#include "preferencesmodule_p.h"

namespace Hawaii
{
    namespace SystemPreferences
    {
        /*
         * PreferencesModulePrivate
         */

        PreferencesModulePrivate::PreferencesModulePrivate(PreferencesModule *parent)
            : q_ptr(parent)
            , translator(0)
        {
        }

        void PreferencesModulePrivate::loadTranslations()
        {
            // Current locale
            const QString locale = QLocale::system().name();

            // Remove translation of the previously loaded locale
            if (translator) {
                QCoreApplication::instance()->removeTranslator(translator);
                translator->deleteLater();
                translator = 0;
            }

            // Load translations
            const QString directory = QString("hawaii-system-preferences/plugins/%1/translations").arg(name);
            translator = new QTranslator(q_ptr);
            QString localeDir = QStandardPaths::locate(
                                    QStandardPaths::GenericDataLocation,
                                    directory,
                                    QStandardPaths::LocateDirectory);
            translator->load(locale, localeDir);
            QCoreApplication::instance()->installTranslator(translator);
        }

        /*
         * PreferencesModule
         */

        PreferencesModule::PreferencesModule(const QString &name, QObject *parent)
            : QObject(parent)
            , d_ptr(new PreferencesModulePrivate(this))
        {
            Q_D(PreferencesModule);
            d->name = name;
            d->loadTranslations();
        }

        PreferencesModule::~PreferencesModule()
        {
            delete d_ptr;
        }

        QString PreferencesModule::name() const
        {
            Q_D(const PreferencesModule);
            return d->name;
        }

        bool PreferencesModule::requiresAdministrativePrivileges() const
        {
            return false;
        }

        QString PreferencesModule::administrativeActionId() const
        {
            return QStringLiteral("");
        }
    }
}

#include "moc_preferencesmodule.cpp"
