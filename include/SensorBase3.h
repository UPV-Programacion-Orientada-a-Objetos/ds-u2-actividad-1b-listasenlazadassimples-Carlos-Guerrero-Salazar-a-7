#ifndef SENSORBASE_H
#define SENSORBASE_H

#include <iostream>

// Lista genérica para almacenar lecturas de sensores
template <typename T>
class ListaSensor {
public:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        Nodo(T valor) : dato(valor), siguiente(nullptr) {}
    };
    Nodo* cabeza;
    ListaSensor() : cabeza(nullptr) {}
    
    ~ListaSensor() {
        while (cabeza) {
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }
    ListaSensor(const ListaSensor& otra) : cabeza(nullptr) {
    Nodo* actual = otra.cabeza;
    while (actual) {
        agregar(actual->dato);
        actual = actual->siguiente;
    }
}

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
    
    // Métodos para acceder a los datos
    Nodo* obtenerCabeza() const { return cabeza; }
    
    // Método para eliminar un nodo específico
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

class SensorBase {
protected:
    char _nombre[50];
    
public:
    static ListaSensor<SensorBase*> sensoresRegistrados;
    SensorBase(char _nombre,char* nombre[], size_t tamaño) {
        sensoresRegistrados.agregar(this);
    }
    virtual void imprimirinfo() const = 0;
    virtual void procesarLectura() = 0;
    virtual ~SensorBase() {}
};

class SensorTemperatura : public SensorBase {
private:
    ListaSensor<float> lecturas;
    
public:
    SensorTemperatura(const char* nombre) : SensorBase(_nombre, nombre, sizeof(_nombre)) {
    }
    
    void agregarLectura(float valor) {
        lecturas.agregar(valor);
    }
    
    void imprimirinfo() const override {
        ListaSensor<float>::Nodo* actual = lecturas.obtenerCabeza();
        std::cout << "Lecturas de Temperatura: ";
        while (actual) {
            std::cout << actual->dato << " ";
            actual = actual->siguiente;
        }
        std::cout << std::endl;
    }
    
    void procesarLectura() override {
        // Borra el que tenga el número más bajo
        ListaSensor<float>::Nodo* actual = lecturas.obtenerCabeza();
        if (!actual) return;
        ListaSensor<float>::Nodo* anterior = nullptr;
        ListaSensor<float>::Nodo* nodoMinimo = actual;
        ListaSensor<float>::Nodo* anteriorMinimo = nullptr;
        
        // Buscar el nodo con el valor mínimo
        while (actual) {
            if (actual->dato < nodoMinimo->dato) {
                nodoMinimo = actual;
                anteriorMinimo = anterior;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
        
        // Eliminar el nodo mínimo
        lecturas.eliminarNodo(anteriorMinimo, nodoMinimo);
        float promedio = 0.0f;
        int contador = 0;
        actual = lecturas.obtenerCabeza();
        while(actual){
            promedio += actual->dato;
            contador++;
            actual = actual->siguiente;
        }
        if (contador > 0) {
            promedio /= contador;
            std::cout << "Promedio de lecturas restantes: " << promedio << std::endl;
        }
    }
    
    ~SensorTemperatura() override = default;
};

class SensorPresion : public SensorBase {
private:
    ListaSensor<int> lecturas;
    
public:
    void agregarLectura(int valor) {
        lecturas.agregar(valor);
    }
    
    void imprimirinfo() const override {
        auto* actual = lecturas.obtenerCabeza();
        std::cout << "Lecturas de Presion: ";
        while (actual) {
            std::cout << actual->dato << " ";
            actual = actual->siguiente;
        }
        std::cout << std::endl;
    }
    
    void procesarLectura() override {
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
    
    ~SensorPresion() override = default;
};

#endif