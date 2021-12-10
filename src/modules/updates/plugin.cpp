// SPDX-FileCopyrightText: 2021 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <QQmlExtensionPlugin>
#include <QQmlComponent>

#include "rpmdiffmodel.h"
#include "softwareupdate.h"
#include "transaction.h"

class UpdatesPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface/1.0")
public:
    void registerTypes(const char *uri) override
    {
        Q_ASSERT(strcmp(uri, "Liri.Settings.Updates") == 0);

        // @uri Liri.Settings.Updates
        qmlRegisterType<RpmDiffModel>(uri, 1, 0, "RpmDiffModel");
        qmlRegisterType<SoftwareUpdate>(uri, 1, 0, "SoftwareUpdate");
        qmlRegisterUncreatableType<Transaction>(uri, 1, 0, "Transaction",
                                                QStringLiteral("Cannot register type Transaction"));
    }
};

#include "plugin.moc"
