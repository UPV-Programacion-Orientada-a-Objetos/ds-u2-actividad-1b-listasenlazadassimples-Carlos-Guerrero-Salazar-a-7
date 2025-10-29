#include "SensorPresion.h"
SensorPresion::SensorPresion(const char* nombre) 
    : SensorBase(nombre) {
}

void SensorPresion::agregarLectura(int valor) {
        lecturas.agregar(valor);
    }
    
    void SensorPresion::imprimirInfo() const {
        auto* actual = lecturas.obtenerCabeza();
        std::cout << "Lecturas de Presion: ";
        while (actual) {
            std::cout << actual->dato << " ";
            actual = actual->siguiente;
        }
        std::cout << std::endl;
    }
    
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
    
    SensorPresion::~SensorPresion(){
        std::cout << "Destruyendo sensor de presión: " << nombre << std::endl;
        lecturas.~ListaSensor();
    }