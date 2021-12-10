// SPDX-FileCopyrightText: 2021 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import Fluid.Controls 1.0 as FluidControls
import QtGSettings 1.0
import Liri.Settings 1.0
import Liri.Settings.Updates 1.0

ModulePage {
    id: page

    actions: [
        FluidControls.Action {
            icon.source: FluidControls.Utils.iconUrl("action/system_update_alt")
            text: qsTr("Check for updates")
            toolTip: qsTr("Check if there are new updates available")
            visible: page.state === "updated"
            onTriggered: {
                let transaction = softwareUpdate.checkForUpdates();
                if (transaction) {
                    transaction.progressChanged.connect(function(text, percentage) {
                        checkForUpdates.updateProgress(text, percentage);
                    });

                    transaction.start();
                }
            }
        }
    ]

    states: [
        State {
            name: "disabled"
            when: !softwareUpdate.enabled
        },
        State {
            name: "updated"
            when: softwareUpdate.model.count == 0 && !softwareUpdate.currentTransaction
            PropertyChanges { target: stackLayout; currentIndex: 1 }
        },
        State {
            name: "checkForUpdates"
            when: softwareUpdate.currentTransaction && softwareUpdate.currentTransaction.type == Transaction.CheckForUpdatesType
            PropertyChanges { target: stackLayout; currentIndex: 2 }
        },
        State {
            name: "updatesAvailable"
            when: softwareUpdate.model.count > 0 && !softwareUpdate.currentTransaction
            PropertyChanges { target: stackLayout; currentIndex: 3 }
        },
        State {
            name: "updateInProgress"
            when: softwareUpdate.currentTransaction && softwareUpdate.currentTransaction.type == Transaction.UpgradeType
            PropertyChanges { target: stackLayout; currentIndex: 4 }
        }
    ]

    SoftwareUpdate {
        id: softwareUpdate
    }

    GSettings {
        id: systemSettings

        schema.id: "io.liri.system"
        schema.path: "/io/liri/system/"
    }

    Component {
        id: detailsPage

        DetailsPage {}
    }

    StackLayout {
        id: stackLayout

        anchors.fill: parent

        FluidControls.Placeholder {
            icon.source: FluidControls.Utils.iconUrl("action/update_disabled")
            text: qsTr("Updates are disable on this device")
        }

        FluidControls.Placeholder {
            icon.source: FluidControls.Utils.iconUrl("device/system_security_update_good")
            text: qsTr("Your device is up to date!")
        }

        TransactionProgress {
            id: checkForUpdates

            Layout.fillWidth: true
            Layout.fillHeight: true

            defaultText: qsTr("Checking for updates...")
        }

        UpdatesAvailable {
            id: updatesAvailable

            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        TransactionProgress {
            id: updateInProgress

            Layout.fillWidth: true
            Layout.fillHeight: true

            defaultText: qsTr("Updating...");
        }
    }
}
