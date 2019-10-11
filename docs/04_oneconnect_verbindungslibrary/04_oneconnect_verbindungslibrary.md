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

## Funktionen

| Funktion            | Parameter    | Beschreibung                                     |
| --------------------| -------------| -------------------------------------------------|
| `radio_init`        | *config - Pointer zu `radio_config_t` Struktur | Diese Funktion führt die Initalisierung aus. Dazu zählt u.a. die Initialisierung des Radio Moduls und des LEUART. |
| `radio_connect`     | *config - Pointer zu `radio_config_t` Struktur | Diese Funktion baut die Netzverbindung mit Mobilfunk und dem IoT-Gateway auf. |
| `radio_send`        | mode - Sendemodus</br>*data - Pointer zu Pufferspeicher mit der Nachricht in binären Form, </br>len - Größe des Pufferspeichers| Diese Funktion ermöglicht das versenden von Nachrichten an das IoT-Gateway. </br>Folgende Sendemodi stehen zur Verfügung: </br> NACK - keine Empfangsbestätigung,</br>NACK_RELEASE - keine Empfangsbestätigung und RELEASE von Netz</br>NACK_RELEASE_AFTER_REPLY - keine Empfangsbestätigung und RELEASE nach Transportprotokollrückmeldung </br>ACK - Empfangsbestätigung für die Nachricht</br>ACK_RELEASE_AFTER_REPLY - Empfangsbestätigung für die Nachricht und RELEASE nach Transportprotokollrückmeldung |
| `radio_get_netstats`| keine  | Diese Funktion fragt die Netzstatistik des Radio-Moduls ab. Das Ergebnis wird in der `radio_stats` Struktur gespeichert. |
| `radio_synchtime`   | keine| Diese Funktion synchronisiert die Zeit der RTC mit dem IoT-Gateway. Die Antwort des IoT-Gateways ist die aktuelle Uhrzeit als Unix Epoche in Sekunden.  |
| `radio_get_rtc`     | keine| Diese Funktion ermöglicht die aktuelle Systemzeit des Geräts abzufragen. |
| `radio_get_millis`  | keine | Diese Funktion ermöglicht die Millisekunden seit Prozessorstart abzufragen. |
| `radio_set_power_mode` | *config - Pointer zu `radio_config_t` Struktur | Diese Funktion ermöglicht den PSM Modus ein / aus-zuschalten. Wenn der PSM  in radio_config definiert wurde, dann wird der PSM auf den Radio Modul aktiviert. Andersfalls wird das PSM deaktiviert. |
| `radio_reboot`      | mode - reboot Modus | Diese Funktion ermöglicht ein Reboot des Radio Moduls durchzuführen. Grundsätzlich gibt es zwei Reboot-Methoden, Softreboot und Hardreboot. Beim Softreboot wird das Radio Module über ein AT Commando rebootet und beim Hardreboot wird es über eine GPIO Leitung rebootet. Insgesamt sind folgende Reboot Modi verfügabr: </br>   SOFT_NO_RECONNECT - Softreboot ohne erneuten Verbindung mit Netz, </br> SOFT_WITH_RECONNECT - Softreboot mit erneuten Verbindung mit Netz,</br> HARD_NO_RECONNECT - Hardreboot ohne erneuten Verbindung mit Netz,</br> HARD_WITH_RECONNECT - Hardreboot mit erneuten Verbindung mit Netz |

Jede Funktion außer `radio_get_rtc` und `radio_get_millis` gibt den Wert 0 im Erfolgsfall oder den Error Code beim Auftreten eines Fehlers retour. 

## LWM2M Event Benachritigung
In `radio_stats_t` in `lwm2m_data_status` werden die LWM2M Benachritigungen gespeichert.

 Code |  Benachritigung                             
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

## Error Codes

Folgende one:connect Library spezifische Error Codes sind definiert:

