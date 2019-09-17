# Setting Up Simplicity Studio

Auf dieser Seite wird beschrieben wie man Simplicity Studio aufsetzt.

## 1. Instalation von Simplicity Studio
Simplicity Studio ist eine kostenlose Software Developement-Umgebung für Silicon Labs Microcontroller. Die neueste Version von Simplicity Studio kann von der Silicon Labs-Website heruntergeladet werden: [https://www.silabs.com/simplicity-studio][simplicity_download]


## 2. Starter Kit verbinden
Damit die Karte mit Strom versorgt ist, ist der DBG-USB-Anschluss mit dem mitgelieferten USB-Kabel an den PC anzuschließen. Dann muss der Energiezufuhr-Schalter in die AEM Position gestellt werden. ![AEM][AEMimg]

Das Entwickler Kit wird automatisch von Simplicity Studio erkannt.
Die relevanten Beispielprograme und die SLSTK3400A Dokumentation wird auf der Getting Started Seite eingezeigt. Damit die Inhalte geladet werden muss im dem Debug Adapters Bereich das Starter-Kit ausgewählt werden.

![DebugAdapter-Bereich][DebugAdapterImg]

![Getting Startet][GettingStartet]
</br></br>Zusätzliche Tools können unter "Help -> Software Update" mit der Hilfe von Installation Manager installiert werden.  
![](../pics/InstallationManager.png ':size=50%')

Der Simplicity Studio User Guide kann von der Silicon Labs Seite heruntergeladet werden:</br>
[AN0822-simplicity-studio-user-guide.pdf][simplicity_ug]



[simplicity_download]: https://www.silabs.com/products/development-tools/software/simplicity-studio
[simplicity_ug]: https://www.silabs.com/documents/public/application-notes/AN0822-simplicity-studio-user-guide.pdf

[DebugAdapterImg]: ../pics/Launcher_DebugAdapter.png
[GettingStartet]: ../pics/Launcher_GettingStartet.png
[AEMimg]: ../pics/aem.png
[InstallMgr]: ../pics/InstallationManager.png 
