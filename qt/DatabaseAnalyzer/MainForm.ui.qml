import QtQuick 2.7
import QtQuick.Controls 2.0

Rectangle {
    property alias mouseArea: mouseArea


    MouseArea {
        id: mouseArea
        anchors.rightMargin: 0
        anchors.fill: parent

        ToolBar {
            id: tool_bar
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.bottomMargin: 440
            anchors.fill: parent

            ToolButton {
                id: import_button
                x: 0
                y: 0
                width: 81
                height: 40
                text: qsTr("Import")
            }

            ToolButton {
                id: save_changes_button
                x: 87
                y: 0
                text: qsTr("Save changes")
                enabled: false
            }

            ToolButton {
                id: filters_button
                x: 189
                y: 0
                width: 57
                height: 40
                text: qsTr("Filters")
                enabled: false
            }

            ToolButton {
                id: generate_report_button
                x: 252
                y: 0
                text: qsTr("Generate report")
                enabled: false
                checkable: false
            }
        }

        Grid {
            id: database_grid
            anchors.rightMargin: -8
            anchors.bottomMargin: 0
            anchors.leftMargin: 8
            anchors.topMargin: 46
            anchors.fill: parent
        }
    }
}