| Code            | Name    | Beschreibung                                     |
| --------------------| -------------| -------------------------------------------------|
| 600 | RADIO_INIT_BAUDRATE_ERR | Die Konfiguration der Baudrate ist fehlgeschlagen. |
 | 601 |  RADIO_INIT_CFUN_ERR | Ein Fehler bzw. Timeout ist bei der Ein/Aus-Schaltung des Radioempfängers während der Initialisierung aufgetreten. |
 | 602 |  RADIO_INIT_NCONFIG_ERR | Die Konfiguration des Radio Moduls ist fehlgeschlagen. |
 | 603 |  RADIO_INIT_REBOOT_ERR | Ein Fehler bzw. Timeout ist beim Radio Modul reboot aufgetreten. |
 | 604 |  RADIO_INIT_NCDP_ERR | Die Konfiguration des IoT-Gateway Zugangs ist fehlgeschlagen. |
 | 605 |  RADIO_INIT_QREGSWT_ERR | Die Konfiguration des IoT-Gateway Registrierungsmodus ist fehlgeschlagen. |
 | 606 |  RADIO_INIT_DRX_MODE_ERR | Die Konfiguration des DRX Modus ist fehlgeschlagen.  |
 | 607 |  RADIO_INIT_PSM_MODE_ERR | Die Konfiguration des PSM Modus ist fehlgeschlagen. |
 | 608 |  RADIO_INIT_CMEE_ERR | Die Konfiguration des Error Modus des Radio Moduls ist fehlgeschlagen. |
 | 609 |  RADIO_INIT_CEREG_ERR | Das Ausführen des AT+CEREG Kommandos ist fehlgeschlagen. |
 | 610 |  RADIO_INIT_CSCON_ERR | Die Konfiguration des Signalling Connection Status ist fehlgeschlagen. |
 | 611 |  RADIO_INIT_NNMI_ERR | Die Konfiguration der Benachrichtigung für neue Daten ist fehlgeschlagen. |
 | 612 |  RADIO_INIT_NPSMR_ERR |  Die Konfiguration des Signalling Connection Status ist fehlgeschlagen. |
 | 613 |  RADIO_INIT_CGSN_ERR | Das Ausführen von den AT+CGSN Kommandos ist fehlgeschlagen. |
 | 614 |  RADIO_INIT_NCCID_ERR | Die Abfrage von USIM ist fehlgeschlagen. |
 | 615 |  RADIO_INIT_CIMI_ERR | Die Abfrage von IMSI ist fehlgeschlagen. |
 | 616 |  RADIO_INIT_CGDCONT_ERR | Die Abfrage bzw. Konfiguration von APN ist fehlgeschlagen. |
 | 617 |  RADIO_INIT_ENCRYPTION_MODE_ERR | Die Konfiguration von Verschlüsselung ist fehlgeschlagen. |
 | 618 |  RADIO_CONNECT_INIT_NOT_DONE_ERR | Das Radio Module wurde noch nicht Initialsiert, zu erst muss die `radio_init` Funktion aufgerufen werden. |
 | 619 |  RADIO_CONNECT_CFUN_ERR | Der Radioempfänger konnte nicht eingeschaltet werden. |
 | 620 |  RADIO_CONNECT_COPS_ERR | Der Verbindungsaufbau mit dem Netz ist fehlgeschlagen. |
 | 621 |  RADIO_SEND_TO_MUCH_DATA_ERR | Die Nachricht ist zu groß ( > 512 byte). |
 | 622 |  RADIO_SEND_IN_PROGRESS_ERR | Der Datenversand läuft noch. |
 | 623 |  RADIO_SEND_OBSRV19_ERR | Das Gerät ist nicht beim IoT-Gateway angemeldet. |
 | 624 |  RADIO_SEND_NOT_REGISTERED_ERR | Das Gerät ist nicht mit den Mobilfunknetz verbunden. |
 | 625 |  RADIO_SEND_ERR | Ein Fehler bzw. Timeout ist bei Versenden von Daten aufgetreten. |
 | 626 |  RADIO_NETSTATS_NOT_IDLE_ERR | Das Gerät ist nicht in Idle, somit die Abfrage der Radio-Netzstatistik ist nicht möglich.  |
 | 627 |  RADIO_NETSTATS_ERR |  Die Abfrage von der Radio-Netzstatistik ist fehlgeschlagen.  |
 | 628 |  RADIO_SET_POWERMODE_ERR | Ein Fehler ist bei Ausführung der radio_set_power_mode Funktion aufgetreten. |
 | 629 |  RADIO_SOFT_REBOOT_ERR | Softreboot des Radio Moduls ist fehlgeschlagen. |
 | 630 |  RADIO_HARD_REBOOT_ERR | Hardreboot des Radio Moduls ist fehlgeschlagen. |

[addLib]: ../pics/addLib.png 
[incPic]: ../pics/incPath.png 
[project]: ../pics/project.png
