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

#ifndef LIRI_SETTINGS_MODULESMODEL_H
#define LIRI_SETTINGS_MODULESMODEL_H

#include <QAbstractListModel>
#include <QQmlParserStatus>

QT_FORWARD_DECLARE_CLASS(QThread)

class Module;
class ModulesModel;

class ModulesModelTask : public QObject
{
    Q_OBJECT
public:
    explicit ModulesModelTask(QObject *parent = nullptr);

Q_SIGNALS:
    void populated();

public Q_SLOTS:
    void populate();

private:
    QVector<Module *> m_plugins;
    QMap<QString, Module *> m_pluginsMap;

    friend class ModulesModel;
};

class ModulesModel : public QAbstractListModel, public QQmlParserStatus
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

    explicit ModulesModel(QObject *parent = nullptr);
    ~ModulesModel();

    QHash<int, QByteArray> roleNames() const override;

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    Q_INVOKABLE Module *getByName(const QString &name) const;

    void classBegin() override {}
    void componentComplete() override;

Q_SIGNALS:
    void vendorChanged();

private:
    ModulesModelTask *m_task;
    QThread *m_thread;
};

#endif // LIRI_SETTINGS_MODULESMODEL_H
