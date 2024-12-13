#include "SpeedSensor.hpp"

SpeedSensor::SpeedSensor(CANBus& can, uint32_t id) : ISensor(can, id), lastSpeed(0) {
    file_logger = spdlog::basic_logger_mt("SpeedSensor", "speed_sensor.log");
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

            // Se os dados tiverem o tamanho esperado (4 bytes para um inteiro de 32 bits)
            if (data.size() >= 4) {
                int value = 0;

                // Converte os 4 primeiros bytes para um valor inteiro
                value = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];

                std::cout << "Valor interpretado do CAN: " << value << std::endl;
                return value; // Retorna o valor interpretado como inteiro
            } else {
                std::cout << "Dados insuficientes para interpretar como inteiro." << std::endl;
                return -1; // Retorna um erro, ou algum valor indicativo
            }
        } else {
            std::cout << "Mensagem ignorada com ID inesperado: 0x" 
                      << std::hex << id << std::dec << std::endl;
        }
    } else {
        std::cout << "Nenhuma mensagem disponível no barramento CAN." << std::endl;
        return -1; // Retorna um erro em caso de falha na leitura
    }

    return 0; // Retorno padrão, embora não deva ser alcançado
}

const std::string SpeedSensor::getType() const{
    return "SpeedSensor";
}


