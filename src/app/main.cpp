/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2011-2012 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
 *
 * $BEGIN_LICENSE:GPL2+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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

#include <QApplication>
#include <QLibraryInfo>
#include <QStandardPaths>
#include <QTranslator>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    // Setup application
    QApplication app(argc, argv);
    app.setApplicationName("System Preferences");
    app.setApplicationVersion("0.0.0");
    app.setOrganizationDomain("maui-project.org");
    app.setOrganizationName("Hawaii");

    // Locale name
    const QString locale = QLocale::system().name();

    // Translations
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + locale,
                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);

    QTranslator translator;
    QString localeDir = QStandardPaths::locate(
                            QStandardPaths::GenericDataLocation,
                            QLatin1String("hawaii-system-preferences/translations"),
                            QStandardPaths::LocateDirectory);
    translator.load(locale, localeDir);
    app.installTranslator(&translator);

    // Show main window
    MainWindow *win = new MainWindow();
    win->show();

    return app.exec();
}
