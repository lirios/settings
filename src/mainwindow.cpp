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
#include <QToolBar>
#include <QAction>
#include <QLineEdit>
#include <QStackedWidget>
#include <QStyledItemDelegate>
#include <QDebug>

#include <VStandardDirectories>
#include <VPreferencesModule>
#include <VPreferencesModulePlugin>

#include "mainwindow.h"
#include "categorydrawer.h"
#include "categorizedview.h"
#include "menumodel.h"
#include "menuitem.h"
#include "menuproxymodel.h"

using namespace VStandardDirectories;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_rootItem(0)
{
    // Set window icon and title
    setWindowTitle(tr("System Preferences"));
    setWindowIcon(QIcon::fromTheme("preferences-system"));

	// Actions
    m_overviewAction = new QAction(tr("Overview"), this);
    m_overviewAction->setEnabled(false);

    // Tool bar
	QToolBar *toolBar = new QToolBar(tr("Tool Bar"), this);
	toolBar->addAction(m_overviewAction);
    addToolBar(toolBar);

    // Stacked widget
    m_stackedWidget = new QStackedWidget(this);
    setCentralWidget(m_stackedWidget);

	// Search all the modules
    m_rootItem = new MenuItem(true, 0);
    populate();

    // Main view
    m_catDrawer = new CategoryDrawer();
    m_catView = new CategorizedView(this);
    m_catView->setSelectionMode(QAbstractItemView::SingleSelection);
    ///    m_catView->setSpacing(QDialog::spacingHint());
    m_catView->setCategoryDrawer(m_catDrawer);
    m_catView->setViewMode(QListView::IconMode);
    m_catView->setMouseTracking(true);
    m_catView->setFrameShape(QFrame::NoFrame);
    m_catView->viewport()->setAttribute(Qt::WA_Hover);

    // Delegate
#if 0
    KFileItemDelegate *delegate = new KFileItemDelegate(m_catView);
    delegate->setWrapMode(QTextOption::WordWrap);
#else
    QStyledItemDelegate *delegate = new QStyledItemDelegate(m_catView);
#endif
    m_catView->setItemDelegate(delegate);

    // Setup the model
    m_model = new MenuModel(m_rootItem, this);
    m_proxyModel = new MenuProxyModel(this);
    m_proxyModel->setCategorizedModel(true);
    m_proxyModel->setSourceModel(m_model);
    m_proxyModel->sort(0);
    m_catView->setModel(m_proxyModel);
#if 0
    connect(m_catView, SIGNAL(activated(QModelIndex)),
            this, SLOT(changeModule(QModelIndex)));
#endif

    // Add it to the stack and populate the model
    m_stackedWidget->insertWidget(0, m_catView);
    m_stackedWidget->setCurrentWidget(m_catView);

#if 0
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
    m_personalModel = new CategoriesModel(VPreferencesModule::PersonalCategory);
    ui->listViewPersonal->setModel(m_personalModel);
    m_hardwareModel = new CategoriesModel(VPreferencesModule::HardwareCategory);
    ui->listViewHardware->setModel(m_hardwareModel);
    m_systemModel = new CategoriesModel(VPreferencesModule::SystemCategory);
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
#endif
}

MainWindow::~MainWindow()
{
    delete m_rootItem;
}

void MainWindow::populate()
{
    if (!m_rootItem)
        return;

    QStringList dirs;
    dirs << QString("%1/preferences").arg(findDirectory(CommonPluginsDirectory))
         << QString("%1/preferences").arg(findDirectory(SystemPluginsDirectory));
    foreach(QString dir, dirs) {
        QDir pluginsDir(dir);
        foreach(QString fileName, pluginsDir.entryList(QDir::Files)) {
            QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
            VPreferencesModulePlugin *plugin = qobject_cast<VPreferencesModulePlugin *>(loader.instance());
            if (!plugin)
                continue;

            foreach(QString key, plugin->keys()) {
                VPreferencesModule *module = plugin->create(key);
                MenuItem *item = new MenuItem(false, m_rootItem);
                item->setModule(module);
                m_stackedWidget->addWidget(module);
                qDebug() << "Added" << item->name();
            }
        }
    }

    m_rootItem->sortChildrenByWeight();
}

void MainWindow::slotShowAllTriggered()
{
#if 0
    // Go to the first page
    ui->stackedWidget->setCurrentIndex(0);

    // Now that we are on the first page the action must be disabled
    ui->actionShowAll->setEnabled(false);

    // Show the search field because now we need it
    m_search->show();
#endif
}

void MainWindow::slotListViewClicked(const QModelIndex &index)
{
#if 0
    QAbstractItemModel *rawModel = const_cast<QAbstractItemModel *>(index.model());
    CategoriesModel *model = qobject_cast<CategoriesModel *>(rawModel);
    if (model) {
        // Find the plugin that was clicked
        VPreferencesModulePlugin *plugin = model->pluginAt(index.row());

        // If we already created the widget we should just use it
        foreach(QString key, plugin->keys()) {
            VPreferencesModule *module = m_modules.value(key);
            if (module) {
                QWidget *widget =

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
#endif
        }

#include "moc_mainwindow.cpp"
