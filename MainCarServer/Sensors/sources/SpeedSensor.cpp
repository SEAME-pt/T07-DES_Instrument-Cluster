#include "SpeedSensor.hpp"

SpeedSensor::SpeedSensor(CANBus& can, uint32_t id) : ISensor(can, id), _lastSpeed(0) {
    ;
}

void SpeedSensor::initialize() {
    std::cout << "Inicializando sensor de velocidade..." << std::endl;
}

int SpeedSensor::readData() {
    uint32_t id;
    std::vector<uint8_t> data;

    // Verifica se há mensagem disponível no barramento CAN e lê os dados
    if (canBus.receiveMessage(id, data)) {
        // Verifica se o ID da mensagem é o esperado
        if (id == canId) {
            std::cout << "Mensagem recebida com ID: 0x" 
                      << std::hex << id << std::dec << "\nDados: ";

            // Imprime os dados recebidos no formato hexadecimal
            for (size_t i = 0; i < data.size(); ++i) {
                std::cout << "0x" << std::hex << (int)data[i] << " ";
            }

            std::cout << std::dec << std::endl; // Retorna ao formato decimal

            // Verifica se temos dados suficientes para interpretar um valor de velocidade
            if (data.size() >= sizeof(float)) {
                // Supondo que os dados estejam em formato little-endian (ou big-endian se for necessário)
                // Converte os primeiros 4 bytes para um valor do tipo float
                uint32_t rawData = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);

                // Faz a conversão de uint32_t para float
                float sensorValue;
                std::memcpy(&sensorValue, &rawData, sizeof(sensorValue));

                // Atribui o valor ao atributo _lastSpeed
                _lastSpeed = sensorValue;

                std::cout << "Velocidade lida: " << _lastSpeed << " m/s" << std::endl;

                return 0; // Sucesso
            } else {
                std::cerr << "Erro: Dados insuficientes para interpretar o valor de velocidade." << std::endl;
                return -1; // Erro: Dados insuficientes
            }
        } else {
            std::cout << "Mensagem ignorada com ID inesperado: 0x" 
                      << std::hex << id << std::dec << std::endl;
            return -1; // Erro: ID inesperado
        }
    } else {
        std::cout << "Nenhuma mensagem disponível no barramento CAN." << std::endl;
        return -1; // Erro: Nenhuma mensagem
    }
}

const float SpeedSensor::getValue() const {
    return _lastSpeed;
}

const std::string SpeedSensor::getType() const{
    return "SpeedSensor";
}


