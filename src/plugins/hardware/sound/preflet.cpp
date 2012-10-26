/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (c) 2011-2012 Pier Luigi Fiorini
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

#include <QIcon>
#include <QPixmap>

#include "preflet.h"
#include "ui_preflet.h"
#include "soundcardmodel.h"

Preflet::Preflet(QWidget *parent) :
    VPreferencesModule(parent),
    ui(new Ui::Preflet),
    m_savedVolume(0)
{
    ui->setupUi(this);

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
}

QString Preflet::name() const
{
    return tr("Sound");
}

QString Preflet::comment() const
{
    return tr("Configure sound.");
}

QString Preflet::iconName() const
{
    return "preferences-desktop-sound";
}

QStringList Preflet::keywords() const
{
    return tr("sound;audio").split(";");
}

VPreferencesModule::Category Preflet::category() const
{
    return VPreferencesModule::HardwareCategory;
}

int Preflet::weight() const
{
    return 50;
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
