// SPDX-FileCopyrightText: 2021 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls
import Fluid.Controls as FluidControls
import Liri.Settings
import Liri.Settings.Updates

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
