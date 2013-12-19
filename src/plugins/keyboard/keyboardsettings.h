/****************************************************************************
 * This file is part of Hawaii Shell.
 *
 * Copyright (C) 2013 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

#ifndef KEYBOARDSETTINGS_H
#define KEYBOARDSETTINGS_H

#include <QtCore/QObject>

class QConfiguration;

class KeyboardSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool keyboardRepeatEnabled READ keyboardRepeatEnabled WRITE setKeyboardRepeatEnabled NOTIFY keyboardRepeatEnabledChanged)
    Q_PROPERTY(int keyboardInputInterval READ keyboardInputInterval WRITE setKeyboardInputInterval NOTIFY keyboardInputIntervalChanged)
    Q_PROPERTY(int keyboardAutoRepeatRate READ keyboardAutoRepeatRate WRITE setKeyboardAutoRepeatRate NOTIFY keyboardAutoRepeatRateChanged)
    Q_PROPERTY(bool cursorFlashEnabled READ cursorFlashEnabled WRITE setCursorFlashEnabled NOTIFY cursorFlashEnabledChanged)
    Q_PROPERTY(int cursorFlashTime READ cursorFlashTime WRITE setCursorFlashTime NOTIFY cursorFlashTimeChanged)
public:
    explicit KeyboardSettings(QObject *parent = 0);
    ~KeyboardSettings();

    bool keyboardRepeatEnabled() const;
    void setKeyboardRepeatEnabled(bool value);

    int keyboardInputInterval() const;
    void setKeyboardInputInterval(int value);

    int keyboardAutoRepeatRate() const;
    void setKeyboardAutoRepeatRate(int value);

    bool cursorFlashEnabled() const;
    void setCursorFlashEnabled(bool value);

    int cursorFlashTime() const;
    void setCursorFlashTime(int value);

Q_SIGNALS:
    void keyboardRepeatEnabledChanged(bool value);
    void keyboardInputIntervalChanged(int value);
    void keyboardAutoRepeatRateChanged(int value);
    void cursorFlashEnabledChanged(bool value);
    void cursorFlashTimeChanged(int value);

private:
    QConfiguration *m_configuration;
    bool m_keyboardRepeatEnabled;
    int m_keyboardInputInterval;
    int m_keyboardAutoRepeatRate;
    bool m_cursorFlash;
    int m_cursorFlashTime;
};

#endif // KEYBOARDSETTINGS_H
