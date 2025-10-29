#include <iostream>
#include <thread>
#include "SensorBase.h"
#include "SensorTemperatura.h"
#include "SensorPresion.h"
#include "ArduinoSerial.h"
#include "ListaGeneral.h"

int main(){
    std::cout << "\n*** Conectando el Arduino ***\n" << std::endl;
    
    // Intentar conectar con Arduino
    const char* puerto = "/dev/ttyUSB0";
    ArduinoSerial* arduino = new ArduinoSerial(puerto);
    ListaGeneral* listaPrincipal = new ListaGeneral();
    SensorBase* sensorTemp = new SensorTemperatura("T-001");
    SensorBase* SensorPres = new SensorPresion("P-105");
    listaPrincipal->agregar(sensorTemp);  // Agrega SensorTemperatura* como SensorBase*
    listaPrincipal->agregar(SensorPres);
    int opcion = 0;
    while(opcion!=5){
        std::cout<<"Simulación de Interacción"<<std::endl;
        std::cout<<"1. Crear Sensor (Tipo Temp - FLOAT)"<<std::endl;
        std::cout<<"2. Crear Sensor (Tipo Presion - INT)"<<std::endl;
        std::cout<<"3. Registrar Lectura"<<std::endl;
        std::cout<<"4. Ejecutar Procesamiento Polimórfico"<<std::endl;
        std::cout<<"5. Cerrar Sistema (Liberar Memoria)"<<std::endl;
        std::cout<<"Seleccione una opción: ";
        std::cin>>opcion;
        switch(opcion){
            case 1:
                {
                std::cout<<"agarrando el sensor de temperatura..."<<std::endl;
                char* linea = arduino->leerLinea();
                if (linea != nullptr) {
                    float valor = arduino->procesarDatos<float>();
                    ((SensorPresion*)SensorPres)->agregarLectura(valor);
                }
                break;
                }
            case 2:{
                std::cout<<"agarrando el sensor de presion..."<<std::endl;
                ((SensorPresion*)SensorPres)->agregarLectura(arduino->procesarDatos<int>());
                break;
            }
            case 3:{
                std::cout<<"Registrando lectura en Sensor de Temperatura..."<<std::endl;
                sensorTemp->imprimirInfo();
                SensorPres->imprimirInfo();
                break;
            }
            case 4:{
                std::cout<<"Ejecutando procesamiento polimórfico..."<<std::endl;
                ((SensorTemperatura*)sensorTemp)->procesarLectura();
                ((SensorPresion*)SensorPres)->procesarLectura();
                break;
            }
            case 5:{
                std::cout<<"Cerrando sistema y liberando memoria..."<<std::endl;
                delete sensorTemp;
                delete SensorPres;
                break;
            }
            default:{
                std::cout<<"Opción inválida. Intente de nuevo."<<std::endl;
                break;
            }
        }
    }

}
