import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {

    id: centerColumn

    anchors {
        top: parent.top
        bottom: parent.bottom
    }

    width: parent.width * 0.5 // 60% da largura do container
    color: "#2F2F2F"
    radius: 8

    Text {
        id: speed

        anchors {
            top: parent.top
            topMargin: 20
            horizontalCenter: parent.horizontalCenter
        }

        text: "42"
        color: "white"
        font.pixelSize: 80

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

    Route {
        id: route
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

    Component.onCompleted: {
        console.log("systemHandler está acessível no QML centerColumn:", systemHandler.speedSensor);
    }

}
