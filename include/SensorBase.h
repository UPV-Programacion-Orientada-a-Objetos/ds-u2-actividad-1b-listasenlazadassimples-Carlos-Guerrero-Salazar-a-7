#ifndef SENSORBASE_H
#define SENSORBASE_H

#include <cstring>
#include "ListaSensor.h"

// Clase abstracta base para todos los sensores
class SensorBase {
protected:
    char nombre[50];
    
public:
    // Lista estática para registrar todos los sensores creados
    static ListaSensor<SensorBase*> sensoresRegistrados;
    
    // Constructor
    SensorBase(const char* nom) {
        strncpy(nombre, nom, 49);
        nombre[49] = '\0';
        sensoresRegistrados.agregar(this);
    }
    
    // Métodos virtuales puros (interfaz)
    virtual void imprimirInfo() const = 0;
    virtual void procesarLectura() = 0;
    
    // Obtener nombre
    const char* obtenerNombre() const {
        return nombre;
    }
    
    // Destructor virtual (crítico para polimorfismo)
    virtual ~SensorBase() {}
};

#endif // SENSORBASE_H