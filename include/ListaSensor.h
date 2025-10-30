#ifndef LISTASENSOR_H
#define LISTASENSOR_H

/**
 * @file ListaSensor.h
 * @brief Implementación de una lista enlazada genérica.
 */

/**
 * @class ListaSensor
 * @brief Lista enlazada genérica simple para almacenar datos de tipo T.
 * * Esta clase implementa una lista enlazada simple, diseñada para ser utilizada 
 * dentro de clases específicas de sensores para manejar sus lecturas o registros.
 * * @tparam T El tipo de dato a almacenar en la lista (ej., `int`, `float`, o una estructura).
 */
template <typename T>
class ListaSensor {
public:
    /**
     * @brief Estructura de nodo para la lista enlazada.
     */
    struct Nodo {
        T dato;          ///< El dato almacenado en este nodo.
        Nodo* siguiente; ///< Puntero al siguiente nodo en la lista.
        
        /**
         * @brief Constructor del nodo.
         * @param valor El valor del tipo T a almacenar.
         */
        Nodo(T valor) : dato(valor), siguiente(nullptr) {}
    };

private:
    Nodo* cabeza; ///< Puntero al primer nodo de la lista.

public:
    /**
     * @brief Constructor por defecto.
     * * Inicializa la lista como vacía.
     */
    ListaSensor() : cabeza(nullptr) {}
    
    /**
     * @brief Destructor.
     * * Libera la memoria de todos los nodos de la lista para evitar fugas de memoria.
     */
    ~ListaSensor() {
        while (cabeza) {
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }
    
    /**
     * @brief Constructor de copia profunda.
     * * Crea una nueva lista con los mismos elementos que la lista `otra`.
     * @param otra Referencia constante a la lista `ListaSensor` que se va a copiar.
     */
    ListaSensor(const ListaSensor& otra) : cabeza(nullptr) {
        Nodo* actual = otra.cabeza;
        while (actual) {
            agregar(actual->dato); // Usa el método agregar para la copia
            actual = actual->siguiente;
        }
    }

    /**
     * @brief Operador de asignación de copia profunda.
     * * Asigna los elementos de la lista `otra` a la lista actual, liberando 
     * primero los nodos existentes.
     * @param otra Referencia constante a la lista `ListaSensor` fuente.
     * @return Una referencia al objeto actual (`*this`) después de la asignación.
     */
    ListaSensor& operator=(const ListaSensor& otra) {
        if (this != &otra) {
            // Limpiar lista actual
            while (cabeza) {
                Nodo* temp = cabeza;
                cabeza = cabeza->siguiente;
                delete temp;
            }
            // Copiar nueva lista
            Nodo* actual = otra.cabeza;
            while (actual) {
                agregar(actual->dato);
                actual = actual->siguiente;
            }
        }
        return *this;
    }

    /**
     * @brief Agrega un nuevo elemento al final de la lista.
     * @param valor El dato de tipo T a insertar.
     */
    void agregar(T valor) {
        Nodo* nuevoNodo = new Nodo(valor);
        if (!cabeza) {
            cabeza = nuevoNodo;
        } else {
            Nodo* actual = cabeza;
            while (actual->siguiente) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevoNodo;
        }
    }
    
    /**
     * @brief Obtiene un puntero al primer nodo de la lista.
     * @note Útil para iniciar iteraciones externas sobre la lista.
     * @return Puntero constante al nodo inicial (`cabeza`).
     */
    Nodo* obtenerCabeza() const { 
        return cabeza; 
    }
    
    /**
     * @brief Verifica si la lista está vacía.
     * @return `true` si la lista no contiene elementos, `false` en caso contrario.
     */
    bool estaVacia() const {
        return cabeza == nullptr;
    }
    
    /**
     * @brief Cuenta el número de elementos en la lista.
     * @return El número total de nodos en la lista.
     */
    int contar() const {
        int contador = 0;
        Nodo* actual = cabeza;
        while (actual) {
            contador++;
            actual = actual->siguiente;
        }
        return contador;
    }
    
    /**
     * @brief Elimina un nodo específico de la lista.
     * @details Se debe proporcionar el puntero al nodo a eliminar y, si no es la cabeza, 
     * el puntero al nodo anterior para poder re-enlazar la lista.
     * @param anterior Puntero al nodo inmediatamente anterior al nodo a eliminar. Puede ser `nullptr` si se elimina la cabeza.
     * @param eliminar Puntero al nodo que se desea eliminar.
     */
    void eliminarNodo(Nodo* anterior, Nodo* eliminar) {
        if (!eliminar) return;
        
        if (eliminar == cabeza) {
            cabeza = eliminar->siguiente;
        } else if (anterior) {
            anterior->siguiente = eliminar->siguiente;
        }
        delete eliminar;
    }
};

#endif // LISTASENSOR_H