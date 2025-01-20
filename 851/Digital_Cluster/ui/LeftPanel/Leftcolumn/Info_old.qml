import QtQuick 2.15

Rectangle {

    id: infoLeft

    // anchors.fill: parent

    color: "transparent"

    Text {
        id: hour
        text: "18:42"
        color: "white"
        font.pixelSize: 50
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 35
    }

    Image {
        id: carRender
        source: "../../assets/carRender.jpg"
        anchors.top: hour.bottom
        anchors.topMargin: 60
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * .80
        fillMode: Image.PreserveAspectFit
    }

    MouseArea {
            anchors.fill: parent
            onClicked: leftLoader.source = "Service.qml"
    }

    Text {
        id: totalKms
        text: "4200"
        color: "white"
        font.pixelSize: 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: carRender.bottom
        anchors.topMargin: 20
    }

    Text {
        id: unity
        text: "Km"
        color: "white"
        font.pixelSize: 15
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: totalKms.bottom
        anchors.topMargin: 5
    }
}
