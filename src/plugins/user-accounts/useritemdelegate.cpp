/****************************************************************************
 * This file is part of System Preferences.
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

#include <QApplication>
#include <QPainter>
#include <QTextDocument>

#include <QtAccountsService/UsersModel>

#include "useritemdelegate.h"

QT_USE_NAMESPACE_ACCOUNTSSERVICE

const int kMargin = 6;
const QSize kMaxSize = QSize(48, 48);

UserItemDelegate::UserItemDelegate(QObject *parent)
    : QAbstractItemDelegate(parent)
{
}

void UserItemDelegate::paint(QPainter *painter,
                             const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    const QAbstractItemModel *model = index.model();
    const QString realName = model->data(index, UsersModel::RealNameRole).toString();
    const QString userName = model->data(index, UsersModel::UserNameRole).toString();
    const QPixmap pixmap = qvariant_cast<QPixmap>(model->data(index, Qt::DecorationRole));

    // Highlight selected item
    QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &option, painter);

    // Draw user icon
    QPixmap userIcon;
    if (pixmap.isNull())
        userIcon = QIcon::fromTheme("avatar-default").pixmap(kMaxSize);
    else
        userIcon = pixmap.scaled(kMaxSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter->drawPixmap(option.rect.left() + kMargin, option.rect.top() + kMargin,
                        kMaxSize.width(), kMaxSize.height(), userIcon);

    // Use a QTextDocument to layout the text
    QTextDocument document;
    QString html = QString::fromUtf8("<strong>%1</strong><br />%2").arg(realName).arg(userName);

    // Set the text color according to the item state
    QColor color;
    if (option.state & QStyle::State_Selected)
        color = QApplication::palette().brush(QPalette::HighlightedText).color();
    else
        color = QApplication::palette().brush(QPalette::Text).color();
    html = QString::fromUtf8("<div style=\"color: %1\" align=\"center\">%2</div>")
            .arg(color.name()).arg(html);

    // Set contents and word-wrap
    document.setHtml(html);
    //document.setTextWidth(kMaxSize.width());

    // Calculate positioning
    int x = option.rect.left() + kMaxSize.width() + kMargin * 2;
    int y = option.rect.top() + kMargin;

    // Draw text
    painter->save();
    painter->translate(x, y);
    document.drawContents(painter, QRect(QPoint(0, 0), option.rect.size() -
                                         QSize(kMaxSize.width() + kMargin, 0)));
    painter->restore();
}

QSize UserItemDelegate::sizeHint(const QStyleOptionViewItem &option,
                                 const QModelIndex &index) const
{
    Q_UNUSED(option)

    const QString realName = index.model()->data(index, UsersModel::RealNameRole).toString();
    const QString userName = index.model()->data(index, UsersModel::UserNameRole).toString();

    // Generate a sample complete entry to calculate size
    QTextDocument document;
    QString html = QString::fromUtf8("<strong>%1</strong><br />%2").arg(realName).arg(userName);
    document.setHtml(html);

    return QSize(kMaxSize.width() + kMargin * 3 + document.textWidth(),
                 kMaxSize.height() + kMargin * 2);
}

#include "moc_useritemdelegate.cpp"
