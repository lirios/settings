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

#ifndef SYSTEMPREFERENCES_PREFERENCESMODULEPLUGIN_H
#define SYSTEMPREFERENCES_PREFERENCESMODULEPLUGIN_H

#include <QObject>
#include <QtCore/qplugin.h>

#include <Hawaii/SystemPreferences/SystemPreferencesExport>

QT_BEGIN_HEADER
QT_BEGIN_NAMESPACE

namespace Hawaii
{
    namespace SystemPreferences
    {
        class PreferencesModule;

#define PreferencesModuleFactoryInterface_iid "org.hawaii.SystemPreferences.PreferencesModuleFactoryInterface"

        /** \addtogroup gui Gui Kit
         *  @{
         */

        /**
         * \class PreferencesModulePlugin vpreferencesmoduleplugin.h <PreferencesModulePlugin>
         *
         * \author Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
         */
        class SYSTEMPREFERENCES_EXPORT PreferencesModulePlugin : public QObject
        {
            Q_OBJECT
        public:
            /**
             * Contructs the PreferencesModulePlugin object.
             */
            explicit PreferencesModulePlugin(QObject *parent = 0);

            /**
             * Destructs the PreferencesModulePlugin object.
             */
            ~PreferencesModulePlugin();

            /**
             * Return the keys corresponding to the module objects that can be created.
             */
            virtual QStringList keys() const = 0;

            /**
             * Creates the preferences module object that corresponds to \a key.
             */
            virtual PreferencesModule *create(const QString &key) const = 0;
        };

        /** @}*/
    }
}

QT_END_NAMESPACE
QT_END_HEADER

#endif // SYSTEMPREFERENCES_PREFERENCESMODULEPLUGIN_H
