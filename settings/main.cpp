/****************************************************************************
 * This file is part of Hawaii.
 *
 * Copyright (C) 2011-2016 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include "config.h"
#include "cmakedirs.h"

Q_DECLARE_LOGGING_CATEGORY(PREFERENCES)
Q_LOGGING_CATEGORY(PREFERENCES, "hawaii.settings")

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

static void loadShellTranslations(const QString &vendor, const QString &name)
{
#ifndef QT_NO_TRANSLATION
    QString locale = QLocale::system().name();

    // Find the translations directory
    const QString path = QLatin1String("hawaii-settings/translations/shells/%1/%2");
    const QString translationsDir =
        QStandardPaths::locate(QStandardPaths::GenericDataLocation,
                               path.arg(vendor, name),
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
#endif
}

static void loadModuleTranslations(const QString &vendor)
{
#ifndef QT_NO_TRANSLATION
    QString locale = QLocale::system().name();

    // Load translations of each module
    const QString rootDir = QLatin1String("hawaii-settings/modules/%1");
    const QString modulesPath =
            QStandardPaths::locate(QStandardPaths::GenericDataLocation,
                                   rootDir.arg(vendor),
                                   QStandardPaths::LocateDirectory);
    QDir modulesDir(modulesPath);
    Q_FOREACH (const QFileInfo &info, modulesDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        const QString name = info.fileName();

        // Find the translations directory
        const QString path = QLatin1String("hawaii-settings/translations/modules/%1");
        const QString translationsDir =
            QStandardPaths::locate(QStandardPaths::GenericDataLocation,
                                   path.arg(vendor),
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

    // Setup application
    QGuiApplication app(argc, argv);
    app.setApplicationName(QLatin1String("Settings"));
    app.setApplicationVersion(QLatin1String(SETTINGS_VERSION_STRING));
    app.setOrganizationDomain(QLatin1String("hawaiios.org"));
    app.setOrganizationName(QLatin1String("Hawaii"));
#if QT_VERSION >= QT_VERSION_CHECK(5, 7, 0)
    app.setDesktopFileName(QLatin1String("org.hawaiios.Settings.desktop"));
#endif

    QQuickStyle::setStyle(QLatin1String("Material"));

    // Find plugin
    const QString vendor = QLatin1String("hawaii");
    const QString plugin = QLatin1String("desktopshell");
    const QString path = QLatin1String("hawaii-settings/shells/%1/%2/main.qml");
    QString fileName = QStandardPaths::locate(QStandardPaths::GenericDataLocation,
                                              path.arg(vendor, plugin));
    if (fileName.isEmpty()) {
        qCWarning(PREFERENCES) << "Failed to find" << plugin << "plugin, aborting...";
        return 1;
    }

    // Load translations
    loadQtTranslations();
    loadShellTranslations(vendor, plugin);
    loadModuleTranslations(vendor);

    // Setup QML engine and show the main window
    qCDebug(PREFERENCES) << "Loading:" << fileName;
    QQmlApplicationEngine engine(QUrl::fromLocalFile(fileName));

    return app.exec();
}
