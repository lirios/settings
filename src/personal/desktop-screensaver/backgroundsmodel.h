/****************************************************************************
 * This file is part of Preferences.
 *
 * Copyright (c) 2011-2012 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Preferences is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Preferences is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Preferences.  If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#ifndef BACKGROUNDSMODEL_H
#define BACKGROUNDSMODEL_H

#include <QAbstractListModel>
#include <QThread>
#include <QDir>

class VDesktopFile;

class BackgroundsModelItem;

class BackgroundsModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE setPath)
    Q_ENUMS(AdditionalRoles)
public:
    enum AdditionalRoles {
        AuthorRole = Qt::UserRole + 1,
        ResolutionRole = Qt::UserRole + 2
    };

    explicit BackgroundsModel(QObject *parent = 0);
    ~BackgroundsModel();

    QString path() const {
        return m_path;
    }
    void setPath(const QString &path);

    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual int rowCount(const QModelIndex &parent) const;

private:
    QString m_path;
    QList<BackgroundsModelItem *> m_list;

    BackgroundsModelItem *getItem(const QModelIndex &index) const;

private slots:
    void slotBackgroundFound(const QString &wallpaperDir,
                             const QString &desktopEntry, const QString &previewImage);
    void slotItemDataChanged(BackgroundsModelItem *item);
};

class BackgroundsModelItem : public QObject
{
    Q_OBJECT
public:
    explicit BackgroundsModelItem(const QDir &imagesDir, const QString &entry,
                                  const QString &previewFileName);
    ~BackgroundsModelItem();

    QString previewFileName() const;

    QVariant data(int role) const;

signals:
    void dataChanged(BackgroundsModelItem *);

private:
    VDesktopFile *m_entry;
    QString m_previewFileName;
    QPixmap m_pixmap;
    QSize m_size;

private slots:
    void slotSizeFound(const QSize &size);
};

class BackgroundSizeFinder : public QThread
{
    Q_OBJECT
public:
    explicit BackgroundSizeFinder(const QSize &resolution,
                                  const QDir &imagesDir, QObject *parent = 0);
    ~BackgroundSizeFinder();

signals:
    void sizeFound(const QSize &size);

protected:
    void run();

private:
    QSize m_resolution;
    QDir m_imagesDir;
};

class BackgroundFinder : public QThread
{
    Q_OBJECT
public:
    explicit BackgroundFinder(const QString &path, QObject *parent = 0);
    ~BackgroundFinder();

    QString path() const {
        return m_path;
    }

signals:
    void backgroundFound(const QString &wallpaperDir,
                         const QString &desktopEntry, const QString &previewImage);

protected:
    void run();

private:
    QString m_path;
};

#endif // BACKGROUNDSMODEL_H
