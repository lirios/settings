/****************************************************************************
 * This file is part of Hawaii.
 *
 * Copyright (C) 2015 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
 *
 * $BEGIN_LICENSE:LGPL2.1+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#ifndef KEYBOARDDATA_H
#define KEYBOARDDATA_H

#include <QtCore/QObject>
#include <QtQml/QQmlListProperty>

class KeyboardModel;
class KeyboardLayout;

class KeyboardData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<KeyboardModel> models READ models NOTIFY modelsChanged)
    Q_PROPERTY(QQmlListProperty<KeyboardLayout> layouts READ layouts NOTIFY layoutsChanged)
public:
    KeyboardData(QObject *parent = 0);
    ~KeyboardData();

    QQmlListProperty<KeyboardModel> models();
    QQmlListProperty<KeyboardLayout> layouts();

    Q_INVOKABLE QString layoutDescription(const QString &name) const;
    Q_INVOKABLE QString variantDescription(const QString &layout, const QString &name) const;

Q_SIGNALS:
    void modelsChanged();
    void layoutsChanged();

private:
    QList<KeyboardModel *> m_models;
    QList<KeyboardLayout *> m_layouts;
    QMap<QString, QString> m_changeLayout;

    void loadData();
};

#endif // KEYBOARDDATA_H
