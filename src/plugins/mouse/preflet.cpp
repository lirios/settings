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

#include <QCoreApplication>
#include <QStandardPaths>
#include <QTranslator>

#include "preflet.h"
#include "ui_mousepreflet.h"

using namespace Hawaii::SystemPreferences;

Preflet::Preflet()
    : PreferencesModule()
    , ui(new Ui::MousePreflet)
    , m_translator(0)
{
    ui->setupUi(this);

    // Load translations
    loadTranslations();
}

Preflet::~Preflet()
{
    delete ui;
    delete m_translator;
}

QString Preflet::name() const
{
    return tr("Mouse & Touchpad");
}

QString Preflet::comment() const
{
    return tr("Set your mouse and touchpad preferences");
}

QString Preflet::iconName() const
{
    return QLatin1String("input-mouse");
}

QStringList Preflet::keywords() const
{
    return tr("pointer;mouse;click;double;button;trackpad;trackball;touchpad;tap").split(";");
}

PreferencesModule::Category Preflet::category() const
{
    return PreferencesModule::HardwareCategory;
}

void Preflet::changeEvent(QEvent *event)
{
    switch (event->type()) {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        case QEvent::LocaleChange:
            loadTranslations();
            break;
        default:
            break;
    }

    QWidget::changeEvent(event);
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
                            QLatin1String("hawaii-system-preferences/plugins/mouse/translations"),
                            QStandardPaths::LocateDirectory);
    m_translator->load(locale, localeDir);
    QCoreApplication::instance()->installTranslator(m_translator);
}

#include "moc_preflet.cpp"
