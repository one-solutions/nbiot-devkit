# Code Examples
Wie man die one:connect Library in ein Projekt einbindet ist [hier](../04_oneconnect_verbindungslibrary/04_oneconnect_verbindungslibrary.md) beschrieben.
Die ersten Schritte mit dem IoT-Piloten können [hier](../05_first_steps/05_first_steps.md) durchgegangen werden.


## Example Project
Im ExampleProject Ordner ist ein fertig konfiguriertes Simplicity Studio Projekt enthalten.
Das Projekt verwendet den ARM GNU Embedded Toolchain v7.2.1 und Gecko MCU SDK v.5.8.0.0. Der ARM  Embedded Toolchain, sowie die Gecko SDK werden zusammen mit den Simplicity Studio installiert.
Alternativ können die Sources in ein eigenes Projekt importiert werden.

Im Beispielprojekt werden die auf den IoT Piloten verfügbare Sensoren angesprochen, so wie der Umgang mit der one:connect Library demonstriert. Die PB0 und PB1 Tasten auf den GeckoKit wurden folgend programmiert:  

- mit Hilfe der PB0-Taste werden die BMI160 und BME280 Sensoren abgefragt und über den
seriellen Output im Terminal angezeigt  

- mit der PB1-Taste werden die BMI160 und BME280 Sensoren abgefragt und deren Messungen an das Magenta IoT-Gateway übertragen

Im Magenta IoT-Gateway ist bereits ein Plugin für den IoT-Piloten installiert. Das Plugin parst die empfangen Daten und stellt sie in JSON Format auf dem Magenta IoT-Gateway zur Verfügung.  
Im Plugin wird für das ExampleProject verwendete Skalierung von BMI160 unterstützt d.h. 2G für den Accelerator und 2000 DPS für das Gyroscope. Falls Werte mit anderen Einstellungen übertragen werden, können Sie mit diesem Plugin nicht richtig dargestellt werden.

## Download
Die Examples können hier heruntergeladen werden.

[ExampleProject_v1.1](ExampleProject_v1.1.zip)

[ExampleProject_v1.2.7](ExampleProject_v1.2.7.zip)


[linkLib]:[../04_oneconnect_verbindungslibrary]
[linkSteps]:[../05_first_steps]
