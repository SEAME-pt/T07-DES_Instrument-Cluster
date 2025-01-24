import QtQuick 2.15

Column {
    id: signsRight
    anchors.horizontalCenter: parent.horizontalCenter
    spacing: 5
    signal gearSelected(string gearSelected)

    property string gear: "P"
    property bool showIcons: false // Indica se os ícones devem estar "ligados"

    Repeater {
        model: ["hold", "brake", "Tractioncontrol", "Tirepressure"]

        delegate: Rectangle {
            width: 40
            height: 40
            color: "transparent"
            clip: true


            Image {
                source: "../../assets/" + modelData + ".png"
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                smooth: true // Para renderização de alta qualidade
                opacity: showIcons ? 1 : 0.3
            }


        }
    }


    Timer {
            id: iconTimer
            interval: 2000 // Tempo em milissegundos (2 segundos "ligados")
            repeat: false // Executa apenas uma vez
            onTriggered: showIcons = false // Desliga os ícones
        }

    onGearSelected: function (selectedGear) {
        console.log("gear in signsright", selectedGear);
        if (selectedGear === "D" && gear === "P") {
            gear = selectedGear
            showIcons = true // Liga os ícones
            iconTimer.restart() // Reinicia o timer para desligar
        } else {
            gear = selectedGear;
        }
    }

}



