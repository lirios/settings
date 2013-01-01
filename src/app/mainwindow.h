/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2011-2013 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <Hawaii/SystemPreferences/PreferencesModule>

class QAction;
class QLineEdit;
class QStackedWidget;
class QTranslator;

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

protected:
    void changeEvent(QEvent *event);

private slots:
    void slotOverviewTriggered();
    void slotSearchChanged(const QString &search);
    void slotListViewClicked(const QModelIndex &index);

private:
    QTranslator *m_translator;
    QAction *m_overviewAction;
    QLineEdit *m_search;
    QStackedWidget *m_stackedWidget;
    QMap<Hawaii::SystemPreferences::PreferencesModule::Category, MenuItem *> m_categories;
    VCategorizedView *m_catView;
    MenuItem *m_rootItem;
    MenuModel *m_model;
    MenuProxyModel *m_proxyModel;

    void loadTranslations();
    void createActions();
    void createToolBar();
    void populate();
};

#endif // MAINWINDOW_H
