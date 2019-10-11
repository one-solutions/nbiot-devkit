# IoT Pilot First Steps

## Schritt 1 - Applikation in IoT Gateway anlegen

1. Im IoT Gateway anmelden:</br>
   https://iotgateway.magenta.at/</br>

2. Um eine Applikation im IoT Gateway zu anlegen müssen die Schritte lt. der Einleitung [Create your first Application][create1App_link] befolgt werden.

## Schritt 2 - NBIot-Pilot Profile importieren

1. Das NBIoT Profile von [Github][profileLink] herrunterladen
2. Im Menu "Device Management" auswählen:
    ![][selectDeviceMgmt]

    Danach in der Sidebar zum Bereich "Product Models" hingehen.

    ![][go2ProductModels]

3. Auf der "Product models" Seite auf den "+ Add" klicken und "Import from Local" auswählen
    ![][importLocal]

    Im Formular Namen des Produkts "NBIot-Pilot" eintragen und die zip Datei hochladen.
    ![][importWindow]

## Schritt 3 - IoT-Pilot Device im IoT Gateway anlegen

1. Zu erst zu "Device Management" hingehen, dann in der Device Sidebar Registration Seite auswählen:
![][selectReg]
2. Auf der Registration Seite auf "+ Register" klicken um das Gerät hinzufügen. Dann erscheint ein Registration Formular zu ausfühlen.
![][registerDevice]

    1. Auf "Select Product" klicken und den zuvor hochgeladnen "NBIoT-Pilot" als Produkt auswählen. ![][iotPilotIcon]
    2. Als "Node ID" die IMEI Nummer des IoT Piloten eintragen
    3. Einen Namen für das Gerät vergeben z.B. "IoT Pilot 01"
    4. Die Zeitzone, in der sich das Gerät befindet, auswählen
    5. Das Gerät zur der Default Group zuordnen
    6. Für Testzwecke kann DTLS deaktiviert werden

## Schritt 4 - IoT Pilot Beispiel Programm herunterladen

1. ExampleProject von [Github][exampleLink] herunterladen
2. Das Projekt in Simplicity Studio importieren (Menu File -> Import)
3. Das Programm auf den GeckoKit hochladen:
![][runProject]

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
