# IoT Pilot First Steps

## Schritt 1 - Applikation im IoT Gateway anlegen

1. Im IoT Gateway anmelden:</br>
   https://iotgateway.magenta.at/</br>

2. Um eine Applikation im IoT Gateway anzulegen,müssen die Schritte lt. der Anleitung [Create your first Application][create1App_link] durchgeführt werden.

## Schritt 2 - NB-IoT Pilot Profile importieren

1. Das NBIoT Profile von [Github][profileLink] herrunterladen
2. Im Menu "Device Management" auswählen: <br>
    ![][selectDeviceMgmt]

    Danach in der Sidebar auf "Product Models" klicken.

    ![][go2ProductModels]

3. Auf der "Product models" Seite den "+ Add" Link anklicken und "Import from Local" auswählen <br>
    ![][importLocal]

    Im Formular Namen des Produkts "NB-IoT Pilot" eintragen und die zip Datei hochladen. <br>
    ![][importWindow]

## Schritt 3 - IoT-Pilot Device im IoT Gateway anlegen

1. Zu erst auf "Device Management" klicken, dann in der Device Sidebar Registration Seite auswählen: <br>
![][selectReg]
2. Auf der Registration Seite auf "+ Register" klicken um das Gerät hinzufügen. Als nächstes erscheint ein Registration Formular zum ausfüllen. <br>
![][registerDevice]

    a.) Auf "Select Product" klicken und den zuvor hochgeladenen "NB-IoT Pilot" als Produkt auswählen. <br> ![][iotPilotIcon]  

    b.) Als "Node ID" die IMEI Nummer des IoT-Piloten eintragen  

    c.) Einen Namen für das Gerät vergeben z.B. "IoT Pilot 01"  

    d.) Die Zeitzone, in der sich das Gerät befindet, auswählen  

    e.) Das Gerät zu Default Group zuordnen  

    f.) Für Testzwecke kann DTLS deaktiviert werden  

## Schritt 4 - IoT Pilot Beispiel Programm herunterladen

1. ExampleProject von [Github][exampleLink] herunterladen
2. Das Projekt in Simplicity Studio importieren (Menu File -> Import)
3. Das Programm auf den GeckoKit hochladen: 
<br> ![][runProject]


[selectDeviceMgmt]: ../pics/select_device_mgmt.png
[selectReg]: ../pics/devices_devreg.png
[iotPilotIcon]: ../pics/NBIotPilot_Product_Icon.png
[registerDevice]: ../pics/register_device.png
[go2ProductModels]: ../pics/select_productModels.png
[importLocal]: ../pics/import_from_local.png
[importWindow]: ../pics/import_window.png
[runProject]: ../pics/run_project.png

[create1App_link]: https://magentabusiness.github.io/IoT-Quickstart/#/01_Create_first_Application
[profileLink]: [../06_code_examples/Profile]
[exampleLink]: [../06_code_examples/ExampleLibProject]