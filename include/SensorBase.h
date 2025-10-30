#ifndef SENSORBASE_H
#define SENSORBASE_H

#include <cstring>
#include "ListaSensor.h"

/**
 * @file SensorBase.h
 * @brief Definición de la clase base abstracta para todos los sensores del sistema.
 */

/**
 * @class SensorBase
 * @brief Clase abstracta base que define la interfaz común para todos los tipos de sensores.
 * * Esta clase implementa un mecanismo para registrar automáticamente cada instancia de 
 * sensor creado en una lista estática, facilitando la gestión polimórfica.
 */
class SensorBase {
protected:
    char nombre[50]; ///< Nombre descriptivo del sensor.
    
public:
    /**
     * @brief Lista estática para registrar todos los sensores creados en el sistema.
     * para operaciones polimórficas (como el procesamiento masivo).
     * @details Utiliza `ListaSensor<SensorBase*>` para almacenar punteros de clase base.
     */
    static ListaSensor<SensorBase*> sensoresRegistrados;
    
    /**
     * @brief Constructor de la clase base.
     * * Inicializa el nombre del sensor y lo registra automáticamente en la lista estática `sensoresRegistrados`.
     * @param nom Cadena de caracteres con el nombre del sensor (máximo 49 caracteres).
     */
    SensorBase(const char* nom) {
        strncpy(nombre, nom, 49);
        nombre[49] = '\0';
        sensoresRegistrados.agregar(this);
    }
    
    /**
     * @brief Método virtual puro para imprimir la información específica del sensor.
     * * Debe ser implementado por todas las clases derivadas.
     */
    virtual void imprimirInfo() const = 0;
    
    /**
     * @brief Método virtual puro para iniciar el proceso de lectura y manejo de datos del sensor.
     * * Debe ser implementado por todas las clases derivadas para definir su lógica de procesamiento.
     */
    virtual void procesarLectura() = 0;
    
    /**
     * @brief Obtiene el nombre del sensor.
     * @return Puntero constante a la cadena de caracteres que contiene el nombre del sensor.
     */
    const char* obtenerNombre() const {
        return nombre;
    }
    
    /**
     * @brief Destructor virtual.
     * * Es importante que sea virtual para asegurar que el destructor correcto de la clase derivada 
     * sea llamado cuando se elimina un objeto `SensorBase` a través de un puntero base (polimorfismo).
     */
    virtual ~SensorBase() {}
};

#endif // SENSORBASE_H