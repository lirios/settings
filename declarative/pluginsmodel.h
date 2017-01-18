/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2016 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#ifndef PLUGINSMODEL_H
#define PLUGINSMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtQml/QQmlParserStatus>

QT_FORWARD_DECLARE_CLASS(QThread)

class Plugin;
class PluginsModel;

class PluginsModelTask : public QObject
{
    Q_OBJECT
public:
    PluginsModelTask(QObject *parent = nullptr);

Q_SIGNALS:
    void populated();

public Q_SLOTS:
    void populate();

private:
    QVector<Plugin *> m_plugins;
    QMap<QString, Plugin *> m_pluginsMap;

    friend class PluginsModel;
};

class PluginsModel : public QAbstractListModel, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        CategoryRole,
        TitleRole,
        CommentRole,
        IconNameRole,
        KeywordsRole,
        MainScriptRole
    };

    PluginsModel(QObject *parent = nullptr);
    ~PluginsModel();

    QHash<int, QByteArray> roleNames() const;

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    Q_INVOKABLE Plugin *getByName(const QString &name) const;

    void classBegin() Q_DECL_OVERRIDE {}
    void componentComplete() Q_DECL_OVERRIDE;

Q_SIGNALS:
    void vendorChanged();

private:
    PluginsModelTask *m_task;
    QThread *m_thread;
};

#endif // PLUGINSMODEL_H
