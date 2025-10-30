/**@file Main.cpp
 * * @brief Archivo principal para la simulación de sensores.
 * * @Details Sistema que permita a un arduino obtener datos flotantes e int, estos datos se guardaran en el sistema mediante una lista de sensores de manera general, los datos dentro se guardan en sus respectivos tipos de sensores.
 * * @author Carlos Gael Guerrero Salazar
 * * @date 2025-10-29
 * @version 1.0
 */

#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include "SensorBase.h"
#include "SensorTemperatura.h"
#include "SensorPresion.h"
#include "ArduinoSerial.h"
#include "ListaGeneral.h"

// Variables y Mutex compartidos globalmente (o como parte de una clase principal)
std::atomic<bool> ejecutando(false);
std::mutex sensor_mutex; // Mutex para proteger el acceso a los sensores

// Declaración de sensores y lista (como punteros globales para el ejemplo)
ArduinoSerial* arduino = nullptr;
ListaGeneral* listaPrincipal = nullptr;
SensorBase* sensorTemp = nullptr;
SensorBase* SensorPres = nullptr;


/**
 * @brief Función que se ejecutará en un hilo separado para recopilar datos.
 */
// Archivo main.cpp (recopilacionDatosSerial)
void recopilacionDatosSerial() {
    std::cout << "[Hilo] Hilo de recopilación iniciado." << std::endl;
    while (ejecutando) {
        if (!arduino->estaConectado()) {
            std::cerr << "[Hilo] Error: Puerto serial desconectado." << std::endl;
            ejecutando = false;
            break;
        }
            std::lock_guard<std::mutex> lock(sensor_mutex); 
            float valor_temp = arduino->procesarDatos<float>();
            ((SensorTemperatura*)sensorTemp)->agregarLectura(valor_temp);
            std::cout << "[Hilo-Temp] Lectura FLOAT: " << valor_temp << std::endl;
            int valor_pres = arduino->procesarDatos<int>();
            ((SensorPresion*)SensorPres)->agregarLectura(valor_pres);
            std::cout << "[Hilo-Pres] Lectura INT: " << valor_pres << std::endl;
        
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    std::cout << "[Hilo] Hilo de recopilación finalizado." << std::endl;
}


int main(){
    const char* puerto = "/dev/ttyUSB0";
    arduino = new ArduinoSerial(puerto);
    listaPrincipal = new ListaGeneral();
    sensorTemp = new SensorTemperatura("T-001");
    SensorPres = new SensorPresion("P-105");
    listaPrincipal->agregar(sensorTemp);
    listaPrincipal->agregar(SensorPres);
    
    std::thread hilo_recopilacion; // Objeto para manejar el hilo
    
    int opcion = 0;
    while(opcion!=5){
        std::cout << "\n--- Simulación de Interacción ---" << std::endl;
        std::cout << "1. Iniciar Recopilación de Datos (Hilo)" << std::endl;
        std::cout << "2. Detener Recopilación de Datos (Hilo)" << std::endl;
        std::cout << "3. Imprimir Info de Sensores (Lecturas Registradas)" << std::endl;
        std::cout << "4. Ejecutar Procesamiento Polimórfico" << std::endl;
        std::cout << "5. Cerrar Sistema (Liberar Memoria)" << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        switch(opcion){

            case 1:
                if (!ejecutando && arduino->estaConectado()) {
                    ejecutando = true;
                    hilo_recopilacion = std::thread(recopilacionDatosSerial); 
                    std::cout << "[MAIN] Recopilación iniciada en un hilo separado." << std::endl;
                } else if (!arduino->estaConectado()) {
                    std::cerr << "[MAIN] No se puede iniciar: Arduino no está conectado." << std::endl;
                } else {
                    std::cout << "[MAIN] La recopilación ya está en curso." << std::endl;
                }
                break;
                
            case 2:
                if (ejecutando) {
                    ejecutando = false;
                    if (hilo_recopilacion.joinable()) {
                        hilo_recopilacion.join();
                    }
                    std::cout << "[MAIN] Recopilación detenida y el hilo finalizado." << std::endl;
                } else {
                    std::cout << "[MAIN] La recopilación no está en curso." << std::endl;
                }
                break;
                
            case 3:
                {
                    std::lock_guard<std::mutex> lock(sensor_mutex);
                    std::cout << "--- Registros Actuales ---" << std::endl;
                    sensorTemp->imprimirInfo();
                    SensorPres->imprimirInfo();
                }
                break;
            
            case 4:
                {
                    std::lock_guard<std::mutex> lock(sensor_mutex);
                    std::cout << "Ejecutando procesamiento polimórfico..." << std::endl;
                    ((SensorTemperatura*)sensorTemp)->procesarLectura();
                    ((SensorPresion*)SensorPres)->procesarLectura();
                }
                break;
                
            case 5:
                std::cout << "Cerrando sistema y liberando memoria..." << std::endl;
                if (ejecutando) {
                    ejecutando = false;
                    if (hilo_recopilacion.joinable()) {
                        hilo_recopilacion.join();
                    }
                }
                delete listaPrincipal;
                delete sensorTemp;
                delete SensorPres;
                delete arduino;
                break;
                
            default:
                std::cout << "Opción inválida. Intente de nuevo." << std::endl;
                break;
        }
    }

    return 0;
}