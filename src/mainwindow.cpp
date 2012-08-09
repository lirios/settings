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

#include <QDir>
#include <QPluginLoader>
#include <QLineEdit>

#include <VPreferencesModule>
#include <VPreferencesModulePlugin>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set window icon
    setWindowIcon(QIcon::fromTheme("preferences-system"));

    // Create a spacer in order to right align the search field
    QWidget *spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->toolBar->addWidget(spacer);

    // Create search line edit
    m_search = new QLineEdit(this);
    ui->toolBar->addWidget(m_search);

    // Disable action, will enable it at the right moment
    ui->actionShowAll->setEnabled(false);

    // Create models
    m_personalModel = new CategoriesModel(VPreferencesModulePlugin::PersonalCategory);
    ui->listViewPersonal->setModel(m_personalModel);
    m_hardwareModel = new CategoriesModel(VPreferencesModulePlugin::HardwareCategory);
    ui->listViewHardware->setModel(m_hardwareModel);
    m_systemModel = new CategoriesModel(VPreferencesModulePlugin::SystemCategory);
    ui->listViewSystem->setModel(m_systemModel);

    // Connect signals
    connect(ui->actionShowAll, SIGNAL(triggered()),
            this, SLOT(slotShowAllTriggered()));
    connect(ui->listViewPersonal, SIGNAL(clicked(QModelIndex)),
            this, SLOT(slotListViewClicked(QModelIndex)));
    connect(ui->listViewHardware, SIGNAL(clicked(QModelIndex)),
            this, SLOT(slotListViewClicked(QModelIndex)));
    connect(ui->listViewSystem, SIGNAL(clicked(QModelIndex)),
            this, SLOT(slotListViewClicked(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_systemModel;
    delete m_hardwareModel;
    delete m_personalModel;
}

void MainWindow::slotShowAllTriggered()
{
    // Go to the first page
    ui->stackedWidget->setCurrentIndex(0);

    // Now that we are on the first page the action must be disabled
    ui->actionShowAll->setEnabled(false);

    // Show the search field because now we need it
    m_search->show();
}

void MainWindow::slotListViewClicked(const QModelIndex &index)
{
    QAbstractItemModel *rawModel = const_cast<QAbstractItemModel *>(index.model());
    CategoriesModel *model = qobject_cast<CategoriesModel *>(rawModel);
    if (model) {
        // Find the plugin that was clicked
        VPreferencesModulePlugin *plugin = model->pluginAt(index.row());

        // If we already created the widget we should just use it
        int index = -1;
        QWidget *widget = m_modules.value(plugin->name());
        if (widget)
            index = ui->stackedWidget->indexOf(widget);
        else {
            // Not found, add it to the dictionary and the stacked widget
            widget = plugin->module();
            index = ui->stackedWidget->addWidget(widget);
            m_modules.insert(plugin->name(), widget);
        }

        // Activate the widget
        ui->stackedWidget->setCurrentIndex(index);

        // Enable the action to go to the first page
        ui->actionShowAll->setEnabled(true);

        // Hide the search field because it cannot be used now
        m_search->hide();
    }
}

#include "moc_mainwindow.cpp"
