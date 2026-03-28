# Leos_Uhr 🕒 ESP32 NTP-Wandtimer

Ein ESP32-basiertes Uhrenprojekt, das die Zeit via WLAN über NTP (Network Time Protocol) bezieht und optisch über LEDs darstellt. Optimiert für das **AZ-Delivery D1 R32** Board (Arduino Uno Layout).

## 🛠 Hardware & Setup-Wichtigkeiten

Dieses Projekt nutzt das ESP32 D1 R32 Board. Aufgrund der speziellen Hardware-Revision sind folgende Einstellungen **zwingend** erforderlich, um Fehler wie `PermissionError(13)` oder `csum err` zu vermeiden:

### 1. USB-Treiber (Kritisch!)
* **Version:** Nutze den **CH340 Treiber Version 3.4**.
* **Warum?** Neuere Versionen (3.5+) verursachen unter Windows häufig den "Permission Error 13", da sie den Port nicht korrekt freigeben oder das Timing beim Auto-Reset nicht passt.

### 2. Arduino IDE Einstellungen
Beim Flashen müssen folgende Parameter im Menü `Werkzeuge` gewählt sein:
* **Board:** `DOIT ESP32 DEVKIT V1` (oder `WEMOS D1 MINI ESP32`)
* **Flash Mode:** `DIO` (Wichtig: `QIO` führt zu Checksummen-Fehlern beim Booten!)
* **Flash Frequency:** `40MHz`
* **Upload Speed:** `115200`

### 3. Manueller Boot-Modus
Da das Board keine dedizierte Boot-Taste hat, kann es vorkommen, dass der automatische Upload fehlschlägt. 
* **Lösung:** Pin `IO0` mit `GND` kurzschließen, dann die `RST`-Taste drücken. Das Board wechselt nun in den Programmiermodus.

## 💻 Software-Struktur
Aus Sicherheitsgründen sind die WLAN-Zugangsdaten nicht im Hauptcode enthalten:
1. Erstelle eine Datei `arduino_secrets.h` im Hauptverzeichnis.
2. Definiere dort `SECRET_SSID` und `SECRET_PASS`.
3. Die Datei wird durch die `.gitignore` automatisch vom Upload ausgeschlossen.

## 🚀 Aktueller Stand
- [x] WLAN-Verbindung stabil
- [x] NTP-Zeit-Synchronisation erfolgreich
- [x] Serielle Zeit-Ausgabe (115200 Baud)
- [x] Test-Logik für volle Stunde an GPIO 2 integriert
- [ ] Hardware-Ausbau (LED-Ring/Einzel-LEDs)