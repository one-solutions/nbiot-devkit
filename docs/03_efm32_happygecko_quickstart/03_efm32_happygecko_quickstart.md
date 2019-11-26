# EFM32 Happy Gecko Starterkit Quick Start Guide

Nach der [Installation des Silabs Simplicity Studios] bitte den IoT Pilot wie folgt anschliessen.

![SLK3400A] Happy Gecko Kit

## Verbinden des IoT Pilot Kits
a) Verbinden Sie das Sensorboard und den Happy Gecko Kit. Dazu stecken Sie an den Expansion Port des Happy Gecko Kits den 20-poligen Stecker des Sensorboards. <br>
b) Schalten Sie den Schalter am GeckoKit auf AEM <br>
c) Verbinden Sie mit dem beiligende Mini-USB Kabel ihren PC und Happy Gecko Kit am Debug-Stecker (DBG) <br>
d) schon können Sie ihre Applikation auf den Gecko laden

## Debug
Debug Messages können Sie via Consolenausgabe z.B.: über Putty ausgeben.

## Energiemessung
Im Silabs-Studio können Sie mit dem Energy Profiler auch den Stromverbrauch monitoren und sehen damit wie energiesparend ihre Applikation ist.
Um den Energieverbrauch mit dem Radiomodul zu messen, ist der Power Meter Switch am Sensorboard auf auf I_ON zu stellen. Die Stellung I_OFF ist die Energiemessung der Schaltung ohne Radiomodul. Hier wird das Radiomodul am Energieprofiler vorbei versorgt. Es ist dazu nichts extra nötig. <br>
Bitte schalten Sie den Power Meter Switch nur im stromlosen Zustand des IoT Pilot um. 

## Welche Sensoren kann ich verwenden?
Die meisten Sensoren befinden sich am Sensorboard bzw. kann das Sensorboard erweitert werden. 
zum Beispiel ist das Display am Happy Gecko Board zu verwenden. Am Sensorboard ist bereits der Display-Stecker für ihr Serienprodukt vorgesehen.<br>
Der Temperatursensor ist am Sensorboard zu verwenden, gerne gemeinsam mit Luftdruck und relativer Luftfeuchte.

## Next Step
Verbinden mit der [one:connect Library]

[SLK3400A]:./pics/Happy_Gecko_DBG.jpg
[Installation des Silabs Simplicity Studios]: ../02_settingup_simplicitystudio/02_settingup_simplicitystudio.md
[one:connect Library]: ../04_oneconnect_verbindungslibrary/04_oneconnect_verbindungslibrary.md
