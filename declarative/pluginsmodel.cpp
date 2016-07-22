/****************************************************************************
 * This file is part of Hawaii.
 *
 * Copyright (C) 2016 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#include <QtCore/QDir>
#include <QtCore/QStandardPaths>
#include <QtCore/QThread>
#include "plugin.h"
#include "pluginsmodel.h"

PluginsModelTask::PluginsModelTask(QObject *parent)
    : QObject(parent)
{
}

void PluginsModelTask::populate()
{
    qDeleteAll(m_plugins);

    QStringList list = QStandardPaths::locateAll(QStandardPaths::GenericDataLocation,
                                                 QLatin1String("hawaii/systemsettings/modules"),
                                                 QStandardPaths::LocateDirectory);
    Q_FOREACH (const QString &location, list) {
        QDir dir(location);
        QStringList modules = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
        Q_FOREACH (const QString &module, modules) {
            QDir moduleDir(dir.absoluteFilePath(module));
            QStringList files = moduleDir.entryList(QDir::Files);
            Q_FOREACH (const QString &fileName, files) {
                if (fileName != QLatin1String("metadata.desktop"))
                    continue;

                Plugin *plugin = new Plugin(moduleDir.absoluteFilePath(fileName));
                m_plugins.append(plugin);
                m_pluginsMap[module] = plugin;
            }
        }
    }

    std::sort(m_plugins.begin(), m_plugins.end(), [](const Plugin *a, const Plugin *b) {
        return a->categoryName() < b->categoryName();
    });

    Q_EMIT populated();
}


PluginsModel::PluginsModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_task(new PluginsModelTask())
    , m_thread(new QThread())
{
    m_task->moveToThread(m_thread);
    m_thread->start();
}

PluginsModel::~PluginsModel()
{
    m_task->deleteLater();

    m_thread->quit();
    m_thread->wait();
}

QHash<int, QByteArray> PluginsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(NameRole, QByteArrayLiteral("name"));
    roles.insert(CategoryRole, QByteArrayLiteral("category"));
    roles.insert(TitleRole, QByteArrayLiteral("title"));
    roles.insert(CommentRole, QByteArrayLiteral("comment"));
    roles.insert(IconNameRole, QByteArrayLiteral("iconName"));
    roles.insert(KeywordsRole, QByteArrayLiteral("keywords"));
    roles.insert(MainScriptRole, QByteArrayLiteral("mainScriptUrl"));
    return roles;
}

int PluginsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_task->m_plugins.count();
}

QVariant PluginsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_task->m_plugins.count())
        return QVariant();

    Plugin *plugin = m_task->m_plugins.at(index.row());

    switch (role) {
    case Qt::DisplayRole:
        return plugin->title();
    case NameRole:
        return plugin->name();
    case CategoryRole:
        switch (plugin->category()) {
        case Plugin::PersonalCategory:
            return tr("Personal");
        case Plugin::HardwareCategory:
            return tr("Hardware");
        case Plugin::SystemCategory:
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

Plugin *PluginsModel::getByName(const QString &name) const
{
    return m_task->m_pluginsMap[name];
}

void PluginsModel::componentComplete()
{
    beginResetModel();
    m_task->populate();
    endResetModel();
}

#include "moc_pluginsmodel.cpp"
