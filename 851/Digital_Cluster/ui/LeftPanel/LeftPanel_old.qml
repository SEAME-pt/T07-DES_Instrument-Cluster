import QtQuick 2.15
import QtQuick.Controls 2.15

// Left panel
Rectangle {
    id: leftPanel
    width: isCenterPanelOn ? parent.width * 0.15 : parent.width
    color: "#2F2F2F"
    radius: 8

    property bool isCenterPanelOn : centerPanel.visible
    // anchors.fill: parent

    anchors {
        bottom: parent.bottom
        left: parent.left
        top: parent.top
        margins: 10
    }

    signal gearSelected(string gear)


    Column {
        // anchors.centerIn: parent
        anchors.fill: parent
        anchors.top: parent.top // Defina como base o topo do `parent`
        anchors.topMargin: 25 // Margem de 50 pixels a partir do topo

        spacing: 10

        // Speed Limit
        Rectangle {
            id: speedLimit

            anchors {
                horizontalCenter: parent.horizontalCenter
                // top: parent.top
                // topMargin: 30
            }
            width: 60
            height: 60
            color: "white"
            radius: 50
            border.color: "red"
            border.width: 4
            Text {
                text: "70"
                font.pixelSize: 30
                anchors.centerIn: parent
            }
        }

        Rectangle {
            height: 10 // Espaçamento específico para este ponto
            width: parent.width
            color: "transparent"
        }

        // Current Speed
        Text {
            id: speed
            text: "42"
            color: "white"
            font.pixelSize: 80
            anchors.horizontalCenter: parent.horizontalCenter
        }


        Text {
            id: speedUnits
            text: "km/h"
            color: "white"
            font.pixelSize: 16
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // // Fuel level
        // // ProgressBar {
        // //     value: 0.7 // Fuel level (70%)
        // //     anchors.horizontalCenter: parent.horizontalCenter
        // //     anchors.top: speedUnits.bottom
        // //     anchors.topMargin: 25
        // //     width: parent.width * 0.9
        // //     height: 10
        // //     // radius: 5
        // // }

        Rectangle {
            height: 20 // Espaçamento específico para este ponto
            width: parent.width
            color: "transparent"
        }


        ProgressBar {
            id: batteryLevel

            anchors.horizontalCenter: parent.horizontalCenter
            // anchors.top: speedUnits.bottom
            // anchors.topMargin: 25
            width: isCenterPanelOn ? parent.width * 0.5 : parent.width * 0.1
            value: 0.7
            padding: 2

            background: Rectangle {
                // implicitWidth: 200 // ver Customization da ajuda
                implicitWidth: parent.width
                implicitHeight: 6
                color: "#e6e6e6"
                radius: 3
            }

            contentItem: Item {
                 // implicitWidth: 200
                implicitWidth: parent.width
                implicitHeight: 4

                Rectangle {
                    width: batteryLevel.visualPosition * parent.width
                    height: parent.height
                    radius: 2
                    color: "#17a81a"
                }
         }
        }


        Text {
            id: batteryInfo
            text: "70%"
            color: "white"
            font.pixelSize: 17
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // // Gear
        // // Text {
        // //     text: "P  R  N  D"
        // //     color: "white"
        // //     font.pixelSize: 20
        // //     anchors.horizontalCenter: parent.horizontalCenter
        // //     anchors.top: batteryInfo.bottom
        // //     anchors.topMargin: 50
        // // }

        Rectangle {
            height: 20 // Espaçamento específico para este ponto
            width: parent.width
            color: "transparent"
        }

        Gear {
            id: gear
            onGearSelected: leftPanel.gearSelected(gear) // Propaga o sinal para o LeftPanel
        }


    }
}
