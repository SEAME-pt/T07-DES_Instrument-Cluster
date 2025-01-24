import QtQuick
import QtQuick.Controls 2.15
import "ui/LeftPanel"
import "ui/CenterPanel"

Window {
    width: 1280
    height: 400
    // width: Screen.width
    // height: Screen.height
    visible: true
    // visibility: Window.FullScreen
    title: qsTr("Cluster v2")

    // Permite fechar ao pressionar "Esc", o Focusscope ouve os eventos do teclado
    FocusScope {
            anchors.fill: parent // O FocusScope cobre toda a janela
            focus: true // Garante que o FocusScope capture os eventos de teclado

            Keys.onPressed:  function test (event) {
                if (event.key === Qt.Key_Escape) {
                    Qt.quit(); // Fecha a aplicação
                }
            }
        }

    Rectangle {
        id: root
        width: 1280
        height: 400
        color: "black" // Background color of the cluster

        LeftPanel {
            id: leftPanel

            onGearSelected: function(gear) {
                if (gear === "D") {
                    console.log("Driving mode activated");
                    // centerPanel.push(centerPanel.carDrivingPage);
                } else {
                    console.log("Stopped mode activated");
                    // centerPanel.push(centerPanel.carStoppedPage);
                }
            }

        }

        CenterPanel {
            id: centerPanel
            visible: false

        }

    }

    Rectangle {
        Component.onCompleted: {
            console.log("systemHandler está acessível no QML:", typeof systemHandler);
        }
    }

    // Component.onCompleted: {
    //     console.log("systemHandler está acessível no QML:", systemHandler.speedSensor);
    // }

    // Component.onCompleted: {
    //     console.log("speed no QML: ", systemHandler.speedSensor);
    // }

}
