# one:connect Verbindungslibrary

Die one:connect Library kann von GIT heruntergelden werden.

## Import one:connect Library in Simplicity Studio
Um die one:connect Libary in einem Projekt verwenden zu können, muss die vorher zum Projekt hinzugefügt werden. Dazu erstelle in der Projektstruktur einen one-connect Ordner und kopiere dort die libone-connet.a Datei und den one-connect.h Header. 

![][project]

Die Header-datei muss zu den Include Path im Projekt hinzugefugt werden: 

![][incPic]

Die libone-connet.a Datei muss als eine Library eingebunden werden, wie erfolgt:   

1. Öffene Project Properties und gehe zu Settings.
2. Wähle die Configuration für welche die Einstellungen gelten sollen.
3. Im Tool Settings Bereich öffene den  GNU ARM C Linker Abschnitt und wähle Libraries.
4. Gib den Namen der Assembler Datei an, im dem Fall ist es "one-connect"
5. Definiere den Pfad der Library-Datei.

![][addLib]

## Wie benutzt man die one:connect Library?
1. Folgende Callback-Funktionen sind vom Benutzer zu implementiert:

| Funktion | Beschreibung |
| ---- | ----|
| `void radio_receive (uint8_t * data, uint16_t len)` | Diese Funktion ermöglicht Empfang der Nachrichten, die vom IoT-Gateway an das Gerät verschickt werden. |
| `void radio_notify (struct radio_stats * stats)` | Diese Funktion wird jedes Mal aufgerufen, wenn sich Daten in der `radio_stats-Struktur` geändert haben. Welche Daten überwacht und gemeldet werden sollen, kann in der Struktur `radio_config` mit Hilfe des Parameters `notification_mode` bestimmt werden. |
 

2. Um das Funkmodul zu initialisieren, ist zunächst eine Gerätestruktur zu erstellen.</br>
Dazu legen Sie eine Instanz der Struktur `radio_config` an.
Füllen Sie anschließend die verschiedenen Parameter aus.
 

3. Initialisieren Sie das Funkmodul mit der Funktion `radio_init`.
 

4. Um die Verbindung mit dem Mobilfunknetz herzustellen, rufen Sie die Funktion `radio_connect` auf. 
Falls der Parameter `notification_mode`  in der Struktur `radio_config` mit NOTIFY_NETREG konfiguriert wurde, ruft die Bibliothek nach erfolgreicher Verbindung mit den Netz die Funktion `radio_notify` auf.
Andernfalls kann die Struktur `radio_stats` nachdem Status abgefragt werden. 

## Konfiguration
In der `radio_config` Struktur werden die Einstellungen gespeichert, welche  für die NB-IoT-Verbindung mit dem IoT-Gateway erforderlich sind.


