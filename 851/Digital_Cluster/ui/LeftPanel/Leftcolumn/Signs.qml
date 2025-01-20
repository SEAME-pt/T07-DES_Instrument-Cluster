import QtQuick 2.15

Row {
    id: signs
    anchors.horizontalCenter: parent.horizontalCenter
    spacing: 5

    Repeater {
        model: ["icon00", "icon03", "icon13", "icon16"]

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
            }

        }
    }
}
