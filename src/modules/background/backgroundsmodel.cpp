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

#include <QtCore/QDirIterator>
#include <QtCore/QFileInfo>
#include <QtCore/QStandardPaths>

#include "backgroundsmodel.h"

using namespace Qt::Literals::StringLiterals;

/*
 * BackgroundsModelPrivate
 */

class BackgroundsModelPrivate
{
public:
    BackgroundsModelPrivate();

    QStringList paths;
    QStringList fileNames;
};

BackgroundsModelPrivate::BackgroundsModelPrivate()
{
}

/*
 * BackgroundsModel
 */

BackgroundsModel::BackgroundsModel(QObject *parent)
    : QAbstractListModel(parent)
    , d_ptr(new BackgroundsModelPrivate())
{
}

QHash<int, QByteArray> BackgroundsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[FileNameRole] = "fileName";
    return roles;
}

int BackgroundsModel::rowCount(const QModelIndex &parent) const
{
    Q_D(const BackgroundsModel);
    Q_UNUSED(parent);
    return d->fileNames.size();
}

QVariant BackgroundsModel::data(const QModelIndex &index, int role) const
{
    Q_D(const BackgroundsModel);

    if (!index.isValid())
        return QVariant();

    QString fileName = d->fileNames.at(index.row());
    if (fileName.isEmpty())
        return QVariant();

    QFileInfo info(fileName);
    if (!info.exists())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
    case NameRole:
        return info.baseName();
    case FileNameRole:
        return fileName;
    default:
        break;
    }

    return QVariant();
}

QString BackgroundsModel::get(int index) const
{
    Q_D(const BackgroundsModel);

    if (index < 0 || index > d->fileNames.size())
        return QString();
    return d->fileNames.at(index);
}

void BackgroundsModel::addStandardPaths()
{
    Q_D(BackgroundsModel);

    QStringList paths =
            QStandardPaths::locateAll(
                QStandardPaths::GenericDataLocation,
                "backgrounds"_L1, QStandardPaths::LocateDirectory);
    for (QString path: paths) {
        d->paths.append(path);
        addFolder(path);
    }
}

void BackgroundsModel::addUserPaths()
{
    Q_D(BackgroundsModel);

    QStringList paths =
            QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    for (QString path: paths) {
        d->paths.append(path);
        addFolder(path);
    }
}

void BackgroundsModel::addFolder(const QString &path)
{
    Q_D(BackgroundsModel);

    QStringList glob;
    glob << "*.png"_L1 << "*.jpg"_L1 << "*.jpeg"_L1 << "*.svg"_L1 << "*.svgz"_L1;

    QDir::Filters filters =
            QDir::NoDotAndDotDot | QDir::Readable | QDir::Files;
    QDirIterator::IteratorFlags flags =
            QDirIterator::Subdirectories | QDirIterator::FollowSymlinks;

    QDirIterator it(path, glob, filters, flags);
    while (it.hasNext()) {
        beginInsertRows(QModelIndex(), d->fileNames.size(), d->fileNames.size());
        d->fileNames.append(it.next());
        endInsertRows();
    }
}

void BackgroundsModel::clear()
{
    Q_D(BackgroundsModel);

    beginRemoveRows(QModelIndex(), 0, d->fileNames.size() - 1);
    d->fileNames.clear();
    endRemoveRows();
}

#include "moc_backgroundsmodel.cpp"
