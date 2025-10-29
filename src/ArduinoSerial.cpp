#include "ArduinoSerial.h"

ArduinoSerial::ArduinoSerial(const char* puerto) : conectado(false) {
    serial_port = open(puerto, O_RDWR | O_NOCTTY);
    if (serial_port < 0) {
        std::cerr << "[ERROR] No se pudo abrir el puerto serial: " << puerto << std::endl;
        return;
    }

    struct termios tty;
    std::memset(&tty, 0, sizeof(tty));
        
    if (tcgetattr(serial_port, &tty) != 0) {
        std::cerr << "[ERROR] Error en tcgetattr" << std::endl;
        close(serial_port);
        serial_port = -1;
        return;
    }
    
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);
    
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;
    
    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO;
    tty.c_lflag &= ~ISIG;
    
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
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

char* ArduinoSerial::leerLinea() {
    if (!conectado) {
        return nullptr;
    }
    
    static char linea[256];
    int idx = 0;
    char buf;
    
    while (idx < 255) {
        int n = read(serial_port, &buf, 1);
        
        if (n > 0) {
            if (buf == '\n') {
                linea[idx] = '\0';
                return linea;
            } else if (buf != '\r') {
                linea[idx++] = buf;
            }
        } else if (n < 0 && errno != EAGAIN && errno != EWOULDBLOCK) {
            std::cerr << "[ERROR] Error leyendo del puerto serial" << std::endl;
            return nullptr;
        }
    }
    
    linea[255] = '\0';
    return linea;
}

bool ArduinoSerial::estaConectado() const {
    return conectado;
}

ArduinoSerial::~ArduinoSerial() {
    if (conectado && serial_port >= 0) {
        close(serial_port);
        std::cout << "[OK] Puerto serial cerrado" << std::endl;
    }
}