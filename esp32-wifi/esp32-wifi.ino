#include <WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "Comunidad_UNMED";
const char* password = "wifi_med_213";

WiFiClient client; // Crea un objeto de la clase WifiClient

unsigned long myChannelNumber = 1913616;
const char * myWriteAPIKey = "RKRHVWS529NH288X";

void setup()
{
  Serial.begin(9600); // Abre el puerto serial a 9600 bps
  WiFi.mode(WIFI_STA); // Configura el ESP32 como estaciónWiFi
  ThingSpeak.begin(client); // Inicializa ThingSpeak
  pinMode(34, INPUT);
}

void loop()
{
//Condicional que verifica la conexión ESP32 y la red
  if(WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Intentando conectar a la red");
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, password);
      delay(5000);
    }
    Serial.println("\nConectado.");
  }
  int sensor;
  sensor=digitalRead(34); 
  //Conecta el sensor al pin #
  Serial.println(sensor,DEC);
  
  // Esta es la instrucción que envia el valor leído del sensor a ThingSpeak
  /*ThingSpeak.writeField(Numero del canal, Numero del
campo (en este caso Field 1), Variable que se enviará, Llave
de identificación (API key))*/
  int x = ThingSpeak.writeField(myChannelNumber, 1, sensor, myWriteAPIKey);
  
  // Si la conexión es exitosa, regresa el codigo HTTP 200
  if(x == 200){
    Serial.println("Canal actualizado exitosamente.");
  }
  else{
    Serial.println("Error al actualizar el canal. Código de error HTTP " + String(x));
  }
  delay(20000);
}
