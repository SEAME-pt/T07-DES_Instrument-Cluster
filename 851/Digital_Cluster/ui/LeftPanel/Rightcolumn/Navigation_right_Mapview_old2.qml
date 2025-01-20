import QtQuick 2.15
import QtLocation
import QtPositioning
import Qt5Compat.GraphicalEffects
import QtQuick.Controls

Rectangle {
    id: mapContainer
    color: "transparent"
    anchors.fill: parent
    radius: 8
    clip: true
    border.color: "red"
    border.width: 4

    // Usa ShaderEffectSource para aplicar bordas arredondadas
    ShaderEffectSource {
        anchors.fill: parent
        live: true
        recursive: true
        sourceItem: MapView {
            id: view
            anchors.fill: parent
            layer.enabled: true

            // Configuração do mapa
            map {
                plugin: Plugin {
                    name: "osm"
                    parameters: [
                        PluginParameter {
                            name: "osm.mapping.host"
                            value: "https://{s}.basemaps.cartocdn.com/dark_all/{z}/{x}/{y}{r}.png"
                        }
                    ]
                }

                zoomLevel: 25
                tilt: 50 // Inclinação do mapa
                center {
                    latitude: 41.14848
                    longitude: -8.61301
                }
            }

            // Rectangle {
            //     anchors.fill: parent
            //     color: "black"
            //     opacity: 0.3
            // }
        }
    }

    // Adiciona os marcadores no mapa
    MapItemView {
        id: mapItem
        parent: view.map

        model: ListModel {
            id: markersModel
            ListElement {
                latitude: 41.14848
                longitude: -8.61301
                icon: "../../assets/red_marker.png" // Marcador inicial
            }
        }

        delegate: MapQuickItem {
            id: marker
            parent: view.map
            coordinate: QtPositioning.coordinate(latitude, longitude)
            anchorPoint.x: markerImage.width / 2
            anchorPoint.y: markerImage.height
            sourceItem: Image {
                id: markerImage
                source: icon
                width: 32
                height: 32
            }
        }
    }
}



// SequentialAnimation {
//     loops: Animation.Infinite
//     NumberAnimation { target: map; property: "tilt"; from: 0; to: 45; duration: 2000 }
//     NumberAnimation { target: map; property: "tilt"; from: 45; to: 0; duration: 2000 }
// }

