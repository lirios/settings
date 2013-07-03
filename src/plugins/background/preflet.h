/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2013 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#ifndef PREFLET_H
#define PREFLET_H

#include <Hawaii/SystemPreferences/PreferencesModule>

class QTranslator;

namespace Hawaii
{
    namespace SystemPreferences
    {
        class Preflet : public PreferencesModule
        {
            Q_OBJECT
        public:
            explicit Preflet();
            ~Preflet();

            QString name() const;
            QString comment() const;
            QString iconName() const;
            QStringList keywords() const;
            PreferencesModule::Category category() const;

            QQuickItem *item();

        private:
            QTranslator *m_translator;
            QQuickItem *m_item;

            void loadTranslations();
        };
    }
}

#endif // PREFLET_H
