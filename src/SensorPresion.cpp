/**
 * @file SensorPresion.cpp
 * @brief Implementación de la clase SensorPresion.
 * @details Esta clase hereda de SensorBase y proporciona funcionalidades específicas para sensores de presión.
 * @author Carlos Gael Guerrero Salazar
 * @date 2025-10-29
 * @version 1.0
 */
#include "SensorPresion.h"

/**
 * @brief Constructor de la clase SensorPresion.
 * @param nombre Nombre del sensor.
 */
SensorPresion::SensorPresion(const char* nombre) 
    : SensorBase(nombre) {
}

/**
 * @brief Agrega un nodo al sensor de presión.
 * @param valor es el valor de la lectura a agregar.
 * @details al ser unicamente para int el sensorpresion no es necesario implementar un template
 */
void SensorPresion::agregarLectura(int valor) {
        lecturas.agregar(valor);
    }
    
    /**
    * @brief Imprime la información del sensor de presión.
    * @details Con el dato privado de cabeza de lista, recorre toda la lista de nodos dentro de ella para mostrarlas
    */
    void SensorPresion::imprimirInfo() const {
        auto* actual = lecturas.obtenerCabeza();
        std::cout << "Lecturas de Presion: ";
        while (actual) {
            std::cout << actual->dato << " ";
            actual = actual->siguiente;
        }
        std::cout << std::endl;
    }
    /**
     * @brief Procesa las lecturas de presión.
     * @details Calcula el promedio de las lecturas y lo muestra por consola.
     * El hecho de ser un sensor de presión no implica que no se pueda hacer un procesamiento polimórfico, por lo que solo calcula el promedio.
     */
    void SensorPresion::procesarLectura() {
        // Calcular el promedio de las lecturas de presión
        int suma = 0;
        int contador = 0;
        auto* actual = lecturas.obtenerCabeza();
        
        while (actual) {
            suma += actual->dato;
            contador++;
            actual = actual->siguiente;
        }
        
        if (contador > 0) {
            int promedio = suma / contador;
            std::cout << "Promedio de presion: " << promedio << std::endl;
        }
    }
    /**
     * @brief Destructor de la clase SensorPresion.
     * @details Libera la memoria utilizada por la lista de lecturas.
     */
    SensorPresion::~SensorPresion(){
        std::cout << "Destruyendo sensor de presión: " << nombre << std::endl;
        lecturas.~ListaSensor();
    }