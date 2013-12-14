/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2011-2013 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include <QtWidgets/QApplication>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtQuick/QQuickWindow>

#include "config.h"
#include "cmakedirs.h"
#include "categoriesmodel.h"
#include "prefletsmodel.h"
#include "prefletsproxymodel.h"

int main(int argc, char *argv[])
{
    // Setup application
    QApplication app(argc, argv);
    app.setApplicationName("System Preferences");
    app.setApplicationVersion(SYSTEMPREFERENCES_VERSION_STRING);
    app.setOrganizationDomain("hawaii.org");
    app.setOrganizationName("Hawaii");
    app.addLibraryPath(QStringLiteral(INSTALL_LIBDIR "/hawaii/plugins"));

    QQmlEngine engine;

    qmlRegisterType<CategoriesModel>("Hawaii.SystemPreferences", 0, 1, "CategoriesModel");
    qmlRegisterType<PrefletsModel>("Hawaii.SystemPreferences", 0, 1, "PrefletsModel");
    qmlRegisterType<PrefletsProxyModel>("Hawaii.SystemPreferences", 0, 1, "PrefletsProxyModel");

    QQmlComponent component(&engine);
    component.loadUrl(QUrl("qrc:/qml/main.qml"));
    if (!component.isReady()) {
        qWarning("%s", qPrintable(component.errorString()));
        return 1;
    }

    QObject *topLevel = component.create();
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
    if (!window) {
        qWarning("Error: Your root item has to be a Window");
        return 1;
    }

    QObject::connect(&engine, SIGNAL(quit()), &app, SLOT(quit()));
    window->show();
    return app.exec();
}
