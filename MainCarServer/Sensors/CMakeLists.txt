cmake_minimum_required(VERSION 3.10)

# Nome do projeto e versão
project(SpeedSensorExample VERSION 1.0)

# Definir o padrão do C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adicionar submódulo para CANBus
add_subdirectory(CANBus)

# Incluir diretórios para os cabeçalhos do CANBus
include_directories(CANBus/includes)

# Incluir diretórios para seus cabeçalhos
include_directories(${PROJECT_SOURCE_DIR}/includes)

# Adicionar os arquivos de origem para a biblioteca SpeedSensor
set(LIB_SOURCES
    sources/SpeedSensor.cpp
)

# Criar a biblioteca estática SpeedSensorLib
add_library(SpeedSensorLib STATIC ${LIB_SOURCES})

# Linkar a biblioteca CANBus
target_link_libraries(SpeedSensorLib PRIVATE CANBus)

# Adicionar testes (opcional)
enable_testing()
add_subdirectory(tests)

# Instalar a biblioteca (opcional)
install(TARGETS SpeedSensorLib DESTINATION lib)

