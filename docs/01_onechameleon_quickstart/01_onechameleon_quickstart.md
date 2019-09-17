
# one:chameleon Quickstart Guide

Das one:chameleon ist der perfekte Startpunkt um mit der Entwicklung eines IoT Projektes zu starten.
Kernpunkt des one:chameleon ist das [NarrowBand IoT (NB-IoT)][nbiot_wp] Radio Module. Mithilfe der NB-IoT Technologie können Sie kostengünstig und energieeffizient überall Daten in die Cloud oder zu Ihrem Server versenden und empfangen.
Neben dem NB-IoT Radio Module enthält das one:chameleon Board noch Sensoren, Interfaces für diverse Anbindungen und Erweiterungsmöglichkeiten. 
Optional haben Sie auch die Möglichkeit ein GPS-Module zu verwenden.

 > **IoT Pilot Inhalt**
 > + EFM32 Happy Gecko Starter Kit board
 > + one:chameleon Sensorboard
 > + 1x mini USB Kabel
 > + 1x micro USB Kabel
 > + 1x NB-IoT Antenne
 > + Getting Started Karte
 > + SIM-Chip (auf one:chameleon Board) inkl. NB-IoT Connectivity
  
## 1. Getting Started  

![one:chameleon Beschreibung][o:ch_besch]

Nach dem Auspacken Ihres IoT-Piloten, machen Sie sich mit dem one:chameleon Sensorboard vertraut.  

Auf der linken Seite finden Sie den Connector um das one:chameleon Sensorboard mit dem EFM32 Happy Gecko Starterkit zu verbinden.

Gleich darüber befindet sich der Multplex Switch. Mit diesem können Sie unterschiedliche Interfaces auswählen, die die gleichen Leitungen verwenden (Bsp: UART und SPI).

Darunter befindet sich der Power Meter Switch. Mit diesem können Sie auswählen, ob die integrierte Energieverbrauchsemessung auch für das NB-IoT Radio Modul durchgeführt werden soll. Dies ist hilfreich, wenn Sie den Magenta IoT Solution Optimizer verwenden. Default ist I_OFF.

Am oberen Rand befindet sich ein 3-poliger Stecker für 1-Wire Module. Am Rasperry PI Header steht das 1-Wire Interface ebenso zur Verfügung.

Am unteren Rand steht noch ein SD-Karten Slot zur Verfügung. Dieser verwendet das SPI Interface.

Für Erweiterungen sind zwei Stecker für das [Grove System][grove] verbaut. Einmal für I2C und einmal für GPIO . Wählen sie aus einer Vielzahl von Sensoren oder Aktoren.

Als Interface stehen I2C, 1-Wire, SPI, UART, GPIO und 2 Analog Eingänge zur Verfügung. Diese Interface können Sie über den Raspberry PI Header, Grove Stecker, 1-Wire Stecker oder am IoT Expansion Card Stecker verwenden.

Bevor Sie mit der Entwicklung beginnen, verbinden sie die Antenne mit dem NB-IoT Antennen Stecker. Danach können Sie das EMF32 Happy Gecko Starterkit an das one:chameleon Sensorboard anschließen. Zu guter letzt wählen Sie ihre Sensoren und Interface aus und Verbinden Sie diese mit dem Senorboard. Vergessen Sie dabei nicht, auf die richtige Einstellung des Multiplex Switch.

## 2. Raspberry PI Header

Für diverse Erweiterungen steht Ihnen ein Raspberry PI Header zur Verfügung. Die Anschlussbelegung ist teilweise multiplexed und kann über den Multiplex Switch konfiguriert werden.

![Raspberry PI Header][rpi]

[nbiot_wp]: https://businessblog.magenta.at/whitepaper-nb-iot "Magenta NB-IoT Whitepaper"
[grove]: http://wiki.seeedstudio.com/Grove_System/ "Grove System"

### UART:

MCU Funktion: US0 auf Position 0 im asynchrone Mode.  

Um die UART nutzen zu können, zuerst den Multiplex Switch wie folgt einstellen. Damit wählen Sie zwischen UART oder SPI(USART).  

TXD: Port E, Pin 10
RXD: Port E, Pin 11

1=ON, 2=OFF  
3=ON, 4=OFF  
5=ON, 6=OFF  
7=ON, 8=OFF  

---

*Falls Sie das optional erhältliche GNSS Modul verwenden, dann wird diese UART für das GNSS Modul verwendet.*

---

### SPI:

MCU Funktion: US0 auf Position 0 im synchrone Mode.

Um die SPI Schnittstelle nutzen zu können, zuerst den Multiplex Switch wie folgt einstellen. Damit wählen Sie zwischen SPI (USART) oder UART.  

MOSI: Port E, Pin 10  
MISO: Port E, Pin 11  
CLK:  Port E, Pin 12  
CS:   Port E, Pin 13  

1=OFF, 2=ON  
3=OFF, 4=ON  
5=OFF, 6=ON  
7=OFF, 8=ON  

---

*Verwenden Sie die SD-Card wird die SPI Schnittstelle für die SD-Card verwendet.*

---

### I2C:
MCU Funktion: I2C0 auf Position 4  
SDA: Port C, Pin 0  
SCL: Port C, Pin 1

Der I2C Bus wird von mehreren Sensoren und Modulen auf dem Development Board verwendet. Zusätzlich steht Ihnen der I2C Bus für Erweiterungen auf dem Raspberry PI Header und Expansion Board Header zur Verfügung.  

| Sensor | Typ    | I2C Adresse |
| ------ | ------ | ------- |
| Temperatur, Luftfeuchtigkeit, Luftdruck | [Bosch BME280][bme280] | 0x76 |
| 6-Achsen Motion | [Bosch BMI160][bmi160] | 0x68 |
| EEPROM | [Microchip 24CW320][e2prom] | 0x50 |
| 1-Wire Bus Treiber | [Dallas DS2484][ds2484] | 0x18 |
||||

[o:ch_besch]: ./pics/och_sb_beschreibung.png
[rpi]: ./pics/rpi_header.png
[e2prom]: http://ww1.microchip.com/downloads/en/DeviceDoc/24CW16X-24CW32X-24CW64X-24CW128X-Data-Sheet-20005772B.pdf

[bmi160]: https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMI160-DS000.pdf

[bme280]: https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BME280-DS002.pdf

[ds2484]: https://datasheets.maximintegrated.com/en/ds/DS2484.pdf
