import QtQuick
import QtQuick.Controls 2.15
import Qt5Compat.GraphicalEffects

Rectangle {
    id: bottomBar
    width: parent.width
    height: parent.height * 0.25
    color: "#2F2F2F"
    opacity: 0.7
    radius: 8
    anchors.bottom: parent.bottom
    layer.enabled: true

    // GaussianBlur {
    //             anchors.fill: parent
    //             source: parent
    //             radius: 4 // Intensidade do desfoque
    //             samples: 16
    //             deviation: 3
    //         }




    Row {
        anchors.fill: parent
        anchors.leftMargin: 30
        spacing: 20

        Column {
            spacing: 3
            anchors.verticalCenter: parent.verticalCenter
            // Current Speed
            Text {
                id: speed
                // text: "42"
                text: systemHandler.speed
                color: "white"
                font.pixelSize: 42
                anchors.horizontalCenter: parent.horizontalCenter
                opacity: 1
            }


            Text {
                id: speedUnits
                text: "km/h"
                color: "white"
                font.pixelSize: 16
                anchors.horizontalCenter: parent.horizontalCenter
                opacity: 1
            }

        }

        // Column {
        //     spacing: 5
        //     Text {
        //         text: "12:27 pm"
        //         font.pixelSize: 20
        //         color: "white"
        //     }
        //     Text {
        //         text: "9 min"
        //         font.pixelSize: 14
        //         color: "lightgray"
        //     }
        // }

        // Rectangle {
        //     id: musicContainer
        //     width: 120
        //     height: parent.height - 20
        //     color: "transparent"
        //     border.color: "white"
        //     radius: 10
        //     Row {
        //         spacing: 10
        //         anchors.centerIn: parent

        //         Image {
        //             source: "album_cover.jpg" // Altere para a imagem desejada
        //             width: 60
        //             height: 60
        //             fillMode: Image.PreserveAspectFit
        //         }

        //         Column {
        //             spacing: 5
        //             Text {
        //                 text: "Simple Man"
        //                 font.pixelSize: 16
        //                 color: "white"
        //             }
        //             Text {
        //                 text: "Lynyrd Skynyrd"
        //                 font.pixelSize: 12
        //                 color: "lightgray"
        //             }
        //         }
        //     }
        // }
    }
}
