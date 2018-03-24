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

#include <QtCore/QFile>
#include <QDebug>

#include "keyboarddata.h"
#include "keyboardmodel.h"
#include "keyboardlayout.h"

enum ListSection{
    NoSection,
    ModelSection,
    LayoutSection,
    VariantSection,
    OptionSection
};

KeyboardData::KeyboardData(QObject *parent)
    : QObject(parent)
{
    loadData();
}

KeyboardData::~KeyboardData()
{
    qDeleteAll(m_models);
    qDeleteAll(m_layouts);
}

QQmlListProperty<KeyboardModel> KeyboardData::models()
{
    auto countFunc = [](QQmlListProperty<KeyboardModel> *prop) {
        return static_cast<KeyboardData *>(prop->object)->m_models.count();
    };
    auto atFunc = [](QQmlListProperty<KeyboardModel> *prop, int index) {
        return static_cast<KeyboardData *>(prop->object)->m_models.at(index);
    };
    return QQmlListProperty<KeyboardModel>(this, 0, countFunc, atFunc);
}

QQmlListProperty<KeyboardLayout> KeyboardData::layouts()
{
    auto countFunc = [](QQmlListProperty<KeyboardLayout> *prop) {
        return static_cast<KeyboardData *>(prop->object)->m_layouts.count();
    };
    auto atFunc = [](QQmlListProperty<KeyboardLayout> *prop, int index) {
        return static_cast<KeyboardData *>(prop->object)->m_layouts.at(index);
    };
    return QQmlListProperty<KeyboardLayout>(this, 0, countFunc, atFunc);
}

QString KeyboardData::layoutDescription(const QString &name) const
{
    Q_FOREACH (KeyboardLayout *l, m_layouts) {
        if (l->name() == name)
            return l->description();
    }

    return QString();
}

QString KeyboardData::variantDescription(const QString &layout, const QString &name) const
{
    KeyboardLayout *foundLayout = nullptr;
    Q_FOREACH (KeyboardLayout *l, m_layouts) {
        if (l->name() == layout) {
            foundLayout = l;
            break;
        }
    }

    if (!foundLayout)
        return QString();

    Q_FOREACH (const KeyboardLayoutVariant *v, foundLayout->m_variants) {
        if (v->name() == name)
            return v->description();
    }

    return QString();
}

/*
 * Code derivded from LXQt keyboard configuration tool.
 * No copyright indication from upstream.
 * Under the terms of GNU LGPL v2.1+
 */
void KeyboardData::loadData()
{
    QFile file(QStringLiteral("/usr/share/X11/xkb/rules/base.lst"));
    if (!file.open(QIODevice::ReadOnly))
        return;

    ListSection section = NoSection;
    while (!file.atEnd()) {
        QByteArray line = file.readLine().trimmed();

        if (section == NoSection) {
            if (line.startsWith("! model"))
                section = ModelSection;
            else if (line.startsWith("! layout"))
                section = LayoutSection;
            else if (line.startsWith("! variant"))
                section = VariantSection;
            else if (line.startsWith("! option"))
                section = OptionSection;
        } else {
            if (line.isEmpty()) {
                section = NoSection;
                continue;
            }

            int sep = line.indexOf(' ');
            QString name = QString::fromLatin1(line, sep);
            while (line[sep] == ' ') // skip spaces
                ++sep;
            QString description = QString::fromUtf8(line.constData() + sep);

            switch (section) {
            case ModelSection:
                m_models.append(new KeyboardModel(name, description));
                Q_EMIT modelsChanged();
                break;
            case LayoutSection:
                m_layouts.append(new KeyboardLayout(name, description));
                Q_EMIT layoutsChanged();
                break;
            case VariantSection:
                // The descriptions of variants are prefixed by their language IDs
                sep = description.indexOf(": ");
                if (sep >= 0) {
                    QString lang = description.left(sep);
                    Q_FOREACH (KeyboardLayout *layout, m_layouts) {
                        if (layout->name() == lang)
                            layout->appendVariant(name, description.mid(sep + 2));
                    }
                }
                break;
            case OptionSection:
                // Key used to switch to another layout
                if (line.startsWith("grp:"))
                    m_changeLayout[name] = description;
                break;
            default:
                break;
            }
        }
    }

    file.close();
}

#include "moc_keyboarddata.cpp"
