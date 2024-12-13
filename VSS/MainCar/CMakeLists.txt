cmake_minimum_required(VERSION 3.10)
project(Module02_ex01-modularity)

set(CMAKE_CXX_STANDARD 17)

# Adiciona o spdlog usando FetchContent
include(FetchContent)
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.11.0
)
FetchContent_MakeAvailable(spdlog)

# Inclui os arquivos gerados do módulo vehicle_speed
add_subdirectory(cpp/modules/vehicle_speed)

# Define o executável principal
add_executable(parts 
    sources/main.cpp 
    sources/ACar.cpp 
    sources/SomeCar.cpp 
    sources/Part.cpp 
    sources/partAll.cpp 
    sources/CANBus.cpp 
    sources/SpeedSensor.cpp
)

# Diretórios de includes
target_include_directories(parts PUBLIC includes)

# Liga o spdlog ao executável
target_link_libraries(parts PRIVATE spdlog::spdlog)

# Liga o módulo vehicle_speed ao executável
target_link_libraries(parts PRIVATE vehicle_speed-core vehicle_speed-implementation)

# Configuração de testes
enable_testing()
add_test(NAME Runs COMMAND parts)
