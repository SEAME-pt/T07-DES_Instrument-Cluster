#include "zmqreader.h"
#include <QDebug>
#include <cstring>
#include <iostream>

ZMQReader::ZMQReader(const QString &address, QObject *parent)
    : QThread(parent), m_address(address), m_running(false)
{
    m_context = std::make_unique<zmq::context_t>(1);
    m_socket = std::make_unique<zmq::socket_t>(*m_context, zmq::socket_type::sub);
}

ZMQReader::~ZMQReader()
{
    stop();
}

void ZMQReader::run()
{
    try {
        m_socket->connect(m_address.toStdString());
        m_socket->set(zmq::sockopt::subscribe, "");

        m_running = true;

        while (m_running) {
            if (!m_context) {
                qWarning() << "Contexto foi destruído ou não está mais ativo!";
                break; // Sai do loop se o contexto não for mais válido
            }
            zmq::message_t message;

            zmq::recv_result_t result = m_socket->recv(message, zmq::recv_flags::none);

            if (!result) {
                if (!m_running) break;
                qWarning() << "Erro ao receber mensagem!";
                continue;
            }

            // QString msg = QString::fromUtf8(static_cast<const char*>(message.data()), message.size());
            std::string msg(static_cast<const char*>(message.data()), message.size());

            std::cout << "Message: " << msg << std::endl;

            // auto parts = QString::fromStdString(msg).split(" ");
            QString qMsg = QString::fromStdString(msg);
            auto parts = qMsg.split(" ");

            if (parts.size() == 2 && parts[0] == "speed") {
                emit speedReceived(parts[1]);
            } else if (parts.size() == 2 && parts[0] == "battery") {
                emit batteryReceived(parts[1]);
            } else if (parts.size() == 2 && parts[0] == "lightshigh") {
                emit headLightsReceived(parts[1]);
            } else if (parts.size() == 2 && parts[0] == "lightsemergency") {
                emit emergencyLightsReceived(parts[1]);
            } else if (parts.size() == 2 && parts[0] == "lightsleft") {
                emit turnLightLeftReceived(parts[1]);
            } else if (parts.size() == 2 && parts[0] == "lightsright") {
                emit turnLightRightReceived(parts[1]);
            }


            // Imprime a string na consola
            //qDebug() << "Mensagem recebida:" << speedString;


            // Emite o sinal para a UI
            //emit speedReceived(speedString);


        }
    } catch (const zmq::error_t &e) {
        qWarning() << "Erro no loop de leitura:" << e.what();
    }
}

void ZMQReader::stop()
{
    m_running = false;

    if (m_socket) {
        m_socket->close();
    }
    if (m_context) {
        m_context->close();
    }
     wait();  // Aguarda a thread terminar

}
