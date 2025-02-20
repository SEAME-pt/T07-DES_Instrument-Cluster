import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: centerColumn

    // width: parent.width * 0.5 // 60% da largura do container
    width: parent.width - leftColumn.width - rightColumn.width - 20
    color: "#3A3A3A"
    // color: "blue"
    radius: 8
    anchors {
        top: parent.top
        bottom: parent.bottom
    }

    signal gearSelected(string gear)

    property bool turnLightLeftOn: systemHandler.turnLightLeft === "true" ? true : false
    property bool turnLightRightOn: systemHandler.turnLightRight === "true" ? true : false
    property bool emergency: systemHandler.emergencyLights === "true" ? true : false


    Text {
        id: speed

        anchors {
            top: parent.top
            topMargin: 10
            horizontalCenter: parent.horizontalCenter
        }

        //text: "42"
        // text: systemHandler.speed
        text: Math.round(Number(systemHandler.speed)) // Exibe a velocidade atual sem casas decimais
        color: "white"
        font.pixelSize: 80

    }


    Route {
        id: route
    }


    Text {
        id: speedUnits
        anchors {
            top: speed.bottom
            horizontalCenter: parent.horizontalCenter
        }
        text: "m/h"
        color: "white"
        font.pixelSize: 16
    }


    Left {
        id: left
    }


    Right {
        id: right
    }


    Image {
           id: carRender
           source: "../../assets/car.png"
           anchors.bottom: parent.bottom
           anchors.bottomMargin: 10
           anchors.horizontalCenter: parent.horizontalCenter
           width: parent.width * .25
           fillMode: Image.PreserveAspectFit
    }


    Rectangle {
        id: turnSignalLeft
        width: 50
        height: 50
        color: "transparent"
        clip: true
        visible: false
        anchors {
            top: parent.top
            left: parent.left
            leftMargin: parent.width * 0.17
            topMargin: parent.height * 0.1
        }

        Image {
            source: "../../assets/turn_light_02.png"
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
            smooth: true // Para renderização de alta qualidade
            // para testes
            // MouseArea {
            //     anchors.fill: parent
            //     onClicked: {
            //         console.log("clicked for teste")
            //         blinkTimerLeft.running = false;
            //     }
            // }
        }

        Timer {
                id: blinkTimerLeft
                interval: 500 // 500ms, ou seja, pisca duas vezes por segundo
                running: turnLightLeftOn || emergency // Inicia automaticamente
                repeat: true // Continua piscando
                onTriggered: {
                    turnSignalLeft.visible = !turnSignalLeft.visible;
                }
                onRunningChanged: {
                   if (!running) {
                       turnSignalLeft.visible = false;
                   }
                }
        }
    }


    Rectangle {
        id: turnSignalRight
        width: 50
        height: 50
        color: "transparent"
        rotation: 180
        visible: false
        clip: true
        anchors {
            top: parent.top
            right: parent.right
            rightMargin: parent.width * 0.17
            topMargin: parent.height * 0.1
        }

        Image {
            source: "../../assets/turn_light_02.png"
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
            smooth: true // Para renderização de alta qualidade
        }

        Timer {
                id: blinkTimerRight
                interval: 500 // 500ms, ou seja, pisca duas vezes por segundo
                running: turnLightRightOn || emergency // Inicia automaticamente
                repeat: true // Continua piscando
                onTriggered: {
                    turnSignalRight.visible = !turnSignalRight.visible
                }
                onRunningChanged: {
                   if (!running) {
                       turnSignalLeft.visible = false;
                   }
                }
        }
    }

    // teste de verificação - c++ -> QML
    // Component.onCompleted: {
    //     console.log("systemHandler está acessível no QML centerColumn:", systemHandler.speed);
    // }

    onGearSelected: function (gear) {
        left.gearSelected(gear);
        right.gearSelected(gear);
    }

}
