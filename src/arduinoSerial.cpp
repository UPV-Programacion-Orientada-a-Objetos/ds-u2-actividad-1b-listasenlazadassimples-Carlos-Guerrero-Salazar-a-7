#include "ArduinoSerial.h"
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <iostream>

// Constructor: abre y configura el puerto serial
SerialReader::SerialReader(const char* puerto) : conectado(false) {
    // Intentar abrir puerto serial
    serial_port = open(puerto, O_RDWR | O_NOCTTY);
    
    if (serial_port < 0) {
        std::cerr << "\n[ERROR] No se pudo abrir puerto " << puerto << std::endl;
        std::cerr << "Razón: " << strerror(errno) << std::endl;
        std::cerr << "\nPosibles soluciones:" << std::endl;
        std::cerr << "1. Verifica que el Arduino esté conectado" << std::endl;
        std::cerr << "2. Ejecuta: sudo usermod -a -G dialout $USER" << std::endl;
        std::cerr << "3. Cierra sesión y vuelve a entrar" << std::endl;
        std::cerr << "4. O ejecuta: sudo chmod 666 " << puerto << std::endl;
        std::cerr << "\nContinuando en modo simulación (sin Arduino)...\n" << std::endl;
        return;
    }
    
    // Configurar puerto serial
    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    
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

// Leer una línea del serial
char* SerialReader::leerLinea() {
    if (!conectado) {
        return nullptr;
    }
    
    char linea[] = "";
    char buf;
    
    while (true) {
        int n = read(serial_port, &buf, 1);
        
        if (n > 0) {
            if (buf == '\n') {
                return linea;
            } else if (buf != '\r') {
                linea += buf;
            }
        } else if (n < 0) {
            std::cerr << "[ERROR] Error leyendo del puerto serial" << std::endl;
            return nullptr;
        }
    }
}

// Procesar y parsear datos del serial
template <typename T>
T SerialReader::procesarDatos(const char* linea) {
    T dato;
    dato.valido = false;
    
    if (linea.empty()) {
        return dato;
    }
    
    // Formato esperado: "FLOAT:25.5" o "INT:1013"
    if (linea.substr(0, 6) == "FLOAT:") {
        try {
            if(typeid(T) == typeid(float)){
                float valor = std::stof(line.substr(6));
                return valor;
            }
        } catch (...) {
            std::cerr << "[ERROR] No se pudo parsear FLOAT: " << linea << std::endl;
        }
    } 
    else if (linea.substr(0, 4) == "INT:") {
        try {
            if(typeid(T) == typeid(int)){
                int valor = std::stoi(line.substr(4));
                return valor;
            }
        } catch (...) {
            std::cerr << "[ERROR] No se pudo parsear INT: " << linea << std::endl;
        }
    }
    else {
        dato.tipo = DatoSerial::DESCONOCIDO;
        std::cerr << "[WARN] Formato desconocido: " << linea << std::endl;
    }
    
    return dato;
}

// Verificar si está conectado
bool SerialReader::estaConectado() const {
    return conectado;
}

// Destructor
SerialReader::~SerialReader() {
    if (conectado && serial_port >= 0) {
        close(serial_port);
        std::cout << "[OK] Puerto serial cerrado" << std::endl;
    }
}