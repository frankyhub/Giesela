/*************************************************************************************************
                                      PROGRAMMINFO
**************************************************************************************************
  Funktion: Giesela; ESP32 WEB Server fuer eine Bewaessungsanlage mit WLAN-Manager
**************************************************************************************************
  Version: 13.03.2023
**************************************************************************************************
  Board: ESP32vn IoT UNO V1.0.4
**************************************************************************************************
  C++ Arduino IDE V1.8.13
**************************************************************************************************
  Einstellungen:
  https://dl.espressif.com/dl/package_esp32_index.json
  http://dan.drown.org/stm32duino/package_STM32duino_index.json
  https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json
**************************************************************************************************
  Librarys
  - WiFi.h V0.16.1
**************************************************************************************************/


#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "SPIFFS.h"
#include <Arduino_JSON.h>


/*
// Set LED GPIO
const int ledPin = 2;
// Stores LED state
String ledState;
*/


AsyncWebServer server(80);
AsyncEventSource events("/events");

JSONVar readings;

unsigned long lastTime = 0;
unsigned long timerDelay = 10000;


int humidity10 = 0;
int humidity20 = 0;
int humidity30 = 0;

int pumpe1 = 16;
int pumpe2 = 17;
int pumpe3 = 25;

//Überschwemmung!
int buzzer = 13;

//Wasserstand im Vorratstank
int sensorLED = 19;
int wassersensor = 39;
int wasserstand;
int ueberschwemmung;


String getSensorReadings() {

  readings["STATE"] = String(digitalRead(buzzer));
//  readings["humidity1"] = String(map(analogRead(34), 4096, 0, 0, 100)-40); //Feuchtesensor
  readings["humidity1"] = String(map(analogRead(34), 4096, 0, 100, 0));  //Poti
  readings["humidity2"] = String(map(analogRead(35), 4096, 0, 100, 0));
  readings["humidity3"] = String(map(analogRead(36), 4096, 0, 100, 0));


  int humiditya = map(analogRead(34), 4096, 0, 100, 0); //Poti
  Serial.print("Bodenfeuchte 1: ");
  Serial.println(humiditya);


  int humidityb = map(analogRead(35), 4096, 0, 100, 0);
  Serial.print("Bodenfeuchte 2: ");
  Serial.println(humidityb);


  int humidityc = map(analogRead(36), 4096, 0, 100, 0);
  Serial.print("Bodenfeuchte 3: ");
  Serial.println(humidityc);


  if (humiditya < 10) {
    digitalWrite(pumpe1, HIGH);
    Serial.println("Pumpe 1 AN");
  } else {
    digitalWrite(pumpe1, LOW);
    Serial.println("Pumpe 1 AUS");
  }

  if (humidityb < 15) {
    digitalWrite(pumpe2, HIGH);
    Serial.println("Pumpe 2 AN");
  } else {
    digitalWrite(pumpe2, LOW);
    Serial.println("Pumpe 2 AUS");
  }

  if (humidityc < 20) {
    digitalWrite(pumpe3, HIGH);
    Serial.println("Pumpe 3 AN");
  } else {
    digitalWrite(pumpe3, LOW);
    Serial.println("Pumpe 2 AUS");
  }

  if ((humiditya > 80)|| (humidityb > 80) || (humidityc > 80)) {
    digitalWrite(buzzer, HIGH);
    Serial.println("ALARM Bodenfeuchte > 80%");
  } else {
    digitalWrite(buzzer, LOW);
    Serial.println("ALARM AUS Bodenfeuchte < 80%");
  }


  wasserstand = digitalRead(wassersensor);
  
    if (wasserstand == HIGH) {
    digitalWrite(sensorLED, HIGH);
    Serial.println("Wasser nachfüllen!");
  } else {
    digitalWrite(sensorLED, LOW);
    Serial.println("Wasserstand OK");
  }

    ueberschwemmung = digitalRead(buzzer);
    if (ueberschwemmung == HIGH) {
   // digitalWrite(sensorLED, HIGH);
    Serial.println("Überschwemmung!");
  } else {
 //   digitalWrite(sensorLED, LOW);
    Serial.println("Keine Überschwemmung");
  }
  




  

  
  String jsonString = JSON.stringify(readings);
  return jsonString;

  

}





//SPIFFS
void initSPIFFS() {
  if (!SPIFFS.begin()) {
    Serial.println("Beim Mounten von SPIFFS ist ein Fehler aufgetreten");
  }
  Serial.println("SPIFFS erfolgreich geladen");
}

//WiFi
void initWiFi() {
        //init WiFi
  Serial.println("Connecting to WiFi");
  while (!makeWLAN()) {
    Serial.println("Cannot connect :(");
    delay(1000);
  }
}






void setup() {

  pinMode(pumpe1, OUTPUT);
  pinMode(pumpe2, OUTPUT);
  pinMode(pumpe3, OUTPUT);

  pinMode(buzzer, OUTPUT);

   pinMode(sensorLED, OUTPUT);
  pinMode(wassersensor, INPUT_PULLUP); 

  Serial.begin(115200);





  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }


  initWiFi();
  initSPIFFS();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", "text/html");

  });
;

  server.serveStatic("/", SPIFFS, "/");

  server.on("/readings", HTTP_GET, [](AsyncWebServerRequest * request) {
    String json = getSensorReadings();
    request->send(200, "application/json", json);
    json = String();
  });

  events.onConnect([](AsyncEventSourceClient * client) {
    if (client->lastId()) {
      Serial.printf("Client wieder verbunden! Die letzte Nachrichten-ID, die es erhalten hat, ist: %u\n", client->lastId());
    }
    //   client->send("Hallo!", NULL, millis(), 10000);
    client->send("Hallo!", NULL, millis(), 3000);
  });
  server.addHandler(&events);



  // Start server
  server.begin();
}

void loop() {

  if ((millis() - lastTime) > timerDelay) {
    // Sende Sensor Daten alle 10 Sek.
    events.send("ping", NULL, millis());
    events.send(getSensorReadings().c_str(), "new_readings" , millis());
    lastTime = millis();
  }
}
