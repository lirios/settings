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

#ifndef KEYBOARDLAYOUT_H
#define KEYBOARDLAYOUT_H

#include <QtCore/QObject>
#include <QtQml/QQmlListProperty>

#include "keyboardlayoutvariant.h"

class KeyboardData;

class KeyboardLayout : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString description READ description CONSTANT)
    Q_PROPERTY(QQmlListProperty<KeyboardLayoutVariant> variants READ variants NOTIFY variantsChanged)
public:
    KeyboardLayout(const QString &name, const QString &description, QObject *parent = 0);
    ~KeyboardLayout();

    QString name() const;
    QString description() const;

    QQmlListProperty<KeyboardLayoutVariant> variants();

    void appendVariant(const QString &name, const QString &description);

    const KeyboardLayoutVariant *findVariant(const QString &name) const;

Q_SIGNALS:
    void variantsChanged();

private:
    QString m_name;
    QString m_description;
    QList<KeyboardLayoutVariant *> m_variants;

    friend class KeyboardData;
};

#endif // KEYBOARDLAYOUT_H
