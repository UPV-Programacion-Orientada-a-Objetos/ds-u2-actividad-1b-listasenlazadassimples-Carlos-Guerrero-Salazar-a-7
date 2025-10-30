#ifndef SENSORTEMPERATURA_H
#define SENSORTEMPERATURA_H

#include "SensorBase.h"
#include "ListaSensor.h" // Asegurarse de incluir la clase ListaSensor
#include <iostream>

/**
 * @file SensorTemperatura.h
 * @brief Definición de la clase SensorTemperatura, que gestiona lecturas de temperatura como flotantes.
 */

/**
 * @class SensorTemperatura
 * @brief Sensor especializado para la adquisición y gestión de lecturas de temperatura (tipo float).
 * * Hereda de SensorBase e implementa los métodos virtuales puros para el polimorfismo.
 */
class SensorTemperatura : public SensorBase {
private:
    ListaSensor<float> lecturas; ///< Lista enlazada para almacenar las lecturas históricas de temperatura (valores flotantes).
    
public:
    /**
     * @brief Constructor de SensorTemperatura.
     * * Inicializa el sensor con un nombre y se auto-registra en `SensorBase::sensoresRegistrados`.
     * @param nombre Cadena de caracteres con el nombre del sensor (p. ej., "Termómetro Exterior").
     */
    SensorTemperatura(const char* nombre);
    
    /**
     * @brief Agrega una nueva lectura de temperatura a la lista de registros.
     * @param valor El valor de la temperatura medida (flotante).
     */
    void agregarLectura(float valor);
    
    /**
     * @brief Muestra información detallada del sensor, incluyendo su tipo y las lecturas almacenadas.
     * @details Implementación del método virtual puro `imprimirInfo()` de SensorBase.
     */
    void imprimirInfo() const override;
    
    /**
     * @brief Procesa las lecturas del sensor (simulado).
     * @details Implementación del método virtual puro `procesarLectura()` de SensorBase. En un entorno real, 
     * esta función se usaría para obtener el último valor del dispositivo o ejecutar lógica de muestreo.
     */
    void procesarLectura() override;
    
    /**
     * @brief Destructor.
     * * Es virtual para asegurar la destrucción correcta de las clases base y derivadas.
     */
    ~SensorTemperatura() override;
};

#endif