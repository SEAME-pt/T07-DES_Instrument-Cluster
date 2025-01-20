import QtQuick 2.15
import QtQuick.Controls 2.15


Rectangle {
    id: centerPanel

    color: "#2F2F2F"
    radius: 8

    anchors {
        left: leftPanel.right
        right: parent.right
        bottom: parent.bottom
        top: parent.top
        margins: 10
    }

    Loader {
        id: rightLoader
        anchors {
            fill: parent
        }
        source: "Navigation.qml"

    }

    Bottombar {
        id: bottomBar
    }

}


// StackView {
//     id: centerPanel
//     // anchors.fill: parent
//     initialItem: carDrivingPage


//     anchors {
//         left: leftPanel.right
//         right: parent.right
//         bottom: parent.bottom
//         top: parent.top
//         margins: 5
//     }

//     property Component carStoppedPage: carStoppedPage
//     property Component carDrivingPage: carDrivingPage

//     Component {
//         id: carStoppedPage
//         Rectangle {
//             color: "gray"
//             anchors.fill: parent
//             Text {
//                 text: "Car Stopped"
//                 color: "white"
//                 font.pixelSize: 30
//                 anchors.centerIn: parent
//             }
//         }
//     }

//     Component {
//         id: carDrivingPage
//         Rectangle {
//             color: "green"
//             anchors.fill: parent
//             Text {
//                 text: "Car Driving"
//                 color: "white"
//                 font.pixelSize: 30
//                 anchors.centerIn: parent
//             }
//         }
//     }
// }

