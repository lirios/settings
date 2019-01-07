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
#include <QFileInfo>

#include <LiriXdg/DesktopFile>

#include "module.h"

/*
 * ModulePrivate
 */

class ModulePrivate
{
public:
    ModulePrivate(const QString &fileName)
        : entry(new Liri::DesktopFile())
    {
        if (!entry->load(fileName))
            qWarning("Failed to load \"%s\"", qPrintable(fileName));
    }

    ~ModulePrivate() { delete entry; }

    Liri::DesktopFile *entry;
    Module::Category category;
    QString categoryName;
};

/*
 * Module
 */

Module::Module(const QString &fileName, QObject *parent)
    : QObject(parent)
    , d_ptr(new ModulePrivate(fileName))
{
    Q_D(Module);
    d->categoryName = d->entry->value(QStringLiteral("X-Liri-Settings-Category"),
                                      QStringLiteral("personal"))
                              .toString();
    if (d->categoryName == QStringLiteral("personal"))
        d->category = Module::PersonalCategory;
    else if (d->categoryName == QStringLiteral("hardware"))
        d->category = Module::HardwareCategory;
    else if (d->categoryName == QStringLiteral("system"))
        d->category = Module::SystemCategory;
    else
        d->category = Module::NoCategory;
}

Module::~Module() { delete d_ptr; }

bool Module::isValid() const
{
    Q_D(const Module);
    return d->entry != nullptr;
}

Module::Category Module::category() const
{
    Q_D(const Module);
    return d->category;
}

QString Module::categoryName() const
{
    Q_D(const Module);
    return d->categoryName;
}

QString Module::name() const
{
    Q_D(const Module);
    return d->entry->value(QStringLiteral("X-Liri-Settings-InternalName")).toString();
}

QString Module::title() const
{
    Q_D(const Module);
    return d->entry->localizedValue(QStringLiteral("Name")).toString();
}

QString Module::comment() const
{
    Q_D(const Module);
    return d->entry->localizedValue(QStringLiteral("Comment")).toString();
}

QString Module::iconName() const
{
    Q_D(const Module);

    QString iconName = d->entry->value(QStringLiteral("X-Liri-Settings-SymbolicIcon")).toString();

    if (iconName.isEmpty()) {
        iconName = d->entry->localizedValue(QStringLiteral("Icon")).toString();
    }

    return iconName;
}

QStringList Module::keywords() const
{
    Q_D(const Module);
    return d->entry->localizedValue(QStringLiteral("Keywords")).toStringList();
}

QUrl Module::mainScriptUrl() const
{
    Q_D(const Module);

    QFileInfo info(d->entry->fileName());
    return QUrl::fromLocalFile(info.absoluteDir().absoluteFilePath(QStringLiteral("main.qml")));
}
