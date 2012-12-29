/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2011-2012 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
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

#include <QDebug>
#include <QDir>
#include <QPluginLoader>
#include <QToolBar>
#include <QAction>
#include <QLineEdit>
#include <QStackedWidget>
#include <QStyledItemDelegate>

#include <VCategorizedView>

#include <Hawaii/SystemPreferences/PreferencesModulePlugin>

#include "mainwindow.h"
#include "categorydrawer.h"
#include "menuitem.h"
#include "menumodel.h"
#include "menuproxymodel.h"
#include "cmakedirs.h"

using namespace Hawaii::SystemPreferences;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set window icon and title
    setWindowTitle(tr("System Preferences"));
    setWindowIcon(QIcon::fromTheme("preferences-system"));

    // Search field
    m_search = new QLineEdit(this);
    m_search->setPlaceholderText(tr("Keywords"));
    connect(m_search, SIGNAL(textChanged(QString)),
            this, SLOT(slotSearchChanged(QString)));

    // Actions
    createActions();

    // Tool bar
    createToolBar();

    // Stacked widget
    m_stackedWidget = new QStackedWidget(this);
    setCentralWidget(m_stackedWidget);

    // Search all the modules
    m_rootItem = new MenuItem(0);
    m_model = new MenuModel(m_rootItem, this);
    populate();

    // Main view
    m_catView = new VCategorizedView(m_stackedWidget);
    m_catView->setViewMode(QListView::IconMode);
    m_catView->setIconSize(QSize(64, 64));
    m_catView->setGridSizeOwn(QSize(128, 128));
    m_catView->setWordWrap(true);
    m_catView->setWrapping(true);
    m_catView->setUniformItemSizes(true);
    m_catView->setMouseTracking(true);
    m_catView->setSelectionMode(QAbstractItemView::NoSelection);
    m_catView->setCategoryDrawer(new CategoryDrawer(m_catView));

    // Setup the model
    m_proxyModel = new MenuProxyModel(this);
    m_proxyModel->setCategorizedModel(true);
    m_proxyModel->setSourceModel(m_model);
    m_proxyModel->sort(0);
    m_catView->setModel(m_proxyModel);

    connect(m_catView, SIGNAL(clicked(QModelIndex)),
            m_catView, SIGNAL(activated(QModelIndex)));
    connect(m_catView, SIGNAL(activated(QModelIndex)),
            this, SLOT(slotListViewClicked(QModelIndex)));

    // Add it to the stack and populate the model
    m_stackedWidget->insertWidget(0, m_catView);
    m_stackedWidget->setCurrentWidget(m_catView);
}

MainWindow::~MainWindow()
{
    delete m_rootItem;
}

void MainWindow::createActions()
{
    m_overviewAction = new QAction(tr("Overview"), this);
    m_overviewAction->setEnabled(false);
    connect(m_overviewAction, SIGNAL(triggered()),
            this, SLOT(slotOverviewTriggered()));
}

void MainWindow::createToolBar()
{
    QToolBar *toolBar = new QToolBar(tr("Tool Bar"), this);
    toolBar->addAction(m_overviewAction);

    QWidget *spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
    toolBar->addWidget(spacerWidget);

    QAction *searchAction = toolBar->addWidget(m_search);
    searchAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
    connect(searchAction, SIGNAL(triggered()),
            m_search, SLOT(setFocus()));

    addToolBar(toolBar);
}

void MainWindow::populate()
{
    QDir pluginsDir(QStringLiteral("%1/preferences").arg(INSTALL_PLUGINSDIR));
    foreach(QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        PreferencesModulePlugin *plugin = qobject_cast<PreferencesModulePlugin *>(loader.instance());
        if (!plugin)
            continue;

        foreach(QString key, plugin->keys()) {
            PreferencesModule *module = plugin->create(key);

            // Create the category if needed
            PreferencesModule::Category category = module->category();
            MenuItem *parent = m_categories.value(category, 0);
            if (!parent) {
                parent = new MenuItem(m_rootItem);
                parent->setCategory(category);
                m_categories[category] = parent;
                m_model->addException(parent);
                qDebug() << "Create new category" << parent->name();
            }

            // Create the item and append its widget to the stack
            MenuItem *item = new MenuItem(parent);
            item->setModule(module);
            m_stackedWidget->addWidget(module);
            qDebug() << "Added" << item->name() << "under category" << parent->name();
        }
    }
}

void MainWindow::slotOverviewTriggered()
{
    // Go to the first page
    m_stackedWidget->setCurrentIndex(0);

    // Now that we are on the first page the action must be disabled
    m_overviewAction->setEnabled(false);

    // Show the search field because now we need it
    m_search->show();
}

void MainWindow::slotSearchChanged(const QString &search)
{
    m_proxyModel->setFilterRegExp(search);
}

void MainWindow::slotListViewClicked(const QModelIndex &index)
{
    MenuItem *item = index.data(Qt::UserRole).value<MenuItem *>();
    if (item->module()) {
        // Show the module
        m_stackedWidget->setCurrentWidget((PreferencesModule *)item->module());

        // Enable the action to go to the first page
        m_overviewAction->setEnabled(true);

        // Hide the search field because it cannot be used now
        m_search->hide();
    }
}

#include "moc_mainwindow.cpp"
