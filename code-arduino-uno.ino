// Librerías
#include <SPI.h>
#include <MFRC522.h>
//#include <Keyboard.h>
// Pines SPI Derecho
#define RST_PIN 9
#define SS_PIN 10
//Pines SPI Izquierdo
#define RST_PIN_R 3
#define SS_PIN_R 4

// Instancia a la clase MFRC522 para el lado derecho
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Instancia a la clase MFRC522 para el lado izquierdo
MFRC522 mfrc522_R(SS_PIN_R, RST_PIN_R);

// Clave de cifrado actuales
MFRC522::MIFARE_Key keyA = { keyByte: { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } };
MFRC522::MIFARE_Key keyB = { keyByte: { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF } };

//Creación de variable
String valorUidTextoPlano;

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;                  // Bucle que no permite continuar hasta que no se ha abierto el monitor serie
  SPI.begin();         // Iniciar bus SPI
  mfrc522.PCD_Init();  // Iniciar lector RFID RC522 derecho
  mfrc522_R.PCD_Init();  // Iniciar lector RFID RC522 izquerdo
}


void loop() {
  // Si no hay una tarjeta cerca no sigue el programa
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522_R.PICC_IsNewCardPresent()) {
    return;
  }

  // Si hay una tarjeta cerca, que la eleccione
  // En caso contrario que no continúe
  if (!mfrc522.PICC_ReadCardSerial() || !mfrc522_R.PICC_ReadCardSerial()) {
    return;
  }

  // Mostrar información de la tarjeta por el monitor serie
  //  Serial.print(F("UID de la tarjeta:"));
  mostrarByteArray(mfrc522.uid.uidByte, mfrc522.uid.size);  // Motrar el UID
  mostrarByteArray(mfrc522_R.uid.uidByte, mfrc522_R.uid.size);  // Motrar el UID
  // Detener el lector
  mfrc522.PICC_HaltA();
  mfrc522_R.PICC_HaltA();
}

void mostrarByteArray(byte* buffer, byte bufferSize) {
  if (buffer == 0 && bufferSize == 0) return;
  String arrayPartesUid;
  for (byte i = 0; i < bufferSize; i++) {
    arrayPartesUid.concat(buffer[i]);
  }
  //Keyboard.println(arrayPartesUid);
  Serial.println(arrayPartesUid);
//  delay(1000);
}
