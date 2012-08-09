/****************************************************************************
 * This file is part of Preferences.
 *
 * Copyright (c) 2011-2012 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Preferences is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Preferences is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Preferences.  If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include <VApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    VApplication app(argc, argv);
    app.setApplicationName("System Preferences");
    app.setApplicationVersion("0.0.0");
    app.setOrganizationDomain("maui-os.org");
    app.setOrganizationName("Maui");
    app.setIdentifier("org.maui.Preferences");
    app.setWindowIcon(QIcon::fromTheme("preferences-system"));

    MainWindow *win = new MainWindow();
    win->show();

    return app.exec();
}
