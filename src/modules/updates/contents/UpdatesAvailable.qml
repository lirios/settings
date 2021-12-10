// SPDX-FileCopyrightText: 2021 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick 2.15
import QtQuick.Controls 2.15
import Fluid.Controls 1.0 as FluidControls
import Liri.Settings 1.0
import Liri.Settings.Updates 1.0

ModuleContainer {
    title: qsTr("Updates available")
    width: page.width

    FluidControls.ListItem {
        icon.source: FluidControls.Utils.iconUrl("device/system_security_update_warning")
        text: qsTr("Version %1").arg(softwareUpdate.version)
        subText: softwareUpdate.information
        rightItem: Button {
            flat: true
            text: qsTr("Update")

            onClicked: {
                let transaction = softwareUpdate.upgrade();
                if (transaction)
                    transaction.start();
            }
        }
        onClicked: {
            window.pageStack.push(detailsPage);
        }
    }
}
