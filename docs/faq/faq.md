FAQ
==========
[1. Wie verbinde ich meinen PC mit dem IoT-Pilot?](./faq/faq?id=wie-verbinde-ich-meinen-pc-mit-dem-iot-pilot)
<br>
[2. Wie greife ich auf die Terminalausgaben des IoT-Pilots zu?](./faq/faq?id=wie-greife-ich-auf-die-terminalausgaben-des-iot-pilots-zu)
<br>
[3. Warum funktioniert der SD-Card-Slot meines IoT-Piloten nicht?](./faq/faq?id=warum-funktioniert-der-sd-card-slot-meines-iot-piloten-nicht)
<br>
[4. Warum werden meine Breakpoints ignoriert?](./faq/faq?id=warum-werden-meine-Breakpoints-ignoriert)
<br>

Fragen
==========
Wie verbinde ich meinen PC mit dem IoT-Pilot?
----------
Die Entwicklungsumgebung stellt im Normalfall automatisch eine Verbindung zum Developer-Kit her.

Wie greife ich auf die Terminalausgaben des IoT-Pilots zu?
----------
Um die Terminalausgaben des IoT-Pilots zu sehen wird ein serielles Terminal (z.B. [Putty](https://www.putty.org)) benötigt.

"Serial" muss gewählt sein um anschließend den "COM-Port" sowie die Speed von 9600 einzutragen
<br>
<img src="./faq/pics/puttyconfig.png" width="40%">

Der "COM-Port" kann über den Geräte-Manager bestimmt werden. (<code>Geräte-Manager -> Anschlüsse(COM&LPT) -> JLink CDC UART Port (COM<b>#</b>)</code>)
<p><img src="./faq/pics/geraetemanagercom.png" width="20%"></p>

Warum funktioniert der SD-Card-Slot meines IoT-Piloten nicht?
----------
Um die Funktionalität des Micro-SD-Card-Slots zu Gewährleisten muss der <strong>Multiplex Dip Switch</strong> passend [konfiguriert](./01_onechameleon_quickstart/01_onechameleon_quickstart?id=spi) sein.

Warum werden meine Breakpoints ignoriert?
----------
damit Simplicity Studio auf Breakpoints reagiert ist in den Projektsettings das Debug-Level anzupassen:<p>
Dazu bitte im Simplicity Studio das Projekt laden. Unter Menü Project -> Properties -> C/C++ Build -> Settings -> im Tab Tool Settings -> Debug Settings -> den Wert "Debug Level" von "Default" auf "Maximum" ändern und bestätigen.