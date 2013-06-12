
import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import QtQuick.Layouts 1.0
import Hawaii.SystemPreferences 0.1

ApplicationWindow {
    id: root
    title: qsTr("System Preferences")
    width: 640
    height: 640
    minimumWidth: 640
    minimumHeight: 640

    toolBar: ToolBar {
        id: mainToolBar
        width: parent.width

        RowLayout {
            anchors.fill: parent
            spacing: 10

            ToolButton {
                action: actionBack
            }

            Item {
                Layout.fillWidth: true
            }

            TextField {
                id: searchEntry
                placeholderText: qsTr("Keywords")

                Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            }
        }
    }

    SystemPalette {
        id: palette
    }

    Action {
        id: actionBack
        iconName: "view-grid-symbolic"
        onTriggered: pageStack.pop()
    }

    StackView {
        id: pageStack
        anchors.fill: parent

        initialItem: Item {
            width: parent.width
            height: parent.height

            ColumnLayout {
                anchors.fill: parent

                Repeater {
                    model: CategoriesModel {}

                    GroupBox {
                        title: label

                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        ScrollView {
                            anchors.fill: parent

                            GridView {
                                id: gridView
                                model: PrefletsProxyModel {}
                                cellWidth: width / 6
                                delegate: GridDelegate {
                                    width: gridView.cellWidth

                                    MouseArea {
                                        anchors.fill: parent
                                        onClicked: pageStack.push({item: model.item, properties: {stackView: pageStack}})
                                    }
                                }

                                Component.onCompleted: gridView.model.setFilterFixedString(name)
                            }
                        }
                    }
                }
            }
        }
    }
}
