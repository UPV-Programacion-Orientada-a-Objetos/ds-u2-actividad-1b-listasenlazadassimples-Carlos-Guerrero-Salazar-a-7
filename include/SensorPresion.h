#ifndef SENSORPRESION_H
#define SENSORPRESION_H

#include "SensorBase.h"
#include <iostream>

// Sensor especializado para lecturas de presión (int)
class SensorPresion : public SensorBase {
private:
    ListaSensor<int> lecturas;
    
public:
    // Constructor
    SensorPresion(const char* nombre);
    
    // Agregar lectura de presión
    void agregarLectura(int valor);
    
    // Implementación de métodos virtuales
    void imprimirInfo() const override;
    void procesarLectura() override;
    
    // Destructor
    ~SensorPresion() override;
};

#endif // SENSORPRESION_H