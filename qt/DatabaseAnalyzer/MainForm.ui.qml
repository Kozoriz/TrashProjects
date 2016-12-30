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
            anchors.bottomMargin: 440
            anchors.fill: parent
        }

        Grid {
            id: database_grid
            anchors.topMargin: 46
            anchors.fill: parent
        }
    }
}