```c
struct radio_config 
{
   char apn_name[40];
   char apn_type[5];
   char devmgmt_server_ip[16];
   char devmgmt_server_port[6];
   
   enum encryption_modes encryption_mode;
   char encryption_psk[33];

   enum psm_modes psm_mode;
   uint8_t psm_activity_timer;
   uint8_t lp_tau_timer;

   enum notification_modes notification_mode;

   void (*radio_receive_callback)(uint8_t *data, uint16_t len);
   void (*radio_notify)(radio_stats_t *stats);
   void (*radio_notify_new_time)(uint32_t newTime);
}
```
| Parameter                | Beschreibung                                                                                                                  |
| ----------------------- | ------------------------------------------------------------|
| `apn_name`              | Name des NB-IoT APN. </br>Magenta APN wurde prekonfiguriert.|
| `apn_type`              | Typ von APN. </br>Prekonfiguriert: IP. |
| `devmgmt_server_ip`     | IP-Addresse von IoT-Gateway. </br>Magenta IoT-Gateway wurde prekonfiguriert. |
| `devmgmt_server_port`   | Port unter welchen das IoT-Gateway erreichbar ist.</br>Magenta IoT-Gateway APN wurde prekonfiguriert. |
| `encryption_mode`       | Mit dem encryption_mode Parameter kann die Nutzdatenverschlüsselung konfiguriert werden. Folgende Optionen stehen zur Verfügung: DTLS, DTLS +, NONE. </br>Prekonfiguriert: NONE |
| `encryption_psk`        | Der PSK Schlüssel der für die Nutzdatenverschlüsselung genützt werden soll. |
| `psm_mode`| Der psm_mode Parameter ermöglicht dem Benutzer den Energiesparmodus zu konfigurieren. Folgende Optionen stehen zur Verfügung: DRX, PSM, eDRX. </br>Prekonfiguriert: DRX|
| `psm_activity_timer`    | Der psm_activity_timer definiert die angeforderte aktive Zeit (T3324) für das Gerät. Dieser Parameter wird nur benötigt, wenn der PSM-Modus aktiviert wurde. </br>Prekonfiguriert: 10 Stunden |
| `lp_tau_timer`          | Der lp_tau_timer definiert die angeforderte erweiterte periodische TAU (T3412) im LTE Netz. Dieser Parameter ist nur erforderlich, wenn der PSM-Modus  aktiviert wurde. </br>Prekonfiguriert: 10 Stunden|
| `notification_mode`     | Mit dem notification_mode Parameter können die Benachrichtigungen konfiguriert werden. Die Einstellung bestimmt bei welchen Ereignis die radio_notify Funktion aufgerufen werden soll.</br>Folgende Optionen stehen zur Verfügung: </br> NOTIFY_NEVER - keine Benachrichtigung, </br>NOTIFY_NETREG - Benachrichtigung bei Änderung des Registrierungsstatus in Mobilfunknetz, </br>NOTIFY_PSM - Banachrichtigung wenn das radio Module in den Energiemodus wechselt</br>NOTIFY_LWM2M_STATUS - LWM2M-Event Benachrichtigung, </br>NOTIFY_LWM2M_DATA_STATUS - Benachrichtigung für Bestätigungsnachrichten für gesendete Daten.</br>Prekonfiguriert: NOTIFY_NEVER </br>Beispiel: `notificatation_mode = NOTIFY_NETREG | NOTIFY_PSM | NOTIFY_LWM2M_STATUS`.|
| `radio_receive_callback`| Der Parameter radio_receive_callback ermöglicht eine Empfangs-Callback-Funktion zu registrieren. Unmittelbar nach dem Empfang der Nachricht werden die Daten aus dem lokalen FIFO Empfangspuffer der LEUART an die entsprechende Callback-Funktion weiterleitet. |
| `radio_notify`          | Im radio_notify Parameter kann eine Notify-Callback-Funktion angegeben werden.  Im notification_mode sind die  Ereignisse zuvor zu aktivieren. Das nächste Ereignis ruft die Funktion auf.      |
| `radio_notify_new_time` | Im radio_notify_new_time Parameter kann eine Notify-Callback-Funktion für Systemzeit-Synchronisierung angegeben werden. Nachdem das Radio Module die aktuelle Uhrzeit vom IoT-Gateway empfangen hat, wird der RTC gesetzt und der Timestamp an die Callback-Funktion weitergegeben. |

## LWM2M Event Benachrichtigung
In `radio_stats_t` in `lwm2m_data_status` werden die LWM2M Benachritigungen gespeichert.

| Code |  Benachrichtigung                             
| ----| ------------------------------------------------| 
| 0   | Registrierung abgeschlossen                     |
| 1   | Abmeldung abgeschlossen                         |
| 2   | Registrierungsstatus aktualisiert               |
| 3   | Objekt 19/0/0 wurde empfangen und wird beobachtet|
| 4   | Bootstrap abgeschlossen                          |
| 5   | Beobachtung von Objekt 5/0/3 wurde abgeschlossen |
| 6   | Aktualisierungs von Paket URL verfügbar         |
| 7   | Download wurde abgeschlossen                    |
| 9   | Beobachtung von Objekt 19/0/0 wurde abgebrochen |


## Detailliertere Dokumentationen
Die Verwendung der neuesten Version (v1.2.7) wird empfohlen.

[v1.2.7](04_oneconnect_verbindungslibrary/documentations/v1.2.7.md)

[v1.1](04_oneconnect_verbindungslibrary/documentations/v1.1.md)



[addLib]: ../pics/addLib.png 
[incPic]: ../pics/incPath.png 
[project]: ../pics/project.png
