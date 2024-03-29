#include "motor.h"

Encoder myEncoders(27, 14, 23, 19, 0.314, 360);

void setup() {
    Serial.begin(9600); 
    myEncoders.init(); 
}

void loop() {
    // Calcula y actualiza las velocidades basadas en los contadores y el tiempo transcurrido.
    myEncoders.calculateSpeed();

    // Obtiene las velocidades calculadas.
    float speedLeft = myEncoders.getSpeedLeft();
    float speedRight = myEncoders.getSpeedRight();

    // Imprime las velocidades por comunicación serial.
    Serial.print("Velocidad Izquierda: ");
    Serial.print(speedLeft);
    Serial.print(" m/s, Velocidad Derecha: ");
    Serial.print(speedRight);
    Serial.println(" m/s");

    //delay(1000); // Espera un segundo antes de la próxima actualización.
}
