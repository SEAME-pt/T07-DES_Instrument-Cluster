#include "zmqreader.h"
#include <QDebug>
#include <cstring>

ZMQReader::ZMQReader(const QString &address, QObject *parent)
    : QThread(parent), m_address(address), m_running(false)
{
    m_context = std::make_unique<zmq::context_t>(1);
    m_socket = std::make_unique<zmq::socket_t>(*m_context, zmq::socket_type::sub);
}

ZMQReader::~ZMQReader()
{
    stop();
    // quit();
    // wait();
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

            // Convertendo a mensagem recebida para int
            float receivedSpeed;
            std::memcpy(&receivedSpeed, message.data(), sizeof(receivedSpeed));
            // qInfo() << "speed: " << receivedSpeed;

            // Emite o sinal para a UI
            // emit speedReceived(receivedSpeed);
            emit speedReceived(static_cast<int>(receivedSpeed));
        }
    } catch (const zmq::error_t &e) {
        qWarning() << "Erro no loop de leitura:" << e.what();
    }
}

void ZMQReader::stop()
{
    m_running = false;

    // if (isRunning()) {
    //     quit();  // Sinaliza o encerramento da thread
    //     wait();  // Aguarda o término da thread
    // }

    if (m_socket) {
        // m_socket->disconnect(m_address.toStdString());
        m_socket->close();
        // m_socket.reset();
    }
    if (m_context) {
        m_context->close();
        // m_context.reset();
    }
     wait();  // Aguarda a thread terminar

}
