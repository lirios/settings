/****************************************************************************
 * This file is part of Liri.
 *
 * Copyright (C) 2019 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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

import QtQml 2.3
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import Fluid.Controls 1.0 as FluidControls
import Liri.Settings.Region 1.0

Dialog {
    id: formatsDialog

    property string selectedCode: ""
    property var selectedLocale: null

    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    width: parent.width * 0.9
    height: parent.height * 0.9

    title: qsTr("Formats")

    modal: true

    standardButtons: Dialog.Ok | Dialog.Cancel

    onOpened: {
        formatsDialog.selectedCode = localeSettings.region;
        formatsDialog.selectedLocale = Qt.locale(formatsDialog.selectedCode);
        searchField.forceActiveFocus();
    }

    onAccepted: {
        localeSettings.region = formatsDialog.selectedCode;
    }

    ButtonGroup {
        id: buttonGroup
    }

    Row {
        anchors.fill: parent
        spacing: FluidControls.Units.smallSpacing * 2

        ColumnLayout {
            width: parent.width * 0.4
            height: parent.height

            TextField {
                id: searchField
                placeholderText: qsTr("Search a language")
                focus: true

                Layout.fillWidth: true
            }

            ScrollView {
                clip: true

                Layout.fillWidth: true
                Layout.fillHeight: true

                ListView {
                    id: localeListView

                    model: LocaleFilterModel {
                        filter: searchField.text
                    }
                    currentIndex: -1
                    delegate: RadioDelegate {
                        width: localeListView.width
                        text: qsTr("%1 (%2)").arg(model.language).arg(model.country)
                        checked: model.code === formatsDialog.selectedCode
                        onClicked: {
                            formatsDialog.selectedCode = model.code;
                            formatsDialog.selectedLocale = Qt.locale(formatsDialog.selectedCode);
                        }

                        ButtonGroup.group: buttonGroup
                    }
                }
            }
        }

        GridLayout {
            columns: 2

            Label {
                text: qsTr("Dates")
                color: Material.secondaryTextColor

                Layout.alignment: Qt.AlignRight
            }

            Label {
                wrapMode: Text.WordWrap
                text: selectedLocale ? qsTr("%1 (%2)").arg(Qt.formatDate(new Date(), selectedLocale.dateFormat(Locale.ShortFormat))).arg(selectedLocale.dateFormat(1)) : ""

                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Times")
                color: Material.secondaryTextColor

                Layout.alignment: Qt.AlignRight
            }

            Label {
                wrapMode: Text.WordWrap
                text: selectedLocale ? qsTr("%1 (%2)").arg(Qt.formatTime(new Date(), selectedLocale.timeFormat(Locale.ShortFormat))).arg(selectedLocale.timeFormat(1)) : ""

                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Dates and Times")
                color: Material.secondaryTextColor

                Layout.alignment: Qt.AlignRight
            }

            Label {
                wrapMode: Text.WordWrap
                text: selectedLocale ? qsTr("%1 (%2)").arg(Qt.formatDateTime(new Date(), selectedLocale.dateTimeFormat(Locale.ShortFormat))).arg(selectedLocale.dateTimeFormat(1)) : ""

                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Numbers")
                color: Material.secondaryTextColor

                Layout.alignment: Qt.AlignRight
            }

            Label {
                wrapMode: Text.WordWrap
                text: selectedLocale ? Number(123456789.00).toLocaleString(selectedLocale) : ""

                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Measurement")
                color: Material.secondaryTextColor

                Layout.alignment: Qt.AlignRight
            }

            Label {
                wrapMode: Text.WordWrap
                text: {
                    if (!selectedLocale)
                        return "";

                    switch (selectedLocale.measurementSystem) {
                    case Locale.MetricSystem:
                        return qsTr("Metric");
                    case Locale.ImperialUKSystem:
                        return qsTr("Imperial (UK)");
                    case Locale.ImperialUSSystem:
                        return qsTr("Imperial (US)");
                    case Locale.ImperialSystem:
                        return qsTr("Imperial");
                    default:
                        break;
                    }

                    return qsTr("Unknown");
                }
            }

            Label {
                text: qsTr("Currency")
                color: Material.secondaryTextColor

                Layout.alignment: Qt.AlignRight
            }

            Label {
                wrapMode: Text.WordWrap
                text: selectedLocale ? selectedLocale.currencySymbol(Locale.CurrencyDisplayName) : ""

                Layout.fillWidth: true
            }
        }
    }
}
