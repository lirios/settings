// SPDX-FileCopyrightText: 2021 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import Fluid.Controls 1.0 as FluidControls
import Liri.Settings.Updates 1.0

Item {
    property string defaultText: ""

    ColumnLayout {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right

        FluidControls.DialogLabel {
            id: label

            Layout.alignment: Qt.AlignHCenter
        }

        ProgressBar {
            id: progressBar

            Layout.fillWidth: true
            Layout.leftMargin: 8
            Layout.rightMargin: 8

            from: 0
            to: 100
            indeterminate: true
        }

        Button {
            Layout.alignment: Qt.AlignHCenter

            text: qsTr("Cancel")
            onClicked: {
                softwareUpdate.currentTransaction.cancel();
            }
        }
    }

    onVisibleChanged: {
        reset();
    }

    function reset() {
        label.text = defaultText;
        progressBar.indeterminate = true;
    }

    function updateProgress(text, percentage) {
        label.text = text;
        progressBar.indeterminate = false;
        progressBar.value = percentage;
    }
}
