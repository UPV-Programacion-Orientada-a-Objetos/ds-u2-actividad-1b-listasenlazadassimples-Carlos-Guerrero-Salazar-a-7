cmake_minimum_required(VERSION 3.10)
project(SistemaMonitoreoIoT)

set(CMAKE_CXX_STANDARD 11)

# Directorios de inclusión
include_directories(include)

# Archivos fuente
set(SOURCES
    src/main.cpp
    src/SensorBase.cpp
    src/SensorTemperatura.cpp
    src/SensorPresion.cpp
    src/SerialReader.cpp
)

# Ejecutable
add_executable(sensor_system ${SOURCES})