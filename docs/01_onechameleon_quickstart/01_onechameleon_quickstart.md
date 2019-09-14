
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

Am oberen Rand befindet sich ein 3-poliger Stecker für 1-Wire Module. Am Rasperry PI Header steht das 1-Wier Interface ebenso zur Verfügung.

Am unteren Rand steht noch ein SD-Karten Slot zur Verfügung. Dieser verwendet das SPI Interface.

Für Erweiterungen wurden zwei Stecker für das [Grove System][grove] verbaut. Einmal für I2C und einmal für GPIO . Wählen sie aus einer Vielzahl von Sensoren oder Aktoren.

Als Interface stehen I2C, 1-Wire, SPI, UART, GPIO und 2 Analog Eingänge zur Verfügung. Diese Interface können Sie über den Raspberry PI Header, Grove Stecker, 1-Wire Stecker oder am IoT Expansion Card Stecker verwenden.

Bevor Sie mit der Entwicklung beginnen, verbinden sie die Antenne mit dem NB-IoT Antennen Stecker. Danach können Sie das EMF32 Happy Gecko Starterkit an das one:chameleon Sensorboard anschließen. Zu guter letzt wählen Sie ihre Sensoren und Interface aus und Verbinden Sie diese mit dem Senorboard. Vergessen Sie dabei nicht, auf die richtige Einstellung des Multiplex Switch.

## 2. Raspberry PI Header

Für diverse Erweiterungen steht Ihnen ein Raspberry PI Header zur Verfügung. Die Anschlussbelegung ist teilweise multiplexed und kann über den Multiplex Switch konfiguriert werden.

![Raspberry PI Header][rasperrypi]

[nbiot_wp]: https://businessblog.magenta.at/whitepaper-nb-iot "Magenta NB-IoT Whitepaper"
[grove]: http://wiki.seeedstudio.com/Grove_System/#digital "Grove System"

[o:ch_besch]: ./pics/och_sb_beschreibung.png
[rasperrypi]: ./pics/raspberrypi.png
