#include "ArduinoSerial.h"
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <iostream>
#include <cstring>

// Constructor: abre y configura el puerto serial
ArduinoSerial::ArduinoSerial(const char* puerto) : conectado(false) {
    // Intentar abrir puerto serial
    serial_port = open(puerto, O_RDWR | O_NOCTTY);
    if (serial_port < 0) {
        std::cerr << "[ERROR] No se pudo abrir el puerto serial: " << puerto << std::endl;
        return;
    }

    // Configurar puerto serial
    struct termios tty;
    std::memset(&tty, 0, sizeof(tty));
        
    if (tcgetattr(serial_port, &tty) != 0) {
        if (tcgetattr(serial_port, &tty) != 0) {
            std::cerr << "[ERROR] Error en tcgetattr" << std::endl;
            close(serial_port);
            serial_port = -1;
            return;
        }
        
        // Configuración: 9600 baud, 8N1
        cfsetispeed(&tty, B9600);
        cfsetospeed(&tty, B9600);
        
        tty.c_cflag &= ~PARENB;        // Sin paridad
        tty.c_cflag &= ~CSTOPB;        // 1 bit de stop
        tty.c_cflag &= ~CSIZE;
        tty.c_cflag |= CS8;            // 8 bits
        tty.c_cflag &= ~CRTSCTS;       // Sin control de flujo hardware
        tty.c_cflag |= CREAD | CLOCAL;
        
        tty.c_lflag &= ~ICANON;        // Modo no canónico
        tty.c_lflag &= ~ECHO;
        tty.c_lflag &= ~ISIG;
        
        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Sin control flujo software
        tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);
        
        tty.c_oflag &= ~OPOST;
        tty.c_oflag &= ~ONLCR;
        
        tty.c_cc[VTIME] = 10;
        tty.c_cc[VMIN] = 0;
        
        if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
            std::cerr << "[ERROR] Error en tcsetattr" << std::endl;
            close(serial_port);
            serial_port = -1;
            return;
        }
        
        conectado = true;
        std::cout << "[OK] Puerto serial " << puerto << " abierto correctamente" << std::endl;
    }
}

    // Leer una línea del serial
    char* ArduinoSerial::leerLinea() {
        if (!conectado) {
            return nullptr;
        }
        
        static char linea[256];  // Buffer estático (se mantiene entre llamadas)
        int idx = 0;
        char buf;
        
        while (idx < 255) {  // Dejar espacio para '\0'
            int n = read(serial_port, &buf, 1);
            
            if (n > 0) {
                if (buf == '\n') {
                    linea[idx] = '\0';  // Terminar el string
                    return linea;
                } else if (buf != '\r') {
                    linea[idx++] = buf;  // Agregar carácter al buffer
                }
            } else if (n < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
                std::cerr << "[ERROR] Error leyendo del puerto serial" << std::endl;
                return nullptr;
            }
            // Si n == 0, timeout, continuar esperando
        }
        
        // Si llegamos aquí, el buffer está lleno
        linea[255] = '\0';
        return linea;
    }

    // Procesar y parsear datos del serial
    template <typename T>
    T ArduinoSerial::procesarDatos() {
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
                continue;  // Línea vacía, reintentar
            }

            if (typeid(T) == typeid(int)) {
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

        // Verificar si está conectado
    bool ArduinoSerial::estaConectado() const {
        return conectado;
    }

    // Destructor
    ArduinoSerial::~ArduinoSerial() {
        if (conectado && serial_port >= 0) {
            close(serial_port);
            std::cout << "[OK] Puerto serial cerrado" << std::endl;
        }
    }