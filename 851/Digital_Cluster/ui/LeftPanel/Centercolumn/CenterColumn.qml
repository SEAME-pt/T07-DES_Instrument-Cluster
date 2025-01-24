import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {

    id: centerColumn

    signal gearSelected(string gear)

    // property bool turnLightLeftOn: false
    // property bool turnLightRightOn: false
    // property bool emergency: true

    property bool turnLightLeftOn: systemHandler.turnLightLeft === "true" ? true : false
    property bool turnLightRightOn: systemHandler.turnLightRight === "true" ? true : false
    property bool emergency: systemHandler.emergencyLights === "true" ? true : false

    anchors {
        top: parent.top
        bottom: parent.bottom
    }

    // width: parent.width * 0.5 // 60% da largura do container
    width: parent.width - leftColumn.width - rightColumn.width - 20
    color: "#3A3A3A"
    // color: "blue"
    radius: 8

    //property int speedy: 0         // Velocidade inicial
    //property string targetSpeed: "50"   // Target
    // property string targetSpeed: systemHandler.speed



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

    // Animação de velocidade
    // NumberAnimation on speedy {
    //     from: speedy
    //     to: Number(targetSpeed)  // Converte targetSpeed (string) para número
    //     duration: Math.abs(Number(targetSpeed) - speedy) * 2 // Ajuste para 60fps 16.67
    //     easing.type: Easing.InOutQuad
    //     running: targetSpeed >= "0"  // Animação começa quando targetSpeed for maior que zero
    //     onRunningChanged: {
    //         if (running) {
    //             speedy = Number(targetSpeed);  // Inicia a animação alterando speedy para targetSpeed
    //         }
    //     }
    // }

    // // Quando o targetSpeed for maior que zero, inicia a animação automaticamente
    // onTargetSpeedChanged: {
    //     if (Number(targetSpeed) > 0) {
    //         // Garante que a animação comece suavemente se o targetSpeed mudar
    //         speedy = Number(targetSpeed); // Atualiza a velocidade
    //     }
    // }


    Route {
        id: route
    }

    Text {
        id: speedUnits

        anchors {
            top: speed.bottom
            horizontalCenter: parent.horizontalCenter
        }

        text: "km/h"
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
        }

        Timer {
                id: blinkTimerLeft
                interval: 500 // 500ms, ou seja, pisca duas vezes por segundo
                running: turnLightLeftOn || emergency // Inicia automaticamente
                repeat: true // Continua piscando
                onTriggered: {
                    turnSignalLeft.visible = !turnSignalLeft.visible
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
            }

    }

    Component.onCompleted: {
        console.log("systemHandler está acessível no QML centerColumn:", systemHandler.speed);
    }

    onGearSelected: function (gear) {
        left.gearSelected(gear);
        right.gearSelected(gear);
    }

}
