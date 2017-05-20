/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2016 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtCore/QLoggingCategory>
#include <QtCore/QStandardPaths>
#include <QtCore/QTranslator>
#include <QtCore/QLibraryInfo>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickWindow>
#include <QtQuickControls2/QQuickStyle>

Q_DECLARE_LOGGING_CATEGORY(PREFERENCES)
Q_LOGGING_CATEGORY(PREFERENCES, "liri.settings")

static void loadQtTranslations()
{
#ifndef QT_NO_TRANSLATION
    QString locale = QLocale::system().name();

    // Load Qt translations
    QTranslator *qtTranslator = new QTranslator(qGuiApp);
    if (qtTranslator->load(QStringLiteral("qt_%1").arg(locale), QLibraryInfo::location(QLibraryInfo::TranslationsPath))) {
        qApp->installTranslator(qtTranslator);
    } else {
        delete qtTranslator;
    }
#endif
}

static void loadShellTranslations()
{
#ifndef QT_NO_TRANSLATION
    QString locale = QLocale::system().name();

    // Find the translations directory
    const QString path = QLatin1String("liri/settings/translations/app");
    const QString translationsDir =
        QStandardPaths::locate(QStandardPaths::GenericDataLocation,
                               path,
                               QStandardPaths::LocateDirectory);

    // Load shell translations
    QTranslator *appTranslator = new QTranslator(qGuiApp);
    if (appTranslator->load(QStringLiteral("%1/settings_%3").arg(translationsDir, locale))) {
        QCoreApplication::installTranslator(appTranslator);
    } else if (locale == QLatin1String("C") ||
                locale.startsWith(QLatin1String("en"))) {
        // English is the default, it's translated anyway
        delete appTranslator;
    }
#endif
}

static void loadModuleTranslations()
{
#ifndef QT_NO_TRANSLATION
    QString locale = QLocale::system().name();

    // Load translations of each module
    const QString rootDir = QLatin1String("liri/settings/modules");
    const QString modulesPath =
            QStandardPaths::locate(QStandardPaths::GenericDataLocation,
                                   rootDir,
                                   QStandardPaths::LocateDirectory);
    QDir modulesDir(modulesPath);
    Q_FOREACH (const QFileInfo &info, modulesDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        const QString name = info.fileName();

        // Find the translations directory
        const QString path = QLatin1String("liri/settings/translations/modules");
        const QString translationsDir =
            QStandardPaths::locate(QStandardPaths::GenericDataLocation,
                                   path,
                                   QStandardPaths::LocateDirectory);

        // Load shell translations
        QTranslator *appTranslator = new QTranslator(qGuiApp);
        if (appTranslator->load(QStringLiteral("%1/%2_%3").arg(translationsDir, name, locale))) {
            QCoreApplication::installTranslator(appTranslator);
        } else if (locale == QLatin1String("C") ||
                    locale.startsWith(QLatin1String("en"))) {
            // English is the default, it's translated anyway
            delete appTranslator;
        }
    }
#endif
}

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // Set the X11 WML_CLASS so X11 desktops can find the desktop file
    qputenv("RESOURCE_NAME", "io.liri.Settings");

    // Setup application
    QGuiApplication app(argc, argv);
    app.setApplicationName(QLatin1String("Settings"));
    app.setApplicationVersion(QLatin1String(LIRISETTINGS_VERSION));
    app.setOrganizationDomain(QLatin1String("liri.io"));
    app.setOrganizationName(QLatin1String("Liri"));
    app.setDesktopFileName(QLatin1String("io.liri.Settings.desktop"));

    QQuickStyle::setStyle(QLatin1String("Material"));

    // Load translations
    loadQtTranslations();
    loadShellTranslations();
    loadModuleTranslations();

    // Setup QML engine and show the main window
    QQmlApplicationEngine engine(QUrl(QLatin1String("qrc:/qml/main.qml")));

    return app.exec();
}
