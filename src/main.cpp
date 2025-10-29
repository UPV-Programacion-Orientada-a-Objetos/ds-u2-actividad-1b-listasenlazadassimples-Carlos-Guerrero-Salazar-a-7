#include "SensorBase.h"
#include "SensorTemperatura.h"
#include "SensorPresion.h"
#include "ArduinoSerial.h"
#include <iostream>
#include <thread>

template <typename T>
T leerDatosArduino(ArduinoSerial* arduino,T tipo_valor);
int main(){
    std::cout << "\n*** Conectando el Arduino ***\n" << std::endl;
    
    // Intentar conectar con Arduino
    const char* puerto = "/dev/ttyUSB0";
    ArduinoSerial* arduino = new ArduinoSerial(puerto);
    SensorTemperatura* sensorTemp = new SensorTemperatura("Sensor de Temperatura");
    SensorPresion* sensorPres = new SensorPresion("Sensor de Presion");
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
                std::cout<<"agarrando el sensor de temperatura..."<<std::endl;
                sensorTemp->agregarLectura(arduino->procesarDatos<float>(arduino->leerLinea()));
                break;
            case 2:
                std::cout<<"agarrando el sensor de presion..."<<std::endl;
                sensorPres->agregarLectura(arduino->procesarDatos<int>(arduino->leerLinea()));
                break;
            case 3:
                std::cout<<"Registrando lectura en Sensor de Temperatura..."<<std::endl;
                sensorTemp->imprimirInfo();
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

template <typename T>
void leerDatosArduino(ArduinoSerial* arduino, T tipo_valor){
    while (true) {
        std::string data = arduino->readLine();
        if (!data.empty()) {
            arduino->processData(data,T valor){
                sensorTemp->agregarLectura(valor);
            }
        }
    }
}