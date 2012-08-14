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

#ifndef PREFLET_H
#define PREFLET_H

#include <VPreferencesModule>

class QModelIndex;

class VSettings;

namespace Ui
{
    class DesktopScreenSaverPreflet;
}

class BackgroundCategoriesModel;
class BackgroundsModel;

class Preflet : public VPreferencesModule
{
    Q_OBJECT
public:
    explicit Preflet(QWidget *parent = 0);
    ~Preflet();

    virtual QString name() const;
    virtual QString comment() const;
    virtual QString iconName() const;
    virtual QStringList keywords() const;
    virtual VPreferencesModule::Category category() const;
    virtual int weight() const;

private slots:
    void slotBackgroundModeSelected(int index);
    void slotBackgroundCategorySelected(const QModelIndex &index);
    void slotBackgroundSelected(const QModelIndex &index);

private:
    Ui::DesktopScreenSaverPreflet *ui;
    VSettings *m_settings;
    BackgroundCategoriesModel *m_catModel;
    BackgroundsModel *m_model;
};

#endif // PREFLET_H
