/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2011-2016 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include <QCoreApplication>
#include <QStandardPaths>
#include <QTranslator>

#include "preflet.h"
#include "ui_mimetypespreflet.h"
#include "typesmodel.h"

using namespace Hawaii::Settings;

Preflet::Preflet()
    : PreferencesModule()
    , ui(new Ui::MimeTypesPreflet)
    , m_translator(0)
{
    ui->setupUi(this);

    // Load translations
    loadTranslations();

    // Set icons
    ui->addButton->setIcon(QIcon::fromTheme("list-add"));
    ui->removeButton->setIcon(QIcon::fromTheme("list-remove"));
    ui->addExtensionButton->setIcon(QIcon::fromTheme("list-add"));
    ui->removeExtensionButton->setIcon(QIcon::fromTheme("list-remove"));

    // Model
    m_model = new TypesModel(this);
    ui->treeView->setModel(m_model);
}

Preflet::~Preflet()
{
    delete ui;
    delete m_translator;
    delete m_model;
}

QString Preflet::name() const
{
    return tr("MIME Types");
}

QString Preflet::comment() const
{
    return tr("Configure the association between MIME types and programs.");
}

QString Preflet::iconName() const
{
    return "preferences-desktop-wallpaper";
}

QStringList Preflet::keywords() const
{
    return tr("mime;types;association;program").split(";");
}

PreferencesModule::Category Preflet::category() const
{
    return PreferencesModule::PersonalCategory;
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
                            QLatin1String("hawaii-settings/plugins/mimetypes/translations"),
                            QStandardPaths::LocateDirectory);
    m_translator->load(locale, localeDir);
    QCoreApplication::instance()->installTranslator(m_translator);
}

#include "moc_preflet.cpp"
