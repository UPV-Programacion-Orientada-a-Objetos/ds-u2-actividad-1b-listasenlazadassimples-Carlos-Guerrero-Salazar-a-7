#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string>
#include <cstring>
#include <errno.h>

class ArduinoSerial {
private:
    int serial_port;
    
public:
    ArduinoSerial(const char* port) {
        // Abrir puerto serial
        serial_port = open(port, O_RDWR | O_NOCTTY);
        
        if (serial_port < 0) {
            std::cerr << "Error abriendo puerto " << port << std::endl;
            std::cerr << "Razón: " << strerror(errno) << std::endl;
            std::cerr << "\nPosibles soluciones:" << std::endl;
            std::cerr << "1. Verifica que el Arduino esté conectado" << std::endl;
            std::cerr << "2. Ejecuta: sudo usermod -a -G dialout $USER" << std::endl;
            std::cerr << "3. Cierra sesión y vuelve a entrar" << std::endl;
            std::cerr << "4. O ejecuta: sudo chmod 666 " << port << std::endl;
            exit(1);
        }
        
        // Configurar puerto serial
        struct termios tty;
        memset(&tty, 0, sizeof(tty));
        
        if (tcgetattr(serial_port, &tty) != 0) {
            std::cerr << "Error en tcgetattr" << std::endl;
            exit(1);
        }
        
        // Configuración: 9600 baud, 8N1
        cfsetispeed(&tty, B9600);
        cfsetospeed(&tty, B9600);
        
        tty.c_cflag &= ~PARENB; // Sin paridad
        tty.c_cflag &= ~CSTOPB; // 1 bit de stop
        tty.c_cflag &= ~CSIZE;
        tty.c_cflag |= CS8; // 8 bits
        tty.c_cflag &= ~CRTSCTS; // Sin control de flujo hardware
        tty.c_cflag |= CREAD | CLOCAL;
        
        tty.c_lflag &= ~ICANON; // Modo no canónico
        tty.c_lflag &= ~ECHO;
        tty.c_lflag &= ~ISIG;
        
        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Sin control flujo software
        tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);
        
        tty.c_oflag &= ~OPOST;
        tty.c_oflag &= ~ONLCR;
        
        tty.c_cc[VTIME] = 10;
        tty.c_cc[VMIN] = 0;
        
        if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
            std::cerr << "Error en tcsetattr" << std::endl;
            exit(1);
        }
        
        std::cout << "Puerto serial " << port << " abierto correctamente" << std::endl;
    }
    
    std::string readLine() {
        std::string line = "";
        char buf;
        
        while (true) {
            int n = read(serial_port, &buf, 1);
            
            if (n > 0) {
                if (buf == '\n') {
                    return line;
                } else if (buf != '\r') {
                    line += buf;
                }
            }
        }
    }
    
    template <typename T>
    T processData(const std::string& line) {
        if (line.substr(0, 4) == "INT:") {
            int valor = std::stoi(line.substr(4));
            std::cout << "📊 Recibido INT: " << valor << std::endl;
            return valor
            // Aquí puedes procesar el int
            
        } else if (line.substr(0, 6) == "FLOAT:") {
            float valor = std::stof(line.substr(6));
            std::cout << "📈 Recibido FLOAT: " << valor << std::endl;
            return valor;
            // Aquí puedes procesar el float
        }
    }
    
    ~ArduinoSerial() {
        close(serial_port);
    }
};

int main(int argc, char* argv[]) {
    // Detectar puerto automáticamente o usar argumento
    const char* puerto = "/dev/ttyUSB0"; // Puerto por defecto
    
    if (argc > 1) {
        puerto = argv[1];
    }
    
    std::cout << "Intentando conectar a: " << puerto << std::endl;
    ArduinoSerial arduino(puerto);
    
    std::cout << "Esperando datos del Arduino..." << std::endl;
    std::cout << "Presiona Ctrl+C para salir" << std::endl << std::endl;
    
    while (true) {
        std::string data = arduino.readLine();
        if (!data.empty()) {
            arduino.processData(data);
        }
    }
    
    return 0;
}