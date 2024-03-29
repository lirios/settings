// SPDX-FileCopyrightText: 2021 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls
import Fluid.Controls as FluidControls
import Liri.Settings
import Liri.Settings.Updates

ModuleContainer {
    property Transaction transaction: null

    title: qsTr("System Updates")
    width: page.width

    Connections {
        target: transaction

        function onStatusChanged(status) {
            switch (status) {
            case Transaction.CompletedStatus:
            case Transaction.CompletedWithErrorStatus:
                transaction = null;
                break;
            default:
                break;
            }
        }

        function onProgressChanged(text, percentage) {
            progressItem.text = text;
            progressBar.value = percentage;
        }
    }

    FluidControls.ListItem {
        id: progressItem

        icon.source: FluidControls.Utils.iconUrl("device/system_security_update_warning")
        secondaryItem: ProgressBar {
            id: progressBar

            anchors.verticalCenter: parent.verticalCenter
            from: 0
            to: 100
            width: parent.width
        }
    }
}
