#include "SensorBase.h"
#include <iostream>

int main(){
    SensorTemperatura* sensorTemp = new SensorTemperatura();
    SensorPresion* sensorPres = new SensorPresion();
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
                std::cout<<"creando sensor en Temperatura..."<<std::endl;
                sensorTemp->agregarLectura(25.0f);
                break;
            case 2:
                std::cout<<"creando sensor en Presion..."<<std::endl;
                sensorPres->agregarLectura(1013);
                break;
            case 3:
                std::cout<<"Registrando lectura en Sensor de Temperatura..."<<std::endl;
                sensorTemp->imprimirinfo();
                break;
            case 4:
                std::cout<<"Ejecutando procesamiento polimórfico..."<<std::endl;
                sensorTemp->procesarLectura();
                sensorPres->procesarLectura();
                break;
            case 5:
                std::cout<<"Cerrando sistema y liberando memoria..."<<std::endl;
                delete sensorTemp;
                delete sensorPres;
                break;
            default:
                std::cout<<"Opción inválida. Intente de nuevo."<<std::endl;
                break;
        }
    }

}