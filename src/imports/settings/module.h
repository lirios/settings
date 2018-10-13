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

#ifndef LIRI_SETTINGS_MODULE_H
#define LIRI_SETTINGS_MODULE_H

#include <QObject>
#include <QUrl>

class ModulePrivate;

class Module : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool valid READ isValid CONSTANT)
    Q_PROPERTY(Category category READ category CONSTANT)
    Q_PROPERTY(QString categoryName READ categoryName CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(QString comment READ comment CONSTANT)
    Q_PROPERTY(QString iconName READ iconName CONSTANT)
    Q_PROPERTY(QStringList keywords READ keywords CONSTANT)
    Q_PROPERTY(QUrl mainScriptUrl READ mainScriptUrl CONSTANT)
    Q_DECLARE_PRIVATE(Module)
public:
    enum Category {
        NoCategory,
        PersonalCategory,
        HardwareCategory,
        SystemCategory
    };
    Q_ENUM(Category)

    explicit Module(const QString &fileName, QObject *parent = nullptr);
    ~Module();

    bool isValid() const;

    Category category() const;
    QString categoryName() const;
    QString name() const;
    QString title() const;
    QString comment() const;
    QString iconName() const;
    QStringList keywords() const;
    QUrl mainScriptUrl() const;

private:
    ModulePrivate *const d_ptr;
};

#endif // LIRI_SETTINGS_MODULE_H
