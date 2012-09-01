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

#ifndef BACKGROUNDSMODEL_H
#define BACKGROUNDSMODEL_H

#include <QAbstractListModel>
#include <QDir>

class VDesktopFile;

class ModelItem : public QObject
{
    Q_OBJECT
    Q_ENUMS(ModelType)
public:
    enum ModelType {
        WallpaperType,
        ColorType
    };

    explicit ModelItem(ModelType type);

    ModelType type() const;

    virtual QVariant data(int role) const;

private:
    class Private;
    Private *d;
};

class WallpaperItem : public ModelItem
{
    Q_OBJECT
public:
    explicit WallpaperItem(const QDir &imagesDir, const QString &entry,
                           const QString &previewFileName);
    ~WallpaperItem();

    QString previewFileName() const;

    QVariant data(int role) const;

signals:
    void dataChanged(WallpaperItem *);

private:
    VDesktopFile *m_entry;
    QString m_previewFileName;
    QPixmap m_pixmap;
    QSize m_size;

private slots:
    void slotSizeFound(const QSize &size);
};

class ColorItem : public ModelItem
{
    Q_OBJECT
public:
    explicit ColorItem(const QColor &color1, const QColor &color2,
                       bool vertical = true);
    ColorItem(const QColor &color);
    ~ColorItem();

    QVariant data(int role) const;

private:
    class Private;
    Private *d;
};

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
    QList<ModelItem *> m_list;

    ModelItem *getItem(const QModelIndex &index) const;

private slots:
    void slotBackgroundFound(const QString &wallpaperDir,
                             const QString &desktopEntry, const QString &previewImage);
    void slotItemDataChanged(ModelItem *item);
};

#endif // BACKGROUNDSMODEL_H
