#ifndef SERIALREADER_H
#define SERIALREADER_H

#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <iostream>
#include <cstring>
#include <typeinfo>

class ArduinoSerial {
private:
    int serial_port;
    bool conectado;
    
    bool tieneDecimal(const char* str) {
        if (*str == '-' || *str == '+') {
            str++;
        }
        while (*str != '\0') {
            if (*str == '.' || *str == ',') {
                return true;
            }
            str++;
        }
        return false;
    }

public:
    ArduinoSerial(const char* puerto = "/dev/ttyUSB0");
    char* leerLinea();
    
    // Template implementado en el header
    template <typename T>
    T procesarDatos() {
        while(true) {
            char* linea = leerLinea();
            
            if (linea == nullptr) {
                continue;
            }
            
            // Saltar espacios iniciales
            while (*linea == ' ' || *linea == '\t' || *linea == '\r' || *linea == '\n') {
                linea++;
            }
            
            if (*linea == '\0') {
                continue;
            }
            
            bool flotantes = tieneDecimal(linea);
            
            if (typeid(T) == typeid(int)) {
                if (flotantes) {
                    continue; // Saltar valores con decimal si esperamos int
                }
                int valor = 0;
                if (sscanf(linea, "%d", &valor) == 1) {
                    return static_cast<T>(valor);
                }
                std::cerr << "[WARN] No es int válido: " << linea << std::endl;
            }
            else if (typeid(T) == typeid(float)) {
                float valor = 0.0f;
                if (sscanf(linea, "%f", &valor) == 1) { 
                    return static_cast<T>(valor);
                }
                std::cerr << "[WARN] No es float válido: " << linea << std::endl;
            }
            else {
                std::cerr << "[ERROR] Tipo no soportado" << std::endl;
                return T();
            }
        }
    }
    
    bool estaConectado() const;
    ~ArduinoSerial();
};

#endif // SERIALREADER_H