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

#include <QtConfiguration/QConfiguration>

#include "keyboardsettings.h"

KeyboardSettings::KeyboardSettings(QObject *parent)
    : QObject(parent)
    , m_keyboardRepeatEnabled(true)
    , m_keyboardInputInterval(30)
    , m_keyboardAutoRepeatRate(500)
    , m_cursorFlash(true)
    , m_cursorFlashTime(400)
{
    // Configuration
    m_configuration = new QConfiguration(this, QStringLiteral("peripherals/keyboard"));
}

KeyboardSettings::~KeyboardSettings()
{
    delete m_configuration;
}

bool KeyboardSettings::keyboardRepeatEnabled() const
{
    return m_keyboardRepeatEnabled;
}

void KeyboardSettings::setKeyboardRepeatEnabled(bool value)
{
    if (m_keyboardRepeatEnabled != value) {
        m_keyboardRepeatEnabled = value;
        Q_EMIT keyboardRepeatEnabledChanged(value);
    }
}

int KeyboardSettings::keyboardInputInterval() const
{
    return m_keyboardInputInterval;
}

void KeyboardSettings::setKeyboardInputInterval(int value)
{
    if (m_keyboardInputInterval != value) {
        m_keyboardInputInterval = value;
        Q_EMIT keyboardInputIntervalChanged(value);
    }
}

int KeyboardSettings::keyboardAutoRepeatRate() const
{
    return m_keyboardAutoRepeatRate;
}

void KeyboardSettings::setKeyboardAutoRepeatRate(int value)
{
    if (m_keyboardAutoRepeatRate != value) {
        m_keyboardAutoRepeatRate = value;
        Q_EMIT keyboardAutoRepeatRateChanged(value);
    }
}

bool KeyboardSettings::cursorFlashEnabled() const
{
    return m_cursorFlash;
}

void KeyboardSettings::setCursorFlashEnabled(bool value)
{
    if (m_cursorFlash != value) {
        m_cursorFlash = value;
        Q_EMIT cursorFlashEnabledChanged(value);
    }
}

int KeyboardSettings::cursorFlashTime() const
{
    return m_cursorFlashTime;
}

void KeyboardSettings::setCursorFlashTime(int value)
{
    if (m_cursorFlashTime != value) {
        m_cursorFlashTime = value;
        Q_EMIT cursorFlashTimeChanged(value);
    }
}

#include "moc_keyboardsettings.cpp"
