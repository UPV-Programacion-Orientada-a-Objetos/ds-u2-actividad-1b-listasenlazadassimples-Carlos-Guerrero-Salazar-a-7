/**
 * @file sensor_simulator.ino
 * @brief Simulador de sensores IoT para comunicación serial desde un arduino externo
 * @details Envía datos simulados de temperatura (float) y presión (int)
 *          por el puerto serial en formato: FLOAT:valor o INT:valor
 */
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  int tipo = random(0, 2); // 0 o 1
  
  if (tipo == 0) {
    // Enviar un INT
    int valor = random(0, 100);
    Serial.println(valor);
  } else {
    // Enviar un FLOAT
    float valor = random(0, 10000) / 100.0; // Float con 2 decimales
    Serial.println(valor, 2); // 2 decimales
  }
  delay(1000);
}