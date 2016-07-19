/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2011-2016 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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
#include <QIcon>
#include <QPixmap>
#include <QStandardPaths>
#include <QTranslator>

#include "preflet.h"
#include "ui_preflet.h"
#include "soundcardmodel.h"

using namespace Hawaii::Settings;

Preflet::Preflet()
    : PreferencesModule()
    , ui(new Ui::Preflet)
    , m_translator(0)
    , m_savedVolume(0)
{
    ui->setupUi(this);

    // Load translations
    loadTranslations();

    // Set icons
    QIcon volumeLowIcon = QIcon::fromTheme("audio-volume-low-symbolic");
    QIcon volumeMaxIcon = QIcon::fromTheme("audio-volume-high-symbolic");
    ui->audioMin->setPixmap(volumeLowIcon.pixmap(QSize(22, 22)));
    ui->audioMax->setPixmap(volumeMaxIcon.pixmap(QSize(22, 22)));
    ui->alertVolumeMin->setPixmap(volumeLowIcon.pixmap(QSize(22, 22)));
    ui->alertVolumeMax->setPixmap(volumeMaxIcon.pixmap(QSize(22, 22)));

    m_model = new SoundCardModel(this);
    ui->hwListView->setModel(m_model);

    // Connect signals
    connect(ui->muteCheckBox, SIGNAL(clicked(bool)),
            this, SLOT(slotMuteClicked(bool)));
}

Preflet::~Preflet()
{
    delete ui;
    delete m_translator;
}

QString Preflet::name() const
{
    return tr("Sound");
}

QString Preflet::comment() const
{
    return tr("Change sound volume and event sounds");
}

QString Preflet::iconName() const
{
    return QLatin1String("multimedia-volume-control");
}

QStringList Preflet::keywords() const
{
    return tr("sound;audio;card;volume;fade;balance;bluetooth;headset").split(";");
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
                            QLatin1String("hawaii-settings/plugins/sound/translations"),
                            QStandardPaths::LocateDirectory);
    m_translator->load(locale, localeDir);
    QCoreApplication::instance()->installTranslator(m_translator);
}

void Preflet::slotMuteClicked(bool state)
{
    if (state) {
        // If mute is checked, save current volume and set slider value to 0
        m_savedVolume = ui->volumeSlider->value();
        ui->volumeSlider->setValue(0);
    } else {
        // Otherwise if unchecked, restore the saved volume
        ui->volumeSlider->setValue(m_savedVolume);
    }
}

#include "moc_preflet.cpp"
