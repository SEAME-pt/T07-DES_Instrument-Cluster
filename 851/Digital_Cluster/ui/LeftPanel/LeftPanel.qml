import QtQuick 2.15
import QtQuick.Controls 2.15
import "./Leftcolumn"
import "./Rightcolumn"
import "./Centercolumn"

// Left panel
Rectangle {
    id: leftPanel
    width: isCenterPanelOn ? (parent.height * 0.618 - 10) : parent.width // não deve ser necessário
    // color: "#272727"
    color: "transparent"
    radius: 8

    property bool isCenterPanelOn : centerPanel.visible

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
            spacing: 10 // Espaçamento entre as colunas
            anchors.fill: parent

            // Coluna da esquerda
            LeftColumn {
                id: leftColumn
                visible: true
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
