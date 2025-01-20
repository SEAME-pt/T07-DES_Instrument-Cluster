#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "System.h"
#include "zmqreader.h"
#include <zmq.hpp>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    System m_systemHandler;

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    // colocar aqui o carregar da classe para depois ao carregar o maincomponent carregar tudo
    QQmlContext *context(engine.rootContext());
    context->setContextProperty("systemHandler", &m_systemHandler);

    // Inicializar o ZMQReader
    ZMQReader zmqReader("tcp://localhost:5555"); // Endereço da socket

    // Conecta o sinal de velocidade para o System
    QObject::connect(&zmqReader, &ZMQReader::speedReceived, [&](int speed) {
        m_systemHandler.setSpeedSensor(speed);
    });

    zmqReader.start(); // Inicia a thread

    engine.loadFromModule("Digital_Cluster", "Main");

    if (engine.rootObjects().isEmpty()) {
        qWarning() << "Erro ao carregar o QML.";
        return -1;
    }

    zmqReader.stop();

    return app.exec();

}
