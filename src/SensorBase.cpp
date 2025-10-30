/**
 * @file SensorBase.cpp
 * @brief Implementación de la clase base para sensores.
 * @details Esta clase proporciona la funcionalidad básica para todos los tipos de sensores, incluyendo el registro y la gestión de lecturas,cuando se crea un sensor el sensor se guarda aqui.
 * @author Carlos Gael Guerrero Salazar
 * @date 2025-10-29
 * @version 1.0
 */

#include "SensorBase.h"
ListaSensor<SensorBase*> SensorBase::sensoresRegistrados;