#ifndef LISTAGENERAL_H
#define LISTAGENERAL_H

#include "SensorBase.h"
#include <iostream>

/**
 * @brief Lista enlazada NO genérica para gestión polimórfica de sensores
 * 
 * Almacena punteros a SensorBase* permitiendo polimorfismo.
 * Es responsable de liberar la memoria de los sensores.
 */
class ListaGeneral {
private:
    // Nodo específico para punteros a SensorBase
    struct Nodo {
        SensorBase* sensor;  // Puntero a clase base (polimorfismo)
        Nodo* siguiente;
        
        Nodo(SensorBase* s) : sensor(s), siguiente(nullptr) {}
    };
    
    Nodo* cabeza;
    int cantidad;

public:
    // Constructor
    ListaGeneral() : cabeza(nullptr), cantidad(0) {}
    
    // Destructor: libera TODOS los sensores
    ~ListaGeneral() {
        
        while (cabeza) {
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            
            std::cout << "  [Destructor] Liberando sensor: " 
                      << temp->sensor->obtenerNombre() << std::endl;
            
            // ¡CRÍTICO! Llamar a delete invoca el destructor virtual
            delete temp->sensor;  // Polimorfismo: llama al destructor correcto
            delete temp;
        }
        
        std::cout << "[ListaGeneral] Memoria liberada completamente\n" << std::endl;
    }
    
    // Agregar sensor a la lista
    void agregar(SensorBase* sensor) {
        Nodo* nuevoNodo = new Nodo(sensor);
        
        if (!cabeza) {
            cabeza = nuevoNodo;
        } else {
            Nodo* actual = cabeza;
            while (actual->siguiente) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevoNodo;
        }
        
        cantidad++;
        std::cout << "[ListaGeneral] Sensor '" << sensor->obtenerNombre() 
                  << "' agregado. Total: " << cantidad << std::endl;
    }
    
    // Buscar sensor por nombre
    SensorBase* buscar(const char* nombre) {
        Nodo* actual = cabeza;
        while (actual) {
            if (strcmp(actual->sensor->obtenerNombre(), nombre) == 0) {
                return actual->sensor;
            }
            actual = actual->siguiente;
        }
        
        return nullptr;  // No encontrado
    }
    
    // Procesar TODOS los sensores (POLIMORFISMO EN ACCIÓN)
    void procesarTodos() {
        std::cout << "\n=== Procesamiento Polimórfico ===" << std::endl;
        
        if (!cabeza) {
            std::cout << "No hay sensores registrados." << std::endl;
            return;
        }
        
        Nodo* actual = cabeza;
        int contador = 1;
        
        while (actual) {
            std::cout << "\n[" << contador << "] Procesando: " 
                      << actual->sensor->obtenerNombre() << std::endl;
            actual->sensor->procesarLectura();
            
            actual = actual->siguiente;
            contador++;
        }
        
        std::cout << "\n=== Procesamiento completado ===" << std::endl;
    }
    
    // Imprimir información de TODOS los sensores
    void imprimirTodos() const {
        std::cout << "\n=== Lista de Sensores Registrados ===" << std::endl;
        
        if (!cabeza) {
            std::cout << "No hay sensores registrados." << std::endl;
            return;
        }
        
        Nodo* actual = cabeza;
        int contador = 1;
        
        while (actual) {
            std::cout << "\n[" << contador << "] ";
            actual->sensor->imprimirInfo();
            
            actual = actual->siguiente;
            contador++;
        }
        
        std::cout << "\nTotal de sensores: " << cantidad << std::endl;
    }
    
    // Verificar si está vacía
    bool estaVacia() const {
        return cabeza == nullptr;
    }
    
    // Obtener cantidad de sensores
    int getCantidad() const {
        return cantidad;
    }
};

#endif // LISTAGENERAL_H