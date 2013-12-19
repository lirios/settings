/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (C) 2013 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QPluginLoader>
#include <QtGui/QIcon>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>

#include <Hawaii/SystemPreferences/PreferencesModulePlugin>

#include "prefletsmodel.h"
#include "cmakedirs.h"

PrefletsModel::PrefletsModel(QObject *parent)
    : QAbstractListModel(parent)
{
    // QML engine and context
    m_engine = new QQmlEngine(this);

    // Populate the model
    beginInsertRows(QModelIndex(), 0, 0);
    populate();
    endInsertRows();
}

QHash<int, QByteArray> PrefletsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[IconNameRole] = "iconName";
    roles[CommentRole] = "comment";
    roles[CategoryRole] = "category";
    roles[CategoryNameRole] = "categoryName";
    roles[ItemRole] = "item";
    return roles;
}

QVariant PrefletsModel::data(const QModelIndex &index, int role) const
{
    PreferencesModule *module = m_modules.at(index.row());

    switch (role) {
    case Qt::DecorationRole:
        return QIcon::fromTheme(module->iconName());
    case Qt::DisplayRole:
    case TitleRole:
        return module->title();
    case IconNameRole:
        return module->iconName();
    case CommentRole:
        return module->comment();
    case CategoryRole:
        return module->category();
    case CategoryNameRole: {
        switch (module->category()) {
        case PreferencesModule::PersonalCategory:
            return QStringLiteral("personal");
        case PreferencesModule::HardwareCategory:
            return QStringLiteral("hardware");
        case PreferencesModule::SystemCategory:
            return QStringLiteral("system");
        }
    }
    case ItemRole: {
        QQmlComponent *component = m_components.value(module->name());
        if (component)
            return QVariant::fromValue(m_items.value(module->name()));
        return QVariant();
    }
    default:
        break;
    }

    return QVariant();
}

int PrefletsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_modules.size();
}

QQuickItem *PrefletsModel::createItem(int index)
{
    if (index < 0)
        return nullptr;

    PreferencesModule *module = m_modules.at(index);
    if (!module)
        return nullptr;

    QQuickItem *item = nullptr;
    QQmlComponent *component = m_components.value(module->name());
    if (component) {
        item = m_items.value(module->name());
        if (!item) {
            item = qobject_cast<QQuickItem *>(component->create());
            if (component->isError())
                qWarning("Couldn't create component for %s: %s",
                         qPrintable(module->name()),
                         qPrintable(component->errorString()));
            else
                m_items.insert(module->name(), item);
        }
    }

    return item;
}

void PrefletsModel::populate()
{
    // Search and append modules
    const QStringList libPaths = QCoreApplication::libraryPaths();
    const QString pathSuffix = QStringLiteral("/preferences/");
    foreach (const QString &libPath, libPaths) {
        QDir dir(libPath + pathSuffix);
        if (!dir.exists())
            continue;

        foreach (const QString &fileName, dir.entryList(QDir::Files)) {
            QPluginLoader loader(dir.absoluteFilePath(fileName));
            PreferencesModulePlugin *plugin = qobject_cast<PreferencesModulePlugin *>(loader.instance());
            if (!plugin) {
                qWarning() << "Couldn't load" << fileName << loader.errorString();
                continue;
            }

            foreach (const QString &key, plugin->keys()) {
                // Skip already registered modules
                if (m_components.contains(key))
                    continue;

                // Append module
                PreferencesModule *module = plugin->create(key);
                m_modules.append(module);

                // Create the QML component
                QQmlComponent *component = module->createComponent(m_engine, this);
                m_components.insert(key, component);
            }
        }
    }
}

#include "moc_prefletsmodel.cpp"
