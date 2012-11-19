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

#ifndef MENUITEM_H
#define MENUITEM_H

#include <VPreferencesModule>

class QString;
class QIcon;
template<typename T> class QList;

/**
 * @brief Provides a specific item in the list of modules or categories
 *
 * This provides convienent access to the list of modules, providing information about them
 * such as name, module information and its module object.\n
 * This is created automatically by System Settings, and is shared among all plugins and so should not
 * be modified under any circumstances.\n
 *
 * System Settings creates it in a tree like manner, with categories containing subcategories and modules,
 * and subcategories repeating this.\n
 *
 * The module object must be set, unless it is the top level item, otherwise using applications
 * will crash when attempting to sort the children by weight
 *
 * @author Ben Cooksley <bcooksley@kde.org>
 * @author Will Stephenson <wstephenson@kde.org>
 */
class MenuItem
{
public:
    /**
     * Creates a MenuItem.
     * @note Will not provide keywords, name, or a module item until a module has been set.
     *
     * @param parent The item it is parented to. Provide 0 for a top level item.
     */
    MenuItem(MenuItem *parent);

    /**
     * Destroys a MenuItem, including all children, the module object and the module information.
     *
     * @warning Destroys the KService and KCModuleInfo objects provided by module() and item().
     */
    ~MenuItem();

    /**
     * Provides the MenuItem for the child at the specified index.
     *
     * @param index The index of the child.
     * @returns The MenuItem object of the specified child.
     */
    MenuItem *child(int index);

    /**
     * Returns the list of keywords, which is used for searching the list of categories and modules.
     *
     * @note The parent items share all the keywords of their children.
     * @returns The list of keywords the item has.
     */
    QStringList keywords() const;

    /**
     * Returns the parent of this item.
     *
     * @returns The MenuItem object of this items parent.
     */
    MenuItem *parent() const;

    /**
     * Provides a list of all the children of this item.
     *
     * @returns The list of children this has.
     */
    QList<MenuItem *> &children() const;

    /**
     * Returns the module object of this item, which contains useful information about it.
     *
     * @returns The module object of this item if it has been set.
     */
    const VPreferencesModule *module() const;

    /**
     * Convenience function which provides the icon of the current item.
     *
     * @returns The icon of the item, if the module object has been set.
     */
    QIcon icon() const;

    /**
     * Convienence function which provides the name of the current item.
     *
     * @returns The name of the item, if the module object has been set.
     */
    QString name() const;

    /**
     * Convienence function which provides the comment of the current item.
     *
     * @returns The comment of the item, if the module object has been set.
     */
    QString comment() const;

    /**
     * Convienence function which provides the System Settings category of the current item.
     *
     * @returns The category of the item, if the module object has been set.
     */
    QString categoryText() const;

    /**
     * Provides information on which type the current item is.
     *
     * @returns true if it is a category.
     * @returns false if it is not a category.
     */
    bool menu() const;

    VPreferencesModule::Category category() const;
    void setCategory(VPreferencesModule::Category category);

    /**
     * Sets the module object, which is used to provide the module information, name and keywords
     * Applications will crash if it is not set, unless it is the top level item.
     *
     * @param module The module object to store.
     */
    void setModule(const VPreferencesModule *module);

private:
    class Private;
    Private *const d;
};

Q_DECLARE_METATYPE(MenuItem *)

#endif // MENUITEM_H
