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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <VPreferencesModule>

class QAction;
class QLineEdit;
class QStackedWidget;

class VCategorizedView;

class MenuItem;
class MenuModel;
class MenuProxyModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void slotOverviewTriggered();
    void slotListViewClicked(const QModelIndex &index);

private:
    QAction *m_overviewAction;
    QLineEdit *m_search;
    QStackedWidget *m_stackedWidget;
    QMap<VPreferencesModule::Category, MenuItem *> m_categories;
    VCategorizedView *m_catView;
    MenuItem *m_rootItem;
    MenuModel *m_model;
    MenuProxyModel *m_proxyModel;

    void createActions();
    void createToolBar();
    void populate();
};

#endif // MAINWINDOW_H
