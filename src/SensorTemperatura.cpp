/**
 * @file SensorTemperatura.cpp
 * @brief Implementación de la clase SensorTemperatura.
 * @details Esta clase hereda de SensorBase y proporciona funcionalidades específicas para sensores de temperatura.
 * @author Carlos Gael Guerrero Salazar
 * @date 2025-10-29
 * @version 1.0
 */
#include "SensorTemperatura.h"

/**
 * @brief Constructor de la clase SensorTemperatura.
 * @param nombre Nombre del sensor.
 */
SensorTemperatura::SensorTemperatura(const char* nombre) 
    : SensorBase(nombre) {
}

/**
 * @brief Agrega una lectura de temperatura al sensor.
 * @param valor Valor de la lectura a agregar.
 * @details Utiliza el método agregar de ListaSensor para añadir la lectura, por lo cual no necesita un template.
 */
void SensorTemperatura::agregarLectura(float valor) {
    lecturas.agregar(valor);
}

/**
    * @brief Imprime la información del sensor de temperatura.
    * @details Con el dato privado de cabeza de lista, recorre toda la lista de nodos dentro de ella para mostrarlas
    */
void SensorTemperatura::imprimirInfo() const {
    std::cout << "Lecturas de Temperatura: ";
    if (lecturas.estaVacia()) {
        std::cout << "No hay lecturas registradas." << std::endl;
        return;
    }
    
    ListaSensor<float>::Nodo* actual = lecturas.obtenerCabeza();
    std::cout << "Lecturas de Temperatura: ";
    while (actual) {
        std::cout << actual->dato << "°C ";
        actual = actual->siguiente;
    }
    std::cout << std::endl;
}

/**
 * @brief Procesa las lecturas de temperatura.
 * @details Esto hace dos procesos busca los el nodo de sus valores más bajo y lo borra para luego, calcular el promedio de las lecturas y lo muestra por consola.
 * El sensor temperatura hace polimorfismo aquí, es una accion unica que comparte nombre en sensorpresion pero con diferente acción
 */
void SensorTemperatura::procesarLectura() {
    std::cout << "\n>>> Procesando lecturas de " << nombre << " <<<" << std::endl;
    
    ListaSensor<float>::Nodo* actual = lecturas.obtenerCabeza();
    if (!actual) {
        std::cout << "No hay lecturas para procesar." << std::endl;
        return;
    }
    
    // Si solo hay una lectura, no se puede eliminar
    if (!actual->siguiente) {
        std::cout << "Solo hay una lectura, no se puede eliminar." << std::endl;
        std::cout << "Valor actual: " << actual->dato << "°C" << std::endl;
        return;
    }
    
    // Buscar el nodo con el valor mínimo
    ListaSensor<float>::Nodo* anterior = nullptr;
    ListaSensor<float>::Nodo* nodoMinimo = actual;
    ListaSensor<float>::Nodo* anteriorMinimo = nullptr;
    
    while (actual) {
        if (actual->dato < nodoMinimo->dato) {
            nodoMinimo = actual;
            anteriorMinimo = anterior;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    
    std::cout << "lectura mínima a eliminar: " << nodoMinimo->dato << std::endl;
    
    // Eliminar el nodo mínimo
    lecturas.eliminarNodo(anteriorMinimo, nodoMinimo);
    
    // Calcular promedio de lecturas restantes
    float promedio = 0.0f;
    int contador = 0;
    actual = lecturas.obtenerCabeza();
    
    while (actual) {
        promedio += actual->dato;
        contador++;
        actual = actual->siguiente;
    }
    
    if (contador > 0) {
        promedio /= contador;
        std::cout << "Promedio de lecturas restantes (" << contador << " valores): " 
                  << promedio << "°C" << std::endl;
    }
}

/**
 * @brief destructor del sensor
 */
SensorTemperatura::~SensorTemperatura() {
    std::cout << "Destruyendo sensor: " << nombre << std::endl;
}