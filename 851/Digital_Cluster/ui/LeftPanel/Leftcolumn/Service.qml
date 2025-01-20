import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: servicePage
    width: parent.width
    height: parent.height
    color: "#3A3A3A" // Fundo escuro
    radius: 8

    Column {
        anchors.centerIn: parent
        spacing: 20 // Espaçamento entre os elementos

        // Título da Página
        Text {
            text: "Próximo Serviço"
            color: "white"
            font.pixelSize: 24
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // Informação do Próximo Serviço
        Text {
            text: "Data: 12/03/2025\nLocal: Oficina XYZ\nDescrição: Revisão geral"
            color: "white"
            font.pixelSize: 15
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
            wrapMode: servicePage.WordWrap
        }

        // Botão para Voltar
        // Button {
        //     text: "back"
        //     anchors.horizontalCenter: parent.horizontalCenter
        //     onClicked: {
        //         // console.log("Voltando para o menu anterior")
        //         servicePage.visible = false // Oculta esta página
        //         leftLoader.source = "Info.qml"
        //         // Coloque aqui o código para exibir a página anterior
        //     }
        // }

        Button {
            text: "Voltar"
            anchors.horizontalCenter: parent.horizontalCenter
            background: Rectangle {
                implicitWidth: 50
                implicitHeight: 20
                color: "#1F1F1F" // Cor de fundo
                radius: 10 // Arredondamento opcional
            }
            contentItem: Text {
                text: "back"
                color: "white"
                font.pixelSize: 12
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            onClicked: {
                // console.log("Voltando para o menu anterior")
                servicePage.visible = false // Oculta esta página
                leftLoader.source = "Info.qml"
                // Coloque aqui o código para exibir a página anterior
            }
        }

    }
}

