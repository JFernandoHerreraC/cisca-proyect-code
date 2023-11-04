#include <ESP8266WiFi.h>

const char* ssid = "";  // Rellena con el nombre de tu red WiFi
const char* password = "";  // Rellena con la contraseña de tu red WiFi
const char* host = "";    //Rellena con la ip de host

const int lonbuffer = 20;
char buffer[lonbuffer];

String numeroTarjeta = "";

//definicion de pines
#define pinMotor1 D5  // 28BYJ48 - In1
#define pinMotor2 D6  // 28BYJ48 - In2
#define pinMotor3 D7  // 28BYJ48 - In3
#define pinMotor4 D8  // 28BYJ48 - In4

//definicion variables
int velocidadMotor = 1000;  // variable para determinar la velocidad
// 800 maxima - minima 1000 o mas
int contadorPasos = 0;      // contador para los pasos
int pasosPorVuelta = 1019;  // pasos para una vuelta completa


//secuencia media fase usar velocidadMotor = 1000
const int cantidadPasos = 8;
const int tablaPasos[8] = { B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001 };

void setup() {
  Serial.begin(9600);
  delay(10);

  // Conectamos a la red WiFi
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Configuramos el ESP8266 como cliente WiFi. Si no lo hacemos 
  se configurará como cliente y punto de acceso al mismo tiempo */
  WiFi.mode(WIFI_STA);  // Modo cliente WiFi
  WiFi.begin(ssid, password);

  // Esperamos a que estemos conectados a la red WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());  // Mostramos la IP
                                   //declarar pines como salida
  pinMode(pinMotor1, OUTPUT);
  pinMode(pinMotor2, OUTPUT);
  pinMode(pinMotor3, OUTPUT);
  pinMode(pinMotor4, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    //Se le el código de la tarjeta
    numeroTarjeta = Serial.readString();
    // Creamos el cliente
    WiFiClient client;
    const int httpPort = 3000;  // Puerto HTTPS
    if (!client.connect(host, httpPort)) {
      // ¿hay algún error al conectar?
      Serial.println("Ha fallado la conexión");
      return;
    }
    // Enviamos la petición
    client.print(String("GET ") + "/sra12?codigo=" + numeroTarjeta + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Superado el tiempo de espera !");
        client.stop();
        return;
      }
    }

    // Leemos la respuesta y la enviamos al monitor serie
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.println(line);
    }
    // put your main code here, to run repeatedly:
    for (int i = 0; i < pasosPorVuelta; i++) {
      sentidoHorario();
      delayMicroseconds(velocidadMotor);
    }
    delay(2000);
    for (int i = 0; i < pasosPorVuelta; i++) {
      sentidoAntihorario();
      delayMicroseconds(velocidadMotor);
    }
  }

  delay(1000);
}
void sentidoHorario()  // en dirección de las agujas del reloj
{
  contadorPasos++;
  if (contadorPasos >= cantidadPasos) contadorPasos = 0;
  escribirSalidas(contadorPasos);
}

void sentidoAntihorario()  // en dirección contraria a las agujas del reloj
{
  contadorPasos--;
  if (contadorPasos < 0) contadorPasos = cantidadPasos - 1;
  escribirSalidas(contadorPasos);
}

void escribirSalidas(int paso) {
  digitalWrite(pinMotor1, bitRead(tablaPasos[paso], 0));
  digitalWrite(pinMotor2, bitRead(tablaPasos[paso], 1));
  digitalWrite(pinMotor3, bitRead(tablaPasos[paso], 2));
  digitalWrite(pinMotor4, bitRead(tablaPasos[paso], 3));
}