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
#include <QDirIterator>
#include <QStandardPaths>
#include <QTranslator>
#include <QUrl>

#include <VSettings>
#include <VDesktopFile>

#include "preflet.h"
#include "ui_desktoppreflet.h"
#include "wallpapermodel.h"
#include "backgrounditemdelegate.h"

using namespace Hawaii::SystemPreferences;

Preflet::Preflet()
    : PreferencesModule()
    , ui(new Ui::DesktopPreflet)
    , m_translator(0)
{
    ui->setupUi(this);

    // Load translations
    loadTranslations();

    // Load icons
    ui->bgPreview->setPixmap(QIcon::fromTheme("monitor").pixmap(QSize(256, 256)));
    ui->monitorIcon->setPixmap(QIcon::fromTheme("monitor").pixmap(QSize(256, 256)));

    // Settings
    m_settings = new VSettings("org.hawaii.desktop");
    m_shellSettings = new VSettings("org.hawaii.greenisland");
    connect(m_shellSettings, SIGNAL(changed()),
            this, SLOT(shellSettingsChanged()));

    // Wallpapers model
    m_wallpaperModel = new WallpaperModel(this);
    ui->bgList->setItemDelegate(new BackgroundItemDelegate(this));
    ui->bgList->setModel(m_wallpaperModel);
    connect(m_wallpaperModel, SIGNAL(wallpapersAdded()),
            this, SLOT(slotAllWallpapersLoaded()));

    // Load settings before connecting the signals to avoid changing the
    // settings twice (if you take a look at the code below you will notice
    // that for example the launcher icon size slider changes the spin box
    // and vice-versa)
    loadSettings();

    // Connect signals for the UI
    connect(ui->launcherIconSizeSlider, SIGNAL(valueChanged(int)),
            ui->launcherIconSizeSpin, SLOT(setValue(int)));
    connect(ui->launcherIconSizeSpin, SIGNAL(valueChanged(int)),
            this, SLOT(slotLauncherIconSizeChanged(int)));
    connect(ui->launcherAlignment, SIGNAL(currentIndexChanged(int)),
            this, SLOT(slotLauncherAlignmentChanged(int)));
    connect(ui->bgCategory, SIGNAL(currentIndexChanged(int)),
            this, SLOT(slotBackgroundCategorySelected(int)));
    connect(ui->bgList, SIGNAL(clicked(QModelIndex)),
            ui->bgList, SIGNAL(activated(QModelIndex)));
    connect(ui->bgList, SIGNAL(activated(QModelIndex)),
            this, SLOT(slotBackgroundSelected(QModelIndex)));
}

Preflet::~Preflet()
{
    delete ui;
    delete m_translator;
    delete m_wallpaperModel;
    delete m_settings;
    delete m_shellSettings;
}

QString Preflet::name() const
{
    return tr("Desktop");
}

QString Preflet::comment() const
{
    return tr("Configure desktop, wallpaper and screen saver.");
}

QString Preflet::iconName() const
{
    return "preferences-desktop-wallpaper";
}

QStringList Preflet::keywords() const
{
    return tr("desktop;launcher;wallpaper;screen saver;hot corner").split(";");
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
                            QLatin1String("hawaii-system-preferences/plugins/desktop/translations"),
                            QStandardPaths::LocateDirectory);
    m_translator->load(locale, localeDir);
    QCoreApplication::instance()->installTranslator(m_translator);
}

void Preflet::loadSettings()
{
    // Launcher icon size
    ui->launcherIconSizeSpin->setValue(m_shellSettings->value("launcher/icon-size").toInt());
    ui->launcherIconSizeSlider->setValue(ui->launcherIconSizeSpin->value());

    // Launcher alignment
    QString alignment = m_shellSettings->value("launcher/alignment").toString();
    int index = 2;
    if (alignment == QLatin1String("left"))
        index = 0;
    else if (alignment == QLatin1String("right"))
        index = 1;
    ui->launcherAlignment->setCurrentIndex(index);

    // Load all the coatings
    slotBackgroundCategorySelected(0);
}

void Preflet::shellSettingsChanged()
{
    QVariant value = m_shellSettings->value("launcher/icon-size");
    ui->launcherIconSizeSpin->setValue(value.toInt());

    QString alignment = m_shellSettings->value("launcher/alignment").toString();
    int index = 2;
    if (alignment == QLatin1String("left"))
        index = 0;
    else if (alignment == QLatin1String("right"))
        index = 1;
    ui->launcherAlignment->setCurrentIndex(index);
}

void Preflet::slotLauncherAlignmentChanged(int index)
{
    switch (index) {
        case 0:
            m_shellSettings->setValue("launcher/alignment", QLatin1String("left"));
            break;
        case 1:
            m_shellSettings->setValue("launcher/alignment", QLatin1String("right"));
            break;
        default:
            m_shellSettings->setValue("launcher/alignment", QLatin1String("bottom"));
    }
}

void Preflet::slotLauncherIconSizeChanged(int value)
{
    ui->launcherIconSizeSlider->setValue(value);
    m_shellSettings->setValue("launcher/icon-size", QVariant(value));
}

void Preflet::slotAllWallpapersLoaded()
{
    // Select the current configured wallpaper
    if (ui->bgCategory->currentIndex() == 0) {
        QString wallpaperPath = m_settings->value("background/wallpaper-uri").toUrl().toLocalFile();
        ui->bgList->selectionModel()->select(m_wallpaperModel->indexOf(wallpaperPath),
                                             QItemSelectionModel::Select | QItemSelectionModel::Current);
        slotBackgroundSelected(m_wallpaperModel->indexOf(wallpaperPath));
    }
}

void Preflet::slotBackgroundCategorySelected(int index)
{
    switch (index) {
        case 0: {
            // Populate the list with wallpapers
            QStringList paths = QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation);
            foreach(QString dir, paths) {
                QString path = QString("%1/wallpapers").arg(dir);
                QDirIterator it(path, QDir::Dirs | QDir::Readable | QDir::NoDotAndDotDot,
                                QDirIterator::FollowSymlinks);
                while (it.hasNext()) {
                    QDir dir(it.next());
                    if (dir.exists("metadata.desktop"))
                        m_wallpaperModel->addPath(dir.absolutePath());
                }
            }
        }
        break;
        default:
            break;
    }
}

void Preflet::slotBackgroundModeSelected(int index)
{
}

void Preflet::slotBackgroundSelected(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    QString type = m_wallpaperModel->data(index, WallpaperModel::TypeRole).toString();
    if (type == "wallpaper") {
        QString name = m_wallpaperModel->data(index, Qt::DisplayRole).toString();
        QString resolution = m_wallpaperModel->data(index, WallpaperModel::ResolutionRole).toString();
        QString path = m_wallpaperModel->data(index, WallpaperModel::AbsoluteFilePathRole).toString();
        ui->bgName->setText("<b>" + name + "</b>");
        ui->bgSize->setText(resolution);

        // Save settings
        m_settings->setValue("background/type", "wallpaper");
        m_settings->setValue("background/wallpaper-uri", QVariant::fromValue(QUrl::fromLocalFile(path)));
    }
}

#include "moc_preflet.cpp"
