import QtQuick 2.15

Column {
    id: signs
    anchors.horizontalCenter: parent.horizontalCenter
    spacing: 5
    signal gearSelected(string gearSelected)

    property string gear: "P"
    property bool showIcons: false // Indica se os ícones devem estar "ligados"

    // Propriedades para controlar os estados individuais das luzes
    property bool minlightOn: false
    property bool headLightsOn: false
    property bool lightOn: false
    property bool lightAutoOn: false

    // Sinal para receber comandos externos
    signal toggleLight(string lightName, bool state)

    Repeater {
        model: ["minlight", "HeadLights", "light", "lightauto"]

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
               // opacity: showIcons ? 1 : 0.3
                opacity: showIcons ? 1 : (modelData === "minlight" ? (minlightOn ? 1 : 0.3) :
                                            modelData === "HeadLights" ? (headLightsOn ? 1 : 0.3) :
                                            modelData === "light" ? (lightOn ? 1 : 0.3) :
                                            modelData === "lightauto" ? (lightAutoOn ? 1 : 0.3) : 0.3)
                }


            }
        }


    Timer {
            id: iconTimer
            interval: 2000 // Tempo em milissegundos (2 segundos "ligados")
            repeat: false // Executa apenas uma vez
            onTriggered: showIcons = false // Desliga os ícones
        }

    // Funções para controlar os estados individuais das luzes
    function setMinlight(on) {
        minlightOn = on;
    }

    function setHeadLights(on) {
        headLightsOn = on;
    }

    function setLight(on) {
        lightOn = on;
    }

    function setLightAuto(on) {
        lightAutoOn = on;
    }


    onGearSelected: function (selectedGear) {
        console.log("gear in signs", selectedGear);
        if (selectedGear === "D" && gear === "P") {
            gear = selectedGear
            showIcons = true // Liga os ícones
            iconTimer.restart() // Reinicia o timer para desligar
        } else {
            gear = selectedGear;
        }
    }

    onToggleLight: function(lightName, state) {
           if (lightName === "HeadLights") {
               headLightsOn = state;
           }
       }

}



