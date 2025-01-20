import QtQuick 2.15
import QtQuick.Controls 2.15
import "./Leftcolumn"
import "./Rightcolumn"
import "./Centercolumn"

// Left panel
Rectangle {
    id: leftPanel
    width: isCenterPanelOn ? (parent.width * 0.2 - 10) : parent.width // não deve ser necessário
    // color: "#2F2F2F"
    color: "#1F1F1F"
    radius: 8

    property bool isCenterPanelOn : centerPanel.visible
    // anchors.fill: parent

    anchors {
        bottom: parent.bottom
        left: parent.left
        top: parent.top
        right: isCenterPanelOn ? centerPanel.left : parent.right // verificar se funciona, é necessário para aplicar a margin à dir
        margins: 10
    }

    signal gearSelected(string gear)


    Row {
            id: rowLayout
            anchors.fill: parent
            spacing: 10 // Espaçamento entre as colunas

            // Coluna da esquerda
            LeftColumn {
                id: leftColumn
                visible: true
                // visible: isCenterPanelOn ? false : true
            }


            CenterColumn {
                id: centerColumn
                // visible: true
                visible: isCenterPanelOn ? false : true
            }


            RightColumn {
                id: rightColumn
                // visible: true
                visible: isCenterPanelOn ? false : true
            }

    }


}
