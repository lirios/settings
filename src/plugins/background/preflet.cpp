/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2011-2013 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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
#include <QtCore/QUrl>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>

#include "preflet.h"
#include "wallpapersmodel.h"

using namespace Hawaii::SystemPreferences;

Preflet::Preflet()
    : PreferencesModule()
    , m_translator(0)
    , m_item(0)
{
    // Register QML types
    qmlRegisterType<WallpapersModel>("Hawaii.SystemPreferences.Background",
                                     0, 1, "WallpapersModel");

    // Load translations
    loadTranslations();
}

Preflet::~Preflet()
{
    delete m_translator;
    delete m_item;
}

QString Preflet::name() const
{
    return tr("Background");
}

QString Preflet::comment() const
{
    return tr("Change your background image to a wallpaper or photo");
}

QString Preflet::iconName() const
{
    return "preferences-desktop-wallpaper";
}

QStringList Preflet::keywords() const
{
    return tr("wallpaper;screen;desktop").split(";");
}

PreferencesModule::Category Preflet::category() const
{
    return PreferencesModule::PersonalCategory;
}

QQuickItem *Preflet::item()
{
    // Return QtQuick item immediately if it was already created
    if (m_item)
        return m_item;

    // Create the QtQuick item
    QQmlEngine *engine = new QQmlEngine(this);
    QQmlComponent component(engine, QUrl("qrc:/qml/Preflet.qml"));
    QObject *object = component.create();
    m_item = qobject_cast<QQuickItem*>(object);
    return m_item;
}

void Preflet::loadTranslations()
{
    // Current locale
    const QString locale = QLocale::system().name();

    // Remove translation of the previously loaded locale
    if (m_translator) {
        QCoreApplication::instance()->removeTranslator(m_translator);
        delete m_translator;
    }

    // Load translations
    m_translator = new QTranslator(this);
    QString localeDir = QStandardPaths::locate(
                            QStandardPaths::GenericDataLocation,
                            QStringLiteral("hawaii-system-preferences/plugins/background/translations"),
                            QStandardPaths::LocateDirectory);
    m_translator->load(locale, localeDir);
    QCoreApplication::instance()->installTranslator(m_translator);
}

#include "moc_preflet.cpp"
