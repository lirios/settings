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

#include "keyboardlayout.h"

KeyboardLayout::KeyboardLayout(const QString &name, const QString &description, QObject *parent)
    : QObject(parent)
    , m_name(name)
    , m_description(description)
{
    appendVariant(QStringLiteral(""), tr("None"));
}

KeyboardLayout::~KeyboardLayout()
{
    qDeleteAll(m_variants);
}

QString KeyboardLayout::name() const
{
    return m_name;
}

QString KeyboardLayout::description() const
{
    return m_description;
}

QQmlListProperty<KeyboardLayoutVariant> KeyboardLayout::variants()
{
    auto countFunc = [](QQmlListProperty<KeyboardLayoutVariant> *prop) {
        return static_cast<KeyboardLayout *>(prop->object)->m_variants.count();
    };
    auto atFunc = [](QQmlListProperty<KeyboardLayoutVariant> *prop, int index) {
        return static_cast<KeyboardLayout *>(prop->object)->m_variants.at(index);
    };
    return QQmlListProperty<KeyboardLayoutVariant>(this, 0, countFunc, atFunc);
}

void KeyboardLayout::appendVariant(const QString &name, const QString &description)
{
    m_variants.append(new KeyboardLayoutVariant(name, description));
    Q_EMIT variantsChanged();
}

const KeyboardLayoutVariant *KeyboardLayout::findVariant(const QString &name) const
{
    if (name.isEmpty())
        return Q_NULLPTR;

    Q_FOREACH (const KeyboardLayoutVariant *variant, m_variants) {
        if (variant->name() == name)
            return variant;
    }

    return Q_NULLPTR;
}

#include "moc_keyboardlayout.cpp"
