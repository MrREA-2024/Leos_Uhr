/*
 * PROJEKT: ESP32 NTP-Uhr (D1 R32 Board)
 * AUTOR: [Dein Name]
 * * --- HARDWARE SETUP ---
 * Board: AZ-Delivery ESP32 D1 R32 (Uno Layout)
 * USB-Treiber: CH340 Version 3.4 (WICHTIG! Neuere Versionen verursachen Fehler 13, Windows Installer liegt Repo bei)
 * Stromversorgung: Externe 9V DC empfohlen beim Flashen
 * * --- ARDUINO IDE EINSTELLUNGEN ---
 * Board: "ESP32 Dev Module" auswählen
 * Flash Mode: DIO (NICHT QIO -> behebt csum err)
 * Flash Frequency: 40MHz
 * Upload Speed: 115200
 * * --- PIN BELEGUNG ---
 * LED: GPIO 2 (Interne LED oder externe LED an IO2 gegen GND)
 */

#include <WiFi.h>
#include "time.h"

// Deine WLAN Zugangsdaten
const char* ssid     = "REA_WLAN";
const char* password = "d3m0nr3a";

// NTP Server Einstellungen
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;      // Deutschland ist UTC +1 (3600 Sek)
const int   daylightOffset_sec = 3600; // Sommerzeit (+1h = 3600 Sek)

// Wir nutzen GPIO 2 (oft die interne LED)
const int ledPin = 2;

void printLocalTime() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Fehler beim Abrufen der Zeit");
    return;
  }
  // Formatierte Ausgabe: HH:MM:SS
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void setup() {
  Serial.begin(115200);

  // LED Pin vorbereiten
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Erstmal aus

  // WLAN Verbindung aufbauen
  Serial.printf("Verbinde mit %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" VERBUNDEN!");

  // Zeit-Konfiguration initialisieren
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Zeit-Fehler");
    delay(1000);
    return;
  }

  // Serielle Ausgabe
  Serial.printf("Aktuelle Zeit: %02d:%02d:%02d\n", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);

  // LOGIK FÜR DIE VOLLE STUNDE
  // Wenn Minute 0 und Sekunde 0 erreicht sind:
  if (timeinfo.tm_sec == 0) {
    Serial.println("DING DONG! Volle Stunde!");
    digitalWrite(ledPin, HIGH); // LED AN
    delay(5000);                // 5 Sekunden leuchten lassen
    digitalWrite(ledPin, LOW);  // LED AUS
  }

  delay(1000);
  printLocalTime(); // Zeit jede Sekunde ausgeben
}