#ifndef SENSORPRESION_H
#define SENSORPRESION_H

#include "SensorBase.h"
#include "ListaSensor.h" // Asegurarse de que ListaSensor.h esté incluido si no está ya en SensorBase.h
#include <iostream>

/**
 * @file SensorPresion.h
 * @brief Definición de la clase SensorPresion, que gestiona lecturas de presión como enteros.
 */

/**
 * @class SensorPresion
 * @brief Sensor especializado para la adquisición y gestión de lecturas de presión (tipo int).
 * * Hereda de SensorBase e implementa los métodos virtuales puros.
 */
class SensorPresion : public SensorBase {
private:
    ListaSensor<int> lecturas; ///< Lista enlazada para almacenar las lecturas históricas de presión (valores enteros).
    
public:
    /**
     * @brief Constructor de SensorPresion.
     * * Inicializa el sensor con un nombre y se auto-registra en `SensorBase::sensoresRegistrados`.
     * @param nombre Cadena de caracteres con el nombre del sensor (p. ej., "Sensor Presión 1").
     */
    SensorPresion(const char* nombre);
    
    /**
     * @brief Agrega una nueva lectura de presión a la lista de registros.
     * @param valor El valor de la presión medida (entero).
     */
    void agregarLectura(int valor);
    
    /**
     * @brief Muestra información detallada del sensor, incluyendo su tipo y las lecturas almacenadas.
     * @details Implementación del método virtual puro de SensorBase.
     */
    void imprimirInfo() const override;
    
    /**
     * @brief Procesa las lecturas del sensor (simulado).
     * @details Implementación del método virtual puro de SensorBase. En un entorno real, 
     * esta función obtendría un nuevo valor o realizaría cálculos.
     */
    void procesarLectura() override;
    
    /**
     * @brief Destructor.
     * * Es virtual para asegurar la destrucción correcta de las clases base y derivadas.
     */
    ~SensorPresion() override;
};

#endif // SENSORPRESION_H