#ifndef SERIALREADER_H
#define SERIALREADER_H

// Clase para manejar comunicación serial con Arduino
class ArduinoSerial {
private:
    int serial_port;
    bool conectado;
public:

    // Constructor: intenta abrir el puerto serial
    ArduinoSerial(const char* puerto = "/dev/ttyUSB0"){};
    
    // Leer una línea del serial
    char* leerLinea();
    
    // Procesar y parsear datos del serial
    template <typename T>
    T procesarDatos();
    
    // Verificar si está conectado
    bool estaConectado() const;
    
    // Destructor
    ~ArduinoSerial();
};

#endif // SERIALREADER_H