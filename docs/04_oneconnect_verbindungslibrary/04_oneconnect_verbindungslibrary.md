# one:connect Verbindungslibrary

## Import one:connect Library in Simplicity Studio
Um die one:connect Libary in einem Projekt verwenden zu können, muss die vorher zum Projekt hinzugefügt werden.
1. Öffene Project Properties und gehe zu Settings.
2. Wähle die Configuration für die Einstellungen gelten sollen.
3. Im Tool Settings Bereich öffene den  GNU ARM C Linker Abschnitt und wähle Libraries.
4. Gib Namen der Assembler Datei an, im Fall ist es "one-connect"
5. Definiere wo sich die Library-Datei befindet

![][addLib]

## Wie benutzt man die one:connect Library?
1. Folgende Callback-Funktionen müssen vom Benutzer implementiert werden:

| Funktion | Beschreibung |
| ---- | ----|
| `void radio_receive (uint8_t * data, uint16_t len)` | Diese Funktion ermöglicht Empfang der Nachrichten, die vom IoT-Gateway an das Gerät verschickt werden. |
| `void radio_notify (struct radio_stats * stats)` | Diese Funktion wird jedes Mal aufgerufen, wenn sich Daten in der `radio_stats-Struktur` geändert haben. Welche Daten überwacht und gemeldet werden sollen, kann in der Struktur `radio_config` mit Hilfe des Parameters `notification_mode` bestimmt werden. |
 

2. Um das Funkmodul zu initialisieren, muss zunächst eine Gerätestruktur erstellen.</br>
Dazu legen Sie eine Instanz der Struktur `radio_config` an.
Füllen Sie anschließend die verschiedenen Parameter aus.
 

3. Initialisieren Sie das Funkmodul mit der Funktion `radio_init`.
 

4. Um die Verbindung mit dem Mobilfunknetz herzustellen, rufen Sie die Funktion `radio_connect` auf.
Falls der Parameter `notification_mode`  in der Struktur `radio_config` mit NOTIFY_NETREG konfiguriert wurde, ruft die Bibliothek nach erfolgreicher Verbindung mit den Netz die Funktion `radio_notify` auf.
Andernfalls kann die Struktur `radio_stats` nachdem Status abgefragt werden. 

## Konfiguration
In der `radio_config` Struktur werden die Einstellungen, die für die NB-IoT-Verbindung mit dem IoT-Gateway erforderlich sind, gespeichert.


