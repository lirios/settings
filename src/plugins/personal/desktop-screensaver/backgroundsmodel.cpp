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

#include <QApplication>
#include <QDesktopWidget>
#include <QFileInfo>
#include <QPixmap>
#include <QPainter>

#include <VDesktopFile>

#include "backgroundsmodel.h"
#include "wallpaperfinder.h"

/*
 * ModelItem
 */

class ModelItem::Private
{
public:
    Private() {}

    ModelItem::ModelType type;
};

ModelItem::ModelItem(ModelType type)
    : d(new Private())
{
    d->type = type;
}

ModelItem::ModelType ModelItem::type() const
{
    return d->type;
}

QVariant ModelItem::data(int role) const
{
	Q_UNUSED(role);
    return QVariant();
}

/*
 * WallpaperItem
 */

WallpaperItem::WallpaperItem(const QDir &imagesDir,
                             const QString &entry,
                             const QString &previewFileName)
    : ModelItem(ModelItem::WallpaperType)
    , m_previewFileName(previewFileName)
{
    // Calculate aspect ratio
    QSize screenSize = qApp->desktop()->size();
    qreal ratio = qreal(screenSize.width() / screenSize.height());

    // Load metadata and preview image scaled down (preserving screen aspect ratio)
    m_entry = new VDesktopFile(entry);
    m_pixmap.load(previewFileName);
    m_pixmap = m_pixmap.scaled(QSize(128 * ratio, 128));

    // Find best size
    WallpaperSizeFinder *finder = new WallpaperSizeFinder(screenSize, imagesDir, this);
    connect(finder, SIGNAL(sizeFound(QSize)),
            this, SLOT(slotSizeFound(QSize)));
    finder->start(QThread::HighestPriority);
}

WallpaperItem::~WallpaperItem()
{
    delete m_entry;
}

QString WallpaperItem::previewFileName() const
{
    return m_previewFileName;
}

QVariant WallpaperItem::data(int role) const
{
    switch (role) {
        case Qt::DisplayRole:
            return m_entry->name();
        case Qt::DecorationRole:
            return QVariant::fromValue(m_pixmap);
        case Qt::ToolTipRole:
            return m_entry->comment();
        case BackgroundsModel::AuthorRole:
            return m_entry->value("X-Hawaii-PluginInfo-Author");
        case BackgroundsModel::ResolutionRole:
            if (m_size.isValid())
                return QString("%1x%2").arg(m_size.width()).arg(m_size.height());
            return QString();
    }

    return QVariant();
}

void WallpaperItem::slotSizeFound(const QSize &size)
{
    m_size = size;
    emit dataChanged(this);
}

/*
 * ColorItem
 */

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
    : ModelItem(ModelItem::ColorType)
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
    : ModelItem(ModelItem::ColorType)
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

/*
 * BackgroundsModel
 */

BackgroundsModel::BackgroundsModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

BackgroundsModel::~BackgroundsModel()
{
    qDeleteAll(m_list);
}

void BackgroundsModel::setPath(const QString &path)
{
    // Don't enter the same path we are into
    if (path == m_path)
        return;

    // Clear the old list of images
    if (m_list.size() > 0) {
        beginRemoveRows(QModelIndex(), 0, m_list.size() - 1);
        qDeleteAll(m_list);
        endRemoveRows();
    }

    // Store it so that we won't enter the same path again
    m_path = path;

    // Find backgrounds in another thread
    WallpaperFinder *finder = new WallpaperFinder(path, this);
    connect(finder, SIGNAL(backgroundFound(QString, QString, QString)),
            this, SLOT(slotBackgroundFound(QString, QString, QString)));
    finder->start(QThread::HighPriority);
}

QVariant BackgroundsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    ModelItem *item = getItem(index);
    if (!item)
        return QVariant();
    return item->data(role);
}

int BackgroundsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_list.size();
}

ModelItem *BackgroundsModel::getItem(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return m_list.at(index.row());
}

void BackgroundsModel::slotBackgroundFound(const QString &wallpaperDir,
                                           const QString &desktopEntry,
                                           const QString &previewImage)
{
    beginInsertRows(QModelIndex(), m_list.size(), m_list.size());
    WallpaperItem *item = new WallpaperItem(QDir(wallpaperDir), desktopEntry, previewImage);
    connect(item, SIGNAL(dataChanged(ModelItem *)),
            this, SLOT(slotItemDataChanged(ModelItem *)));
    m_list.append(item);
    endInsertRows();
}

void BackgroundsModel::slotItemDataChanged(ModelItem *item)
{
    for (int i = 0; i < m_list.size(); i++) {
	if (item->type() != ModelItem::WallpaperType)
		continue;

	WallpaperItem *reqItem = qobject_cast<WallpaperItem *>(item);
        WallpaperItem *curItem = qobject_cast<WallpaperItem *>(m_list.at(i));

	if (!reqItem || !curItem)
		continue;

        if (curItem->previewFileName() == reqItem->previewFileName()) {
            QModelIndex idx = index(i, 0);
            emit dataChanged(idx, idx);
            emit layoutAboutToBeChanged();
            changePersistentIndex(idx, idx);
            emit layoutChanged();
            break;
        }
    }
}

#include "moc_backgroundsmodel.cpp"
