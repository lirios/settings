/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (c) 2011-2012 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:GPL$
 *
 * System Preferences is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * System Preferences is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with System Preferences.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include <QColor>
#include <QVariant>
#include <QPixmap>
#include <QPainter>
#include <QLinearGradient>

#include "coloritem.h"

class ColorItem::Private
{
public:
    Private() {}

    QColor color1;
    QColor color2;
    bool solid : 1;
    bool vertical : 1;
    QString name;
};

ColorItem::ColorItem(const QColor &color1, const QColor &color2,
                     bool vertical)
    : BackgroundItem(BackgroundItem::ColorType)
    , d(new Private())
{
    d->color1 = color1;
    d->color2 = color2;
    d->solid = false;
    d->vertical = vertical;
    if (vertical)
        d->name = tr("Vertical Gradient");
    else
        d->name = tr("Horizontal Gradient");
}

ColorItem::ColorItem(const QColor &color)
    : BackgroundItem(BackgroundItem::ColorType)
    , d(new Private())
{
    d->color1 = color;
    d->solid = true;
    d->name = tr("Solid Color");
}

QVariant ColorItem::data(int role) const
{
    switch (role) {
        case Qt::DisplayRole:
            return d->name;
        case Qt::DecorationRole: {
            QPixmap pixmap(64, 64);
            QPainter painter(&pixmap);

            if (d->solid)
                painter.fillRect(pixmap.rect(), d->color1);
            else if (d->vertical) {
                QLinearGradient gradient(pixmap.rect().topLeft(), pixmap.rect().bottomLeft());
                gradient.setColorAt(0, d->color1);
                gradient.setColorAt(1, d->color2);
                painter.fillRect(pixmap.rect(), gradient);
            } else {
                QLinearGradient gradient(pixmap.rect().topLeft(), pixmap.rect().topRight());
                gradient.setColorAt(0, d->color1);
                gradient.setColorAt(1, d->color2);
                painter.fillRect(pixmap.rect(), gradient);
            }

            return pixmap;
        }
        default:
            break;
    };

    return QVariant();
}

#include "moc_coloritem.cpp"
