# Setting Up Simplicity Studio

Auf dieser Seite erfahren Sie, wie Sie Simplicity Studio aufsetzen und mit dem EFM32 Happy Gecko Starter Kit SLSTK3400A verwenden.

## 1. Instalation von Simplicity Studio
Simplicity Studio ist eine kostenlose Software Developement-Umgebung für Silicon Labs Microcontroller. Sie können die neueste Version von Simplicity Studio von der Silicon Labs-Website herunterladen: [https://www.silabs.com/simplicity-studio][simplicity_download]


## 2. Starteer Kit verbinden
| Versorgen Sie die Karte mit Strom, indem Sie den DBG-USB-Anschluss mit dem mitgelieferten USB-Kabel an den PC anschließen. Dann stellen Sie den Energiezufuhr-Schalter in die AEM Position. | ![AEM][AEMimg] |
</br>Das Entwickler Kit wird automatisch von Simplicity Studio erkannt.
Im dem Debug Adapters Bereich das Starter-Kit auswählen, damit die relevante Beispielprograme und Dokumentation auf der Getting Started Seite eingezeigt werden.
![DebugAdapter-Bereich][DebugAdapterImg]
![Getting Startet][GettingStartet]
</br></br>Zusätzliche Tools und Gecko SDK können unter "Help -> Software Update" mit der Hilfe von Installation Manager installiert werden.  
![](../pics/InstallationManager.png ':size=50%')

Der Simplicity Studio User Guide kann von der SiLocon Labs Seite heruntergeladet werden:</br>
[AN0822-simplicity-studio-user-guide.pdf][simplicity_ug]



[simplicity_download]: https://www.silabs.com/products/development-tools/software/simplicity-studio
[simplicity_ug]: https://www.silabs.com/documents/public/application-notes/AN0822-simplicity-studio-user-guide.pdf

[DebugAdapterImg]: ../pics/Launcher_DebugAdapter.png
[GettingStartet]: ../pics/Launcher_GettingStartet.png
[AEMimg]: ../pics/aem.png
[InstallMgr]: ../pics/InstallationManager.png 
