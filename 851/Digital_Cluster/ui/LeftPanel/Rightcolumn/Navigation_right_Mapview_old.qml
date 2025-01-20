import QtQuick 2.15
import QtLocation
import QtPositioning
import Qt5Compat.GraphicalEffects
import QtQuick.Controls


Rectangle {
    id: mapContainer
    color: "transparent"
    anchors {
        fill: parent
    }

    // Define um contêiner Clip para aplicar o arredondamento
    radius: 8
    clip: true
    border.color: "red"
    border.width: 4

    MapView {
            id: view
            anchors.fill: parent
            layer.enabled: true
            z: -1
            // Configuração do mapa
            map {
                plugin: Plugin {
                    name: "osm"
                    parameters: [
                                PluginParameter { name: "osm.mapping.host"; value: "https://{s}.basemaps.cartocdn.com/dark_all/{z}/{x}/{y}{r}.png" }
                            ]
                }


                // zoomLevel: (maximumZoomLevel - minimumZoomLevel) / 2
                zoomLevel: 25
                tilt: 50 // inclinação do mapa
                // colorOverlay: Qt.rgba(0, 0, 0, 0.5) // escurecer o mapa utilizar com Map
                center {
                    latitude: 41.14848
                    longitude: -8.61301
                }

            }

            function geocodeFinished() {
                console.log("Geocodificação finalizada, status:", geocodeModel.status)
                if (geocodeModel.status === GeocodeModel.Ready) {
                    console.log("Resultados encontrados:", geocodeModel.count)
                } else if (geocodeModel.status === GeocodeModel.Error) {
                    console.error("Erro na geocodificação!")
                }
            }

            Rectangle {
                   anchors.fill: parent
                   color: "black"
                   opacity: 0.3 // Ajusta a opacidade para escurecer o mapa
               }

        }


    // GeocodeModel {
    //        id: geocodeModel
    //        plugin: view.map.plugin

    //        onStatusChanged: {
    //            if (status === GeocodeModel.Ready || status === GeocodeModel.Error) {
    //                view.geocodeFinished()

    //                menuList.enabled = true; // para esperar que a consulta seja feita para o adress
    //            }
    //        }

    //        onLocationsChanged: {
    //            if (count > 0) {
    //                console.log("Localizações encontradas:", count)
    //                view.map.center.latitude = get(0).coordinate.latitude
    //                view.map.center.longitude = get(0).coordinate.longitude

    //                menuList.enabled = true; // para esperar que a consulta seja feita para o adress
    //            }
    //        }
    //    }

    // Exibe os resultados da geocodificação no mapa
      // MapItemView {
      //     parent: view.map
      //     model: geocodeModel
      //     delegate: pointDelegate
      // }

      // Template para os pontos no mapa
      // Component {
      //     id: pointDelegate

      //     MapQuickItem {
      //         id: point
      //         parent: view.map
      //         coordinate: locationData.coordinate

      //         sourceItem: Image {
      //             id: pointMarker
      //             source: "../../assets/red_marker.png" // Certifique-se de ter esta imagem no diretório correto
      //         }
      //     }
      // }

      // Component.onCompleted: {
      //       menuList.enabled = false; // desactiva o menu durante a consulta - código assincrono
      //        // Montar a consulta ao carregar o componente
      //        const queryAddress = fromAddress.street + ", " + fromAddress.city + ", " + fromAddress.country
      //        geocodeModel.query = queryAddress
      //        geocodeModel.update()
      //    }

      // Address {
      //     id :fromAddress
      //     street: "Sandakerveien 116"
      //     city: "Oslo"
      //     country: "Norway"
      //     state : ""
      //     postalCode: "0484"
      // }


        // color: "orange"


        MapItemView {
                   id: mapItem
                   parent: view.map
                   // visible: false

                   model: ListModel {
                       id: markersModel
                       ListElement {
                           latitude: 41.14848
                           longitude: -8.61301
                           icon: "../../assets/red_marker.png" // Marcador inicial
                       }
                       // ListElement {
                       //     latitude: 59.9645
                       //     longitude: 10.671
                       //     icon: "../../assets/red_marker.png" // Marcador final
                       // }
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

