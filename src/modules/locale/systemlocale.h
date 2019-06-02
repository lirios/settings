/****************************************************************************
 * This file is part of Liri.
 *
 * Copyright (C) 2019 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#ifndef SYSTEMLOCALE_H
#define SYSTEMLOCALE_H

#include <QDBusInterface>
#include <QObject>

class SystemLocale : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString language READ language NOTIFY languageChanged)
    Q_PROPERTY(QString country READ country NOTIFY countryChanged)
    Q_PROPERTY(QString code READ code WRITE setCode NOTIFY codeChanged)
public:
    explicit SystemLocale(QObject *parent = nullptr);

    QString language() const;

    QString country() const;

    QString code() const;
    void setCode(const QString &code);

Q_SIGNALS:
    void languageChanged();
    void countryChanged();
    void codeChanged();

private:
    QDBusInterface *m_interface = nullptr;
    QMap<QString, QString> m_localeCache;
    QString m_language;
    QString m_country;

    void updateLanguage();
    void updateCountry();
};

#endif // SYSTEMLOCALE_H
