import QtQuick 2.15

Rectangle {
    id: rightColumn
    width: parent.width * 0.2 - 10// 20% da largura do container retirar os 10 da margin , ver coluna da esquerda

    anchors {
        top: parent.top
        bottom: parent.bottom
    }

    color: "#3A3A3A"
    radius: 8

    Column {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        ListView {
            id: optionsList
            width: parent.width
            height: parent.height - 50 // Ajuste a altura para caber os itens
            model: ListModel {
                ListElement { name: "navigation" }
                ListElement { name: "modes" }
                ListElement { name: "media" }
                ListElement { name: "settings" }
            }

            delegate: Item {
                width: parent.width
                height: 50



                Text {
                    anchors.centerIn: parent
                    text: model.name
                    // color: "white"
                    color: index === optionsList.currentIndex ? "#4A90E2" : "white"
                    font.pixelSize: 16
                }

                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    onClicked: {
                        optionsList.currentIndex = index; // Atualiza o índice do item selecionado
                    }
                }
            }
        }


    }
}
