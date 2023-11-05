# Código de las placas del proyecto.
El código usado en las placas de desarrollo abierto Arduino para el desarrollo del proyecto, el cual proporciona las funcionalidades principales del proyecto, sin embargo, no es todo, ya que necesita para que funcione correctamente un Back-end.
# Pre-requerimientos
Para que funcione necesitan lo siguiente:
* Arduino Uno R3
* Nodemcu ESP8266
* Motor a pasos 28BYJ-48 con driver de potencia basado en el chip ULN2003A.
* Cables dupont Hembras - Machos.
Una vez teniendo todo los materiales debemos conectarlos a su discreción o siguiendo el manual de operaciones.
# Requerimientos.
Rellenar los siguientes campos en el archivo [***code-esp8266.ino***] (https://github.com/JFernandoHerreraC/cisca-proyect-code/blob/main/code-esp8266.ino) para que pueda funcionar.
```
const char* ssid = "";  // Rellena con el nombre de tu red WiFi
const char* password = "";  // Rellena con la contraseña de tu red WiFi
const char* host = "";    //Rellena con la ip de host
```
