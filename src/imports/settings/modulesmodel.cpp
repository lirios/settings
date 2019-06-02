/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2018 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include <QDir>
#include <QStandardPaths>
#include <QThread>

#include "modulesmodel.h"

/*
 * ModulesModelTask
 */

ModulesModelTask::ModulesModelTask(QObject *parent)
    : QObject(parent)
{
}

void ModulesModelTask::populate()
{
    qDeleteAll(m_plugins);

    QStringList list = QStandardPaths::locateAll(QStandardPaths::GenericDataLocation,
                                                 QLatin1String("liri-settings/modules"),
                                                 QStandardPaths::LocateDirectory);
    for (const QString &location : qAsConst(list)) {
        QDir dir(location);
        QStringList modules = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
        for (const QString &module : qAsConst(modules)) {
            QDir moduleDir(dir.absoluteFilePath(module));
            QStringList files = moduleDir.entryList(QDir::Files);
            for (const QString &fileName : qAsConst(files)) {
                if (fileName != QLatin1String("metadata.desktop"))
                    continue;

                // Skip modules already added
                if (m_pluginsMap.contains(module))
                    continue;

                Module *plugin = new Module(moduleDir.absoluteFilePath(fileName));
                if (plugin->isValid()) {
                    m_plugins.append(plugin);
                    m_pluginsMap[module] = plugin;
                }
            }
        }
    }

    std::sort(m_plugins.begin(), m_plugins.end(), [](const Module *a, const Module *b) {
        return a->categoryName() < b->categoryName();
    });

    Q_EMIT populated();
}

/*
 * ModulesModel
 */

ModulesModel::ModulesModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_task(new ModulesModelTask())
    , m_thread(new QThread())
{
    m_task->moveToThread(m_thread);
    m_thread->start();
}

ModulesModel::~ModulesModel()
{
    m_task->deleteLater();

    m_thread->quit();
    m_thread->wait();
}

QHash<int, QByteArray> ModulesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(NameRole, QByteArrayLiteral("name"));
    roles.insert(CategoryRole, QByteArrayLiteral("category"));
    roles.insert(CategoryNameRole, QByteArrayLiteral("categoryName"));
    roles.insert(TitleRole, QByteArrayLiteral("title"));
    roles.insert(CommentRole, QByteArrayLiteral("comment"));
    roles.insert(IconNameRole, QByteArrayLiteral("iconName"));
    roles.insert(KeywordsRole, QByteArrayLiteral("keywords"));
    roles.insert(MainScriptRole, QByteArrayLiteral("mainScriptUrl"));
    return roles;
}

int ModulesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_task->m_plugins.count();
}

QVariant ModulesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_task->m_plugins.count())
        return QVariant();

    Module *plugin = m_task->m_plugins.at(index.row());
    if (!plugin)
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        return plugin->title();
    case NameRole:
        return plugin->name();
    case CategoryRole:
        return plugin->category();
    case CategoryNameRole:
        switch (plugin->category()) {
        case Module::PersonalCategory:
            return tr("Personal");
        case Module::HardwareCategory:
            return tr("Hardware");
        case Module::SystemCategory:
            return tr("System");
        default:
            break;
        }
        return QString();
    case TitleRole:
        return plugin->title();
    case IconNameRole:
        return plugin->iconName();
    case KeywordsRole:
        return plugin->keywords();
    case MainScriptRole:
        return plugin->mainScriptUrl();
    default:
        break;
    }

    return QVariant();
}

Module *ModulesModel::getByName(const QString &name) const
{
    return m_task->m_pluginsMap[name];
}

void ModulesModel::componentComplete()
{
    beginResetModel();
    m_task->populate();
    endResetModel();
}

ModulesProxyModel::ModulesProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

Module::Category ModulesProxyModel::category() const
{
    return m_category;
}

void ModulesProxyModel::setCategory(Module::Category category)
{
    if (m_category == category)
        return;

    m_category = category;
    invalidate();
    Q_EMIT categoryChanged();
}

bool ModulesProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    const auto modelIndex = sourceModel()->index(source_row, 0, source_parent);
    const auto category = static_cast<Module::Category>(sourceModel()->data(modelIndex, ModulesModel::CategoryRole).toInt());
    return category == m_category;
}
