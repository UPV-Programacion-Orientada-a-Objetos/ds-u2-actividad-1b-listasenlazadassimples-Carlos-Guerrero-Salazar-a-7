#ifndef LISTAGENERAL_H
#define LISTAGENERAL_H

#include "SensorBase.h"
#include <iostream>
#include <cstring> // Necesario para strcmp

/**
 * @brief Lista enlazada NO genérica para gestión polimórfica de sensores
 * @details Almacena punteros a SensorBase* permitiendo el polimorfismo.
 * Es responsable de liberar la memoria de los objetos de sensor
 * apuntados al ser destruida (propiedad de la lista).
 */
class ListaGeneral {
private:
    /**
     * @brief Estructura de nodo para la lista enlazada.
     * * Almacena un puntero a un objeto derivado de SensorBase y el puntero al siguiente nodo.
     */
    struct Nodo {
        SensorBase* sensor;  ///< Puntero a clase base (polimorfismo).
        Nodo* siguiente;     ///< Puntero al siguiente nodo en la lista.
        
        /**
         * @brief Constructor del nodo.
         * @param s Puntero al objeto SensorBase o derivado a almacenar.
         */
        Nodo(SensorBase* s) : sensor(s), siguiente(nullptr) {}
    };
    
    Nodo* cabeza; ///< Puntero al primer nodo de la lista.
    int cantidad; ///< Número actual de sensores en la lista.

public:
    /**
     * @brief Constructor por defecto.
     */
    ListaGeneral() : cabeza(nullptr), cantidad(0) {}
    
    /**
     * @brief Destructor.
     * * Recorre la lista, libera la memoria de cada objeto SensorBase y luego la del propio nodo.
     */
    ~ListaGeneral() {
        
        while (cabeza) {
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            
            std::cout << "  [Destructor] Liberando sensor: " 
                      << temp->sensor->obtenerNombre() << std::endl;
            delete temp->sensor; // Liberar la memoria del sensor (polimorfismo)
            delete temp;         // Liberar la memoria del nodo
        }
        
        std::cout << "[ListaGeneral] Memoria liberada completamente\n" << std::endl;
    }
    
    /**
     * @brief Agrega un sensor al final de la lista.
     * * La lista toma la propiedad del puntero sensor y es responsable de su liberación.
     * @param sensor Puntero al objeto SensorBase o derivado a agregar.
     */
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
    
    /**
     * @brief Busca un sensor por su nombre.
     * @param nombre Cadena de caracteres con el nombre del sensor a buscar.
     * @return Puntero al objeto SensorBase si es encontrado, o nullptr si no existe.
     */
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
    
    /**
     * @brief Itera sobre la lista y llama polimórficamente a procesarLectura() 
     * de cada sensor.
     */
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
            actual->sensor->procesarLectura(); // Llamada polimórfica
            
            actual = actual->siguiente;
            contador++;
        }
        
        std::cout << "\n=== Procesamiento completado ===" << std::endl;
    }
    
    /**
     * @brief Itera sobre la lista y llama polimórficamente a imprimirInfo() 
     * de cada sensor.
     */
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
            actual->sensor->imprimirInfo(); // Llamada polimórfica
            
            actual = actual->siguiente;
            contador++;
        }
        
        std::cout << "\nTotal de sensores: " << cantidad << std::endl;
    }
    
    /**
     * @brief Verifica si la lista está vacía.
     * @return true si no hay sensores, false en caso contrario.
     */
    bool estaVacia() const {
        return cabeza == nullptr;
    }
    
    /**
     * @brief Obtiene la cantidad de sensores en la lista.
     * @return El número de sensores.
     */
    int getCantidad() const {
        return cantidad;
    }
};

#endif // LISTAGENERAL_H