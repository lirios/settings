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
#include <QSet>
#include <QFileInfo>
#include <QPixmap>

#include <VDesktopFile>

#include "backgroundsmodel.h"

/*
 * BackgroundsModelItem
 */

static bool sizeGreaterThan(const QSize &s1, const QSize &s2)
{
    return (s1.width() > s2.width()) || (s1.height() > s2.height());
}

BackgroundsModelItem::BackgroundsModelItem(const QDir &imagesDir,
                                           const QString &entry,
                                           const QString &previewFileName) :
    m_previewFileName(previewFileName)
{
    // Calculate aspect ratio
    QSize screenSize = qApp->desktop()->size();
    qreal ratio = qreal(screenSize.width() / screenSize.height());

    // Load metadata and preview image scaled down (preserving screen aspect ratio)
    m_entry = new VDesktopFile(entry);
    m_pixmap.load(previewFileName);
    m_pixmap = m_pixmap.scaled(QSize(128 * ratio, 128));

    // Find best size
    BackgroundSizeFinder *finder = new BackgroundSizeFinder(screenSize, imagesDir, this);
    connect(finder, SIGNAL(sizeFound(QSize)),
            this, SLOT(slotSizeFound(QSize)));
    finder->start(QThread::HighestPriority);
}

BackgroundsModelItem::~BackgroundsModelItem()
{
    delete m_entry;
}

QString BackgroundsModelItem::previewFileName() const
{
    return m_previewFileName;
}

QVariant BackgroundsModelItem::data(int role) const
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

void BackgroundsModelItem::slotSizeFound(const QSize &size)
{
    m_size = size;
    emit dataChanged(this);
}

/*
 * BackgroundSizeFinder
 */

BackgroundSizeFinder::BackgroundSizeFinder(const QSize &resolution,
                                           const QDir &imagesDir, QObject *parent) :
    QThread(parent),
    m_resolution(resolution),
    m_imagesDir(imagesDir)
{
}

BackgroundSizeFinder::~BackgroundSizeFinder()
{
    wait();
}

void BackgroundSizeFinder::run()
{
    // Check for available resolutions
    QList<QSize> resolutions;
    QSet<QString> suffixes;
    suffixes << "png" << "jpg" << "jpeg" << "svg" << "svgz";
    QFileInfoList fileInfoList = m_imagesDir.entryInfoList(QDir::Files | QDir::Readable);
    foreach(QFileInfo fileInfo, fileInfoList) {
        if (suffixes.contains(fileInfo.suffix().toLower())) {
            // Save resolutions
            QImage image(fileInfo.absoluteFilePath());
            resolutions.append(image.size());
        }
    }

    // Sort resolutions list
    qSort(resolutions.begin(), resolutions.end(), sizeGreaterThan);

    // Find the resolution closest to the screen size
    QSize closestSize;
    for (int i = 0; i < resolutions.size(); i++) {
        QSize currentSize = resolutions.at(i);
        QSize size1(qAbs(currentSize.width() - m_resolution.width()),
                    qAbs(currentSize.height() - m_resolution.height()));
        QSize size2(qAbs(closestSize.width() - m_resolution.width()),
                    qAbs(closestSize.height() - m_resolution.height()));
        if ((size1.width() < size2.width()) && (size1.height() < size2.height()))
            closestSize = currentSize;
    }

    if (closestSize.isValid())
        emit sizeFound(closestSize);
}

/*
 * BackgroundFinder
 */

BackgroundFinder::BackgroundFinder(const QString &path, QObject *parent) :
    QThread(parent),
    m_path(path)
{
}

BackgroundFinder::~BackgroundFinder()
{
    wait();
}

void BackgroundFinder::run()
{
    QSet<QString> suffixes;
    suffixes << "png" << "jpg" << "jpeg" << "svg" << "svgz";

    QDir dir(m_path);
    dir.setFilter(QDir::Dirs | QDir::Readable | QDir::NoDotAndDotDot);

    // Loop over all directories under the current category
    QFileInfoList list = dir.entryInfoList();
    foreach(QFileInfo fileInfo, list) {
        // Look for the metadata and preview files
        QDir subDir(fileInfo.absoluteFilePath());
        if (subDir.exists("metadata.desktop")) {
            subDir = QDir(fileInfo.absoluteFilePath() + "/contents");
            subDir.setNameFilters(QStringList() << "screenshot.*");
            subDir.setFilter(QDir::Files | QDir::Readable);
            foreach(QString previewFileName, subDir.entryList()) {
                // Can continue only if preview has the right extension and wallpaper set has images
                QFileInfo preview(subDir.absoluteFilePath(previewFileName));
                if (preview.exists() && suffixes.contains(preview.suffix().toLower())) {
                    QDir imagesDir(subDir.absolutePath() + "/images");
                    imagesDir.setFilter(QDir::Files | QDir::Readable | QDir::NoDotAndDotDot);

                    if (imagesDir.entryList().size() > 0)
                        emit backgroundFound(imagesDir.absolutePath(),
                                             fileInfo.absoluteFilePath() + "/metadata.desktop",
                                             preview.absoluteFilePath());
                }
            }
        }
    }
}

/*
 * BackgroundsModel
 */

BackgroundsModel::BackgroundsModel(QObject *parent) :
    QAbstractListModel(parent)
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
    BackgroundFinder *finder = new BackgroundFinder(path, this);
    connect(finder, SIGNAL(backgroundFound(QString, QString, QString)),
            this, SLOT(slotBackgroundFound(QString, QString, QString)));
    finder->start(QThread::HighPriority);
}

QVariant BackgroundsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    BackgroundsModelItem *item = getItem(index);
    if (!item)
        return QVariant();
    return item->data(role);
}

int BackgroundsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_list.size();
}

BackgroundsModelItem *BackgroundsModel::getItem(const QModelIndex &index) const
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
    BackgroundsModelItem *item = new BackgroundsModelItem(QDir(wallpaperDir), desktopEntry, previewImage);
    connect(item, SIGNAL(dataChanged(BackgroundsModelItem *)),
            this, SLOT(slotItemDataChanged(BackgroundsModelItem *)));
    m_list.append(item);
    endInsertRows();
}

void BackgroundsModel::slotItemDataChanged(BackgroundsModelItem *item)
{
    for (int i = 0; i < m_list.size(); i++) {
        BackgroundsModelItem *curItem = m_list.at(i);

        if (curItem->previewFileName() == item->previewFileName()) {
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
