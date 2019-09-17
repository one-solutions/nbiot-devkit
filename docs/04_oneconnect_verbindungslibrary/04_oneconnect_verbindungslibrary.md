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
   
   uint32_t connection_reestablishment_intervall;
   enum psm_modes psm_mode;
   uint8_t psm_activity_timer;
   uint8_t lp_tau_timer;
   uint32_t paging_time_window;
   uint32_t edrx_cycle;

   void (*radio_receive_callback)(uint8_t *data, uint16_t len);

   bool allow_radio_sw_upgrade;
   bool allow_mcu_sw_upgrade;
   uint32_t sw_version_id;

   void (*set_time)(uint32_t epoch_sec);
   void (*radio_notify)(radio_stats_t *stats);

   enum encryption_modes encryption_mode;
   char encryption_psk[33];
   
   enum notification_modes notification_mode;

   char radio_module_type[5];
}
```
| Paramter | Beschreibung |
| ---- | ----|
|`psm_mode`| Der psm_mode Paramter ermöglicht dem Benutzer den Energiesparmodus zu konfigurieren. Folgende Optionen stehen zur Verfügung: DRX, PSM, eDRX </br>Prekonfiguriert: DRX|
|`psm_activity_timer`| Der psm_activity_timer definiert die angeforderte aktive Zeit (T3324) für das Gerät. Dieser Parameter wird nur benötigt, wenn der PSM-Modus aktiviert wurde. </br>Prekonfiguriert: 10 Stunden |
|`lp_tau_timer`| Der lp_tau_timer definiert die angeforderte erweiterte periodische TAU (T3412) im LTE Netz. Dieser Parameter ist nur erforderlich, wenn der PSM-Modus aktiviert wurde. </br>Prekonfiguriert: 10 Stunden|
|`paging_time_window`| xxx |
|`xxx`| xxx |
|`xxx`| xxx |
|`xxx`| xxx |
|`xxx`| xxx |
|`xxx`| xxx |
|`xxx`| xxx |

[addLib]: ../pics/addLib.png 

