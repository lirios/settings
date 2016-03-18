/****************************************************************************
 * This file is part of Hawaii.
 *
 * Copyright (C) 2013-2016 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:GPL2+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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

import QtQuick 2.1
import QtQuick.Controls 1.0
import Qt.labs.controls 1.0
import Fluid.Ui 1.0 as FluidUi
import org.hawaiios.systempreferences 0.1

GroupBox {
    property string categoryName
    property string categoryIconName
    readonly property int itemSize: 96
    property alias model: repeater.model

    frame: Item {}
    label: Row {
        spacing: FluidUi.Units.smallSpacing

        FluidUi.Icon {
            iconName: categoryIconName + "-symbolic"
            width: FluidUi.Units.iconSizes.small
            height: width
        }

        Label {
            text: title
        }
    }

    Grid {
        anchors.fill: parent

        Repeater {
            id: repeater
            delegate: GridDelegate {
                width: itemSize
                height: itemSize

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if (!model.mainScript)
                            return;

                        var component = Qt.createComponent(model.mainScript);
                        if (component.status !== Component.Ready) {
                            console.error(component.errorString());
                            return;
                        }

                        var item = component.createObject(null);

                        if (typeof(item.minimumWidth) != "undefined")
                            root.minimumWidth = item.minimumWidth;
                        if (typeof(item.minimumHeight) != "undefined")
                            root.minimumHeight = item.minimumHeight;

                        prefletTitle.text = model.title;
                        pageStack.push({item: item});
                    }
                }
            }
        }
    }
}
