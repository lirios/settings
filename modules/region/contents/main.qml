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

import QtQuick 2.0
import QtQuick.Controls 2.0
import Fluid.Controls 1.0 as FluidControls
import QtGSettings 1.0
import Liri.Settings 1.0
import Liri.Settings.Region 1.0

ModulePage {
    GSettings {
        id: localeSettings
        schema.id: "io.liri.session.locale"
        schema.path: "/io/liri/session/locale/"
    }

    LanguageDialog {
        id: langDialog
    }

    FormatsDialog {
        id: formatsDialog
    }

    ModuleContainer {
        FluidControls.ListItem {
            text: qsTr("Language")
            valueText: {
                if (localeSettings.language)
                    return qsTr("%1 (%2)").arg(LocaleManager.languageFromCode(localeSettings.language)).arg(LocaleManager.countryFromCode(localeSettings.language));
                return qsTr("%1 (%2)").arg(SystemLocale.language).arg(SystemLocale.country);
            }

            onClicked: langDialog.open()
        }

        FluidControls.ListItem {
            text: qsTr("Formats")
            valueText: {
                if (localeSettings.region)
                    return qsTr("%1 (%2)").arg(LocaleManager.languageFromCode(localeSettings.region)).arg(LocaleManager.countryFromCode(localeSettings.region));
                return qsTr("%1 (%2)").arg(SystemLocale.language).arg(SystemLocale.country);
            }
            onClicked: formatsDialog.open()
        }
    }
}
