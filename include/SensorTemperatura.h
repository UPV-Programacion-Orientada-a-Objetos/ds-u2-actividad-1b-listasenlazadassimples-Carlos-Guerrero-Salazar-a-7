#ifndef SENSORTEMPERATURA_H
#define SENSORTEMPERATURA_H

#include "SensorBase.h"
#include <iostream>

// Sensor especializado para lecturas de temperatura (float)
class SensorTemperatura : public SensorBase {
private:
    ListaSensor<float> lecturas;
    
public:
    // Constructor
    SensorTemperatura(const char* nombre);
    
    // Agregar lectura de temperatura
    void agregarLectura(float valor);
    
    // Implementación de métodos virtuales
    void imprimirInfo() const override;
    void procesarLectura() override;
    
    // Destructor
    ~SensorTemperatura() override;
};

#endif // SENSORTEMPERATURA_H