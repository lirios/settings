// SPDX-FileCopyrightText: 2021 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick 2.15
import QtQuick.Controls 2.15
import Fluid.Controls 1.0 as FluidControls
import Liri.Settings 1.0

ModulePage {
    title: qsTr("System Updates | Details")

    ScrollView {
        anchors.fill: parent
        clip: true

        ListView {
            model: softwareUpdate.model
            // FIXME: Section delegate is transparent su the label positioning doesn't work
            //section.labelPositioning: ViewSection.CurrentLabelAtStart
            section.property: "category"
            section.delegate: FluidControls.Subheader {
                text: section
            }
            delegate: FluidControls.ListItem {
                text: model.name
                subText: model.description
            }
        }
    }
}
