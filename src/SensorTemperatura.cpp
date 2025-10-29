#include "SensorTemperatura.h"

// Constructor
SensorTemperatura::SensorTemperatura(const char* nombre) 
    : SensorBase(nombre) {
}

// Agregar lectura de temperatura
void SensorTemperatura::agregarLectura(float valor) {
    lecturas.agregar(valor);
    std::cout << "Lectura agregada a " << nombre << ": " << valor << "°C" << std::endl;
}

// Imprimir información del sensor
void SensorTemperatura::imprimirInfo() const {
    std::cout << "\n=== Sensor: " << nombre << " (Temperatura) ===" << std::endl;
    
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

// Procesar lecturas: elimina el valor mínimo y calcula promedio
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

// Destructor
SensorTemperatura::~SensorTemperatura() {
    std::cout << "Destruyendo sensor: " << nombre << std::endl;
}