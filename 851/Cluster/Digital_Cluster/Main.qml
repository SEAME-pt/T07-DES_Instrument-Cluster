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

        signal gearSelected(string gear)

        property string gearRoot: "P" // tem P no Gear ao inicio

        LeftPanel {
            id: leftPanel
            property bool isCenterPanelOn
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


        StackView {
            id: stackview
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.margins: 10
            width: parent.width - (parent.height * 0.618 + 10)
            initialItem: Item {width: 0; height: 0}
            pushEnter: Transition {
                    PropertyAnimation {
                        property: "x"
                        from: stackview.width // Começa fora da tela (direita)
                        to: 0                 // Fica visível na posição final
                        duration: 1000
                        easing.type: Easing.OutCubic
                    }
            }
        }

        // mudar esta função tem que aceitar o navigation
        onGearSelected: function (gear) {
            console.log("gear no root: ", gear);
            // gearRoot = gear;
            if(gear === "D" && gearRoot !== "D") {
                leftPanel.isCenterPanelOn = true;
                // centerLoader.source = "ui/CenterPanel/CenterPanel.qml";
                gearRoot = gear;
                stackview.push("ui/CenterPanel/CenterPanel.qml")
            } else if (gear !== "D" ){
                leftPanel.isCenterPanelOn = false;
                // centerLoader.source = "";
                gearRoot = gear;
                stackview.pop();
            }
        }
    }

    //teste c++ -> QML
    Rectangle {
        Component.onCompleted: {
            console.log("systemHandler está acessível no QML:", typeof systemHandler);
        }
    }

}
