/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2018 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 * Copyright (C) 2016 Michael Spencer <sonrisesoftware@gmail.com>
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

import QtQuick 2.4
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import Fluid.Core 1.0 as FluidCore
import Fluid.Controls 1.0 as FluidControls
import Liri.Settings 1.0
import Vibe.PulseAudio 1.0 as PA

Page {
    header: ToolBar {
        height: bar.height

        TabBar {
            id:bar
            width: parent.width

            TabButton {
                text: qsTr("Volume")
            }

            TabButton {
                text: qsTr("Output")
            }

            TabButton {
                text: qsTr("Input")
            }

            TabButton {
                text: qsTr("Applications")
            }
        }
    }

    PA.SinkModel {
        id: sinkModel
    }

    PA.SourceModel {
        id: sourceModel
    }

    PA.CardModel {
        id: cardModel
    }

    StackLayout {
        anchors.fill: parent
        currentIndex: bar.currentIndex

        Page {
            anchors.fill: parent
            anchors.margins: FluidControls.Units.smallSpacing * 2

            Item {
                width: parent.width
                height: childrenRect.height

                ModuleContainer {
                    anchors.centerIn: parent

                    Repeater {
                        model: FluidCore.SortFilterProxyModel {
                            sourceModel: PA.StreamRestoreModel {}
                            filterRoleName: "Name"
                            filterValue: "sink-input-by-media-role:event"
                        }
                        delegate: StreamDelegate {}
                    }
                }
            }
        }

        Page {
            anchors.fill: parent
            anchors.margins: FluidControls.Units.smallSpacing * 2

            Item {
                width: parent.width
                height: childrenRect.height

                ModuleContainer {
                    anchors.centerIn: parent

                    Repeater {
                        model: FluidCore.SortFilterProxyModel {
                            sourceModel: sinkModel
                            sortExpression: {
                                var left = modelLeft.Properties["device.product.name"];
                                var right = modelRight.Properties["device.product.name"];
                                return left < right;
                            }
                        }
                        delegate: SinkDelegate {}
                    }
                }
            }
        }

        Page {
            anchors.fill: parent
            anchors.margins: FluidControls.Units.smallSpacing * 2

            Item {
                width: parent.width
                height: childrenRect.height

                ModuleContainer {
                    anchors.centerIn: parent

                    Repeater {
                        model: sourceModel
                        delegate: SinkDelegate {}
                    }
                }
            }
        }

        Page {
            anchors.fill: parent
            anchors.margins: FluidControls.Units.smallSpacing * 2

            Item {
                width: parent.width
                height: childrenRect.height

                ModuleContainer {
                    anchors.centerIn: parent

                    Repeater {
                        model: FluidCore.SortFilterProxyModel {
                            sourceModel: PA.SourceOutputModel {}
                            filterRoleName: "VirtualStream"
                            filterValue: false
                        }
                        delegate: StreamDelegate {}
                    }
                }
            }

            Item {
                width: parent.width
                height: childrenRect.height

                ModuleContainer {
                    anchors.centerIn: parent

                    Repeater {
                        model: FluidCore.SortFilterProxyModel {
                            sourceModel: PA.SinkInputModel {}
                            filterRoleName: "VirtualStream"
                            filterValue: false
                        }
                        delegate: StreamDelegate {}
                    }
                }
            }
        }
    }
}
