# Define la versión mínima requerida de CMake
cmake_minimum_required(VERSION 3.10)

# Define el nombre del proyecto
project(ProyectoArduino CXX)

# Establece el estándar de C++ (por ejemplo, C++11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 1. Define las rutas de inclusión (¡Soluciona tu error!)
# Esto le dice al compilador dónde buscar los archivos .h
include_directories(include)

# 2. Define las fuentes (archivos .cpp)
# Junta todos los archivos .cpp necesarios para la compilación
file(GLOB SOURCES
    src/*.cpp
    main.cpp
)

# 3. Define el ejecutable
# Crea el ejecutable final llamado 'proyectomain' usando todos los archivos .cpp
add_executable(proyectomain ${SOURCES})

# Opcional: Define la ruta de salida del ejecutable
set_target_properties(proyectomain PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")