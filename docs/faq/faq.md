FAQ
==========
[1. Wie verbinde ich meinen PC mit dem IoT-Pilot?](./faq/faq?id=wie-verbinde-ich-meinen-pc-mit-dem-iot-pilot)
<br>
[2. Wie greife ich auf die Terminalausgaben des IoT-Pilots zu?](./faq/faq?id=wie-greife-ich-auf-die-terminalausgaben-des-iot-pilots-zu)
<br>
[3. Warum funktioniert der SD-Card-Slot meines IoT-Piloten nicht?](./faq/faq?id=warum-funktioniert-der-sd-card-slot-meines-iot-piloten-nicht)

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
Um die Funktionalität des Micro-SD-Card-Slots zu Gewährleisten muss der <strong>Multiplex Dip Switch</strong> wie folgt konfiguriert sein.
<br>
1=ON, 2=OFF<br>
3=ON, 4=OFF<br>
5=ON, 6=OFF<br>
7=ON, 8=OFF<br>
