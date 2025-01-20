import QtQuick 2.15

Rectangle {
        id: route
        anchors.fill: parent
        color: "transparent"

        Canvas {
            id: routeCanvas
            anchors.fill: parent
            onPaint: {
                var ctx = routeCanvas.getContext("2d")
                ctx.clearRect(0, 0, width, height)

                // Estrada central (trapézio preto)
                ctx.fillStyle = "#2F2F2F"
                ctx.beginPath()
                ctx.moveTo(width * 0.25, height)   // Base esquerda mais aberta
                ctx.lineTo(width * 0.75, height)   // Base direita mais aberta
                ctx.lineTo(width * 0.6, height / 3) // Ponto superior direito
                ctx.lineTo(width * 0.4, height / 3) // Ponto superior esquerdo
                ctx.closePath()
                ctx.fill()

                // Lateral esquerda com inclinação ajustada
                // var gradientLeft = ctx.createLinearGradient(width * 0.25, height, width * 0.4, height / 3)
                // gradientLeft.addColorStop(0, "#2E2E2E") // Tom mais escuro na base
                // gradientLeft.addColorStop(1, "#8A8A8A") // Tom mais claro no topo
                // ctx.fillStyle = gradientLeft
                // ctx.beginPath()
                // ctx.moveTo(width * 0.25, height)       // Base extrema esquerda
                // ctx.lineTo(width * 0.4, height / 3)   // Ponto superior esquerdo
                // ctx.lineTo(width * 0.3, height / 3)   // Lateral interna
                // ctx.lineTo(width * 0.2, height)       // Base interna esquerda
                // ctx.closePath()
                // ctx.fill()
                var gradientLeft = ctx.createLinearGradient(width * 0.30, height / 3, width * 0.30, height)
                gradientLeft.addColorStop(0, "#2E2E2E") // Tom mais escuro no topo
                gradientLeft.addColorStop(1, "#8A8A8A") // Tom mais claro na base
                ctx.fillStyle = gradientLeft
                ctx.beginPath()
                ctx.moveTo(width * 0.25, height)       // Base extrema esquerda (maior base inferior)
                ctx.lineTo(width * 0.4, height / 3)   // Ponto superior esquerdo (menor base superior)
                ctx.lineTo(width * 0.3, height / 3)   // Ponto interno superior
                ctx.lineTo(width * 0.1, height)       // Base interna esquerda
                ctx.closePath()
                ctx.fill()


                // Lateral direita com inclinação ajustada
                // var gradientRight = ctx.createLinearGradient(width * 0.6, height / 3, width * 0.6, height)
                // gradientRight.addColorStop(0, "#2E2E2E") // Tom mais escuro na base
                // gradientRight.addColorStop(1, "#8A8A8A") // Tom mais claro no topo
                // ctx.fillStyle = gradientRight
                // ctx.beginPath()
                // ctx.moveTo(width * 0.75, height)       // Base extrema direita
                // ctx.lineTo(width * 0.6, height / 3)   // Ponto superior direito
                // ctx.lineTo(width * 0.7, height / 3)   // Lateral interna
                // ctx.lineTo(width * 0.8, height)       // Base interna direita
                // ctx.closePath()
                // ctx.fill()

                var gradientRight = ctx.createLinearGradient(width * 0.7, height / 3, width * 0.7, height)
                gradientRight.addColorStop(0, "#2E2E2E") // Tom mais escuro no topo
                gradientRight.addColorStop(1, "#8A8A8A") // Tom mais claro na base
                ctx.fillStyle = gradientRight
                ctx.beginPath()
                ctx.moveTo(width * 0.75, height)        // Base extrema direita (maior base inferior)
                ctx.lineTo(width * 0.6, height / 3)     // Ponto superior direito (menor base superior)
                ctx.lineTo(width * 0.7, height / 3)     // Ponto interno superior
                ctx.lineTo(width * 0.9, height)         // Base interna direita
                ctx.closePath()
                ctx.fill()


                // Linhas de limite brancas (efeito 3D)
                // ctx.strokeStyle = "#EAEAEA" // Tom claro para realçar as bordas
                // ctx.lineWidth = 2

                // // Lateral esquerda
                // ctx.beginPath()
                // ctx.moveTo(width * 0.25, height)   // Base esquerda externa
                // ctx.lineTo(width * 0.4, height / 3) // Ponto superior esquerdo
                // ctx.stroke()

                // // Lateral direita
                // ctx.beginPath()
                // ctx.moveTo(width * 0.75, height)   // Base direita externa
                // ctx.lineTo(width * 0.6, height / 3) // Ponto superior direito
                // ctx.stroke()
            }
        }
    }
