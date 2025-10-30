# Define la versión mínima requerida de CMake
cmake_minimum_required(VERSION 3.10)

# Define el nombre del proyecto
project(ProyectoArduino CXX)

# Establece el estándar de C++ (por ejemplo, C++11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 1. Define las rutas de inclusión
include_directories(include)

# 2. Define las fuentes (archivos .cpp)
file(GLOB SOURCES
    src/*.cpp
    main.cpp
)

# 3. Define el ejecutable
add_executable(proyectomain ${SOURCES})

# Opcional: Define la ruta de salida del ejecutable
set_target_properties(proyectomain PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# --- INTEGRACIÓN DOXYGEN ---

# 4. Busca el programa Doxygen
find_package(Doxygen)

if (DOXYGEN_FOUND)
    message(STATUS "Doxygen encontrado. Configurando la documentación...")
    
    # 5. Define la plantilla y la ruta de salida del Doxyfile generado
    # Nota: Debes crear un archivo Doxyfile.in en la raíz del proyecto.
    set(DOXYFILE_IN "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in")
    set(DOXYFILE_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")

    # 6. Genera la configuración final (Doxyfile) reemplazando variables de CMake
    configure_file(
        ${DOXYFILE_IN}
        ${DOXYFILE_OUT}
        @ONLY
    )

    # 7. Crea el target 'doc' para generar la documentación
    # Usamos la función FindDoxygen (disponible desde CMake 3.4)
    doxygen_add_docs(
        doc 
        ${DOXYFILE_OUT}
        # Indicamos a Doxygen dónde encontrar las fuentes para documentar
        # Se puede listar explícitamente, o usar la configuración del Doxyfile.in
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
    
    # Opcional: Para que 'make all' también genere la documentación
    # add_dependencies(all doc)
else()
    message(WARNING "Doxygen no encontrado. La documentación no se generará.")
endif()