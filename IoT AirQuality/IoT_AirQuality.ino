/*
 Basic ESP8266 MQTT example

 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.

 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.

 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"

*/
//Libreria para conexión WiFi
#include <ESP8266WiFi.h>
//Libreria para la conexión MQTT
#include <PubSubClient.h>

// Update these with values suitable for your network.
//Credenciales WiFi
//Nombre de la Red WiFi
//const char* ssid = "Invitados_UDistrital";
const char* ssid = "Familia Alvarado";
//Contraseña de la Red WiFi
//const char* password = "1nv1tad05";
const char* password = "19190017";

//MQTT Broker
const char* mqtt_server = "broker.mqtt-dashboard.com";
const char* mqtt_Port = 1883;

//Objeto de la Clase WiFiClient para establecer una conexión
WiFiClient espClient;
//Objeto de la Clase PubSubClient para conexión MQTT
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

//*************************************************************************
//Configuración de la Conexión WiFi
//*************************************************************************
void setup_wifi() {

  delay(10);
  //Inicialización de la conexión WiFi
  Serial.println();
  Serial.print("Intentando conectarse a la red WiFi ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print("Conectando a la red WiFi...");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("!Conectado a la red WiFi¡");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

//*************************************************************************
//Manejo de Mensajes Suscritos Recibidos 
//*************************************************************************
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje Recibido en el topic:");
  Serial.print(topic);
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Intentando establecer una conexión con el Broker MQTT...");
    //Crea un ID de Cliente Aleatorio
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    //Intenta Conectarse al Broker
    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado al Broker");
      //Una vez conectado, publica un mensaje...
      client.publish("AirQuality/CO", "CO: 200ppm");
      //Suscribirse a un Topic
      client.subscribe("AirQuality/CO");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("Intentando conectar en segundos");
      //Espera 5 segundos antes de vovler a intentar
      delay(5000);
    }
  }
}


void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  //Conexión al Broker MQTT
  client.setServer(mqtt_server, mqtt_Port);
  //Función de manejo para la recepción de mensajes MQTT
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  //El dispositivo IoT Publica mensajes cada 2 segundos
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 50, "CO: #%ld ppm", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("AirQuality/CO", msg);
  }
}
