#ifndef LISTASENSOR_H
#define LISTASENSOR_H

// Template de lista enlazada genérica
template <typename T>
class ListaSensor {
public:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        Nodo(T valor) : dato(valor), siguiente(nullptr) {}
    };

private:
    Nodo* cabeza;

public:
    // Constructor
    ListaSensor() : cabeza(nullptr) {}
    
    // Destructor
    ~ListaSensor() {
        while (cabeza) {
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }
    
    // Constructor de copia
    ListaSensor(const ListaSensor& otra) : cabeza(nullptr) {
        Nodo* actual = otra.cabeza;
        while (actual) {
            agregar(actual->dato);
            actual = actual->siguiente;
        }
    }

    // Operador de asignación
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

    // Agregar elemento al final
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
    
    // Obtener primer nodo
    Nodo* obtenerCabeza() const { 
        return cabeza; 
    }
    
    // Verificar si la lista está vacía
    bool estaVacia() const {
        return cabeza == nullptr;
    }
    
    // Contar elementos
    int contar() const {
        int contador = 0;
        Nodo* actual = cabeza;
        while (actual) {
            contador++;
            actual = actual->siguiente;
        }
        return contador;
    }
    
    // Eliminar un nodo específico
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