```c
struct radio_config 
{
   char apn_name[40];
   char apn_type[5];
   char devmgmt_server_ip[16];
   char devmgmt_server_port[6];
   
   enum psm_modes psm_mode;

   uint8_t psm_activity_timer;
   uint8_t lp_tau_timer;

   void (*radio_receive_callback)(uint8_t *data, uint16_t len);
   void (*radio_notify)(radio_stats_t *stats);
   void (*radio_notify_new_time)(uint32_t newTime);

   enum encryption_modes encryption_mode;
   char encryption_psk[33];
   
   enum notification_modes notification_mode;
}
```
| Paramter                | Beschreibung                                                                                                                  |
| ----------------------- | ------------------------------------------------------------|
| `apn_name`              | Name des NB-IoT APN. </br>Magenta APN wurde prekonfiguriert.|
| `apn_type`              | Typ von APN. </br>Prekonfiguriert: IP. |
| `devmgmt_server_ip`     | IP-Addresse von IoT-Gateway. </br>Magenta IoT-Gateway wurde prekonfiguriert. |
| `devmgmt_server_port`   | Port unter welchen das IoT-Gateway erreichbar ist.</br>Magenta IoT-Gateway APN wurde prekonfiguriert. |
| `psm_mode`| Der psm_mode Parameter ermöglicht dem Benutzer den Energiesparmodus zu konfigurieren. Folgende Optionen stehen zur Verfügung: DRX, PSM, eDRX. </br>Prekonfiguriert: DRX|
| `psm_activity_timer`    | Der psm_activity_timer definiert die angeforderte aktive Zeit (T3324) für das Gerät. Dieser Parameter wird nur benötigt, wenn der PSM-Modus aktiviert wurde. </br>Prekonfiguriert: 10 Stunden |
| `lp_tau_timer`          | Der lp_tau_timer definiert die angeforderte erweiterte periodische TAU (T3412) im LTE Netz. Dieser Parameter ist nur erforderlich, wenn der PSM-Modus  aktiviert wurde. </br>Prekonfiguriert: 10 Stunden|
| `encryption_mode`       | Mit dem encryption_mode Parameter kann die Nutzdatenverschlüsselung konfiguriert werden. Folgende Optionen stehen zur Verfügung: DTLS, DTLS +, NONE. </br>Prekonfiguriert: NONE |
| `notification_mode`     | Mit dem notification_mode PArameter können die Benachritigugen konfiguriert werden. Die Einstellung bestimmt wann d.h. bei welchen Ereignis die radio_notify Funktion aufgerufen werden soll.</br>Folgende Optionen stehen zur Verfügung: </br> NOTIFY_NEVER - keine Benachritigung, </br>NOTIFY_NETREG - Benachritigung bei Anderung des Registrierstatus in Mobilfunknetz , </br>NOTIFY_PSM - Banachrtigung wenn das radio Module den Energiemodus wechselt</br>NOTIFY_LWM2M_STATUS - LWM2M-Event Benachritigung, </br>NOTIFY_LWM2M_DATA_STATUS - Benachritigung für Bestätigungsnachrichten für geschickte Daten.</br>Prekonfiguriert: NOTIFY_NEVER </br>Beispiel: `notificatation_mode = NOTIFY_NETREG | NOTIFY_PSM | NOTIFY_LWM2M_STATUS`.|
| `encryption_psk`        | Der PSK Schlüssel der für die Nutzdatenverschlüsselung genützt werden soll. |
| `radio_receive_callback`| Der Parameter radio_receive_callback ermöglicht eine Empfangs-Callback-Funktion zu regestrieren. Unmittelbar nach dem Empfang der Nachricht werden die Daten aus dem lokalen FIFO Empfangspuffer der LEUART an die entsprechende Callback-Funktion weiterleitet. |
| `radio_notify`          | Im radio_notify Parameter kann eine Notify-Callback-Funktion angegeben werden. Soobald ein Ereigniss, der in notification_mode activiert wurde, statt findet, wird die Funktion aufgerufen.      |
| `radio_notify_new_time` | Im radio_notify_new_time Parameter kann eine Notify-Callback-Funktion für Systemzeit-Synchronisierung angegeben werden. Nachdem das Radio Module die aktuelle Uhrzeit vom IoT-Gateway empfangen hat, wird der RTC gesetzt und der Timestamp an die Callback-Funktion weitergegeben. |

## Funktionen

| Funktion                                                        | Beschreibung |
| ----------------------------------------------------------------| -------------|
| `radio_init(radio_config_t *config)`                            | Initalisierung von dem Radio Modul unf LEUART |
| `radio_connect(radio_config_t *config)`                         | Aufbau der Netzverbindung mit NB-IoT und IoT-Gateway |
| `radio_send(enum send_modes mode, uint8_t *data, uint16_t len)` | Senden von Daten zu IoT-Gateway |
| `radio_get_netstats(void)`                                      | Frage die RAdio-Modul Netzstatistik ab |
| `radio_synchtime(void)`                                         | Synchronsiere RTC mit IoT-Gateway |
| `radio_get_rtc(void)`                                           | Frage die aktuelle Uhrzeit an Gerät ab |
| `radio_get_millis(void)`                                        | Frage die Millisekunden seit Prozessorstart ab |
| `radio_set_power_mode(radio_config_t *rc)`                      | Wenn der PSM mode in radio_config aktiviert wurde, dann wird das PSM Mode auf den Radio Modul konfiguriert. Andersfalls wird das PSM deaktiviert. |
| `radio_reboot(enum reboot_modes mode)`                          | Rebooten von Radio Modul. |

[addLib]: ../pics/addLib.png 

