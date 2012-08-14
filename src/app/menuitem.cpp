/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (c) 2012 Pier Luigi Fiorini
 * Copyright (c) 2007 Will Stephenson
 * Copyright (c) 2009 Ben Cooksley
 *
 * Author(s):
 *    Ben Cooksley <bcooksley@kde.org>
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *    Will Stephenson <wstephenson@kde.org>
 *
 * $BEGIN_LICENSE:GPL$
 *
 * System Preferences is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * System Preferences is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with System Preferences.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include <QList>
#include <QString>
#include <QVariant>
#include <QIcon>

#include <VPreferencesModule>

#include "menuitem.h"

static bool childIsLessThan(MenuItem *left, MenuItem *right)
{
    return left->weight() < right->weight();
}

class MenuItem::Private
{
public:
    Private() {}

    MenuItem *parent;
    QList<MenuItem *> children;
    VPreferencesModule::Category category;
    QString name;
    QString categoryText;
    int weight;
    QIcon icon;
    const VPreferencesModule *module;
};

MenuItem::MenuItem(MenuItem *itsParent)
    : d(new Private())
{
    d->parent = itsParent;
    setModule(0);

    if (d->parent)
        d->parent->children().append(this);
}

MenuItem::~MenuItem()
{
    qDeleteAll(d->children);
    delete d;
}

void MenuItem::sortChildrenByWeight()
{
    qSort(d->children.begin(), d->children.end(), childIsLessThan);
}

MenuItem *MenuItem::child(int index)
{
    return d->children.at(index);
}

QStringList MenuItem::keywords() const
{
    QStringList listOfKeywords;

    if (d->module)
        listOfKeywords << d->module->keywords();
    listOfKeywords << name();

    foreach(MenuItem * child, d->children)
    listOfKeywords += child->keywords();
    return listOfKeywords;
}

MenuItem *MenuItem::parent() const
{
    return d->parent;
}

QList<MenuItem *>& MenuItem::children() const
{
    return d->children;
}

const VPreferencesModule *MenuItem::module() const
{
    return d->module;
}

QIcon MenuItem::icon() const
{
    return d->icon;
}

QString MenuItem::name() const
{
    if (d->module)
        return d->module->name();
    return d->name;
}

QString MenuItem::comment() const
{
    if (d->module)
        return d->module->comment();
    return QString();
}

QString MenuItem::categoryText() const
{
    return d->categoryText;
}

int MenuItem::weight() const
{
    return d->weight;
}

bool MenuItem::menu() const
{
    if (d->module)
        return false;
    return true;
}

VPreferencesModule::Category MenuItem::category() const
{
    return d->category;
}

void MenuItem::setCategory(VPreferencesModule::Category category)
{
    setModule(0);

    switch (category) {
        case VPreferencesModule::PersonalCategory:
            d->name = QObject::tr("Personal");
            d->icon = QIcon::fromTheme("preferences-personal");
            break;
        case VPreferencesModule::HardwareCategory:
            d->name = QObject::tr("Hardware");
            d->icon = QIcon::fromTheme("preferences-hardware");
            break;
        case VPreferencesModule::SystemCategory:
            d->name = QObject::tr("System");
            d->icon = QIcon::fromTheme("preferences-system");
            break;
        case VPreferencesModule::OtherCategory:
            d->name = QObject::tr("Other");
            d->icon = QIcon::fromTheme("preferences-other");
            break;
    }
}

void MenuItem::setModule(const VPreferencesModule *module)
{
    if (!module) {
        d->module = 0;
        d->name = QString();
        d->categoryText = QString();
        d->icon = QIcon();
        d->weight = 100;
        return;
    }

    d->module = module;
    d->name = module->name();
    d->icon = QIcon::fromTheme(module->iconName());
    switch (module->category()) {
        case VPreferencesModule::PersonalCategory:
            d->categoryText = QObject::tr("Personal");
            break;
        case VPreferencesModule::HardwareCategory:
            d->categoryText = QObject::tr("Hardware");
            break;
        case VPreferencesModule::SystemCategory:
            d->categoryText = QObject::tr("System");
            break;
        case VPreferencesModule::OtherCategory:
            d->categoryText = QObject::tr("Other");
            break;
    }
    const QVariant itemWeight = module->weight();
    if (itemWeight.isValid())
        d->weight = itemWeight.toInt();
    else
        d->weight = 100;
}
