# Code Examples
Wie man die one-connect Library in ein Projekt einbindet ist [hier][linkLib] beschrieben.
Die ersten Schritte mit den Iot-Piloten können [hier] durchgegangen werden.


## ExampleProject
Im ExampleProject Ordner ist ein fertig konfiguriertes Simplicity Studio Projekt enthalten.
Das Projekt verwendet den ARM GNU Embedded Toolchain v7.2.1 und Gecko MCU SDK v.5.8.0.0. Der ARM  Embedded Toolchain, sowie die Gecko SDK werden zusammen mit den Simplicity Studio installiert.
Alternativ können die Sources in ein eignes Projekt importiert werden.

Im Beispielprojekt werden die auf den IoT Piloten verfügbare Sensoren angesprochen, so wie der Umgang mit der one:connect Library demonstriert. Die PB0 und PB1 Tasten auf den GeckoKit wurden folgend programmiert:
- mit Hilfe der PB0-Taste werden die BMI160 und BME280 Sensoren abgefragt und über den Serielen Output im Terminal angezeigt
- mit der PB1-Taste werden die BMI160 und BME280 Sensoren abgefragt und deren Messungen an den IoT Gateway verschickt

Im Iot-Gateway ist bereits ein Plugin für den Iot Piloten installiert. Der Plugin parst die empfangen Daten und stellt die in JSON Format auf dem IoT-Gateway zur Verfügung. 
Im Plugin wird für den ExampleProject verwendete Skalierung von BMI160 unterstützt d.h. 2G für den Accelerator und 2000 DPS für Gyroscope. Falls Werte mit anderen Einstellungen übertragen werden, können Sie mit dem Plugin nicht richtig dargestellt werden.



[linkLib]:[../04_oneconnect_verbindungslibrary]
[linkSteps]:[../05_first_steps]