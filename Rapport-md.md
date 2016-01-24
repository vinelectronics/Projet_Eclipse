# Sujet : Programmation de µC avec Eclipse
##### UE : Programmation orienté objet
##### Auteurs : FRANCOIS Kévin / ANICIC Jean-Baptiste
##### Université : INSSET / UPJV - M1SE - Semestre 1
##### Date : 26 Janvier 2016

## <p style='text-align: center;'>Sommaire</p>

[1. Objectif](#n1)</br>
[2. Logiciels de développement](#n2)</br>
[3. Installation des logiciels](#n3)</br>
[4. Installation des drivers pour la sonde JTAG](#n4)</br>
[5. Débug de la carte avec Eclipse](#n5)</br>
&nbsp;&nbsp;&nbsp;&nbsp;[5.1 Lancement d'Openocd](#n5.1)</br>
&nbsp;&nbsp;&nbsp;&nbsp;[5.2 Configuration de Eclipse](#n5.2)</br>
&nbsp;&nbsp;&nbsp;&nbsp;[5.3 Moyens de débug](#n5.3)</br>
[6. Débug de la carte avec Keil](#n6)</br>
[7. Avantages et inconvénients entre Eclipse et Keil](#n7)</br>
[8. JTAG](#n8)</br>
[9. Problèmes rencontrés](#n9)</br>
&nbsp;&nbsp;&nbsp;&nbsp;[9.1 Problème d'installation des pilotes de la sonde JTAG](#n9.1)</br>
&nbsp;&nbsp;&nbsp;&nbsp;[9.2 Problème de compatibilité avec linux](#n9.2)</br>
&nbsp;&nbsp;&nbsp;&nbsp;[9.3 Programmes de démo pour la carte LPC1766 incompatible avec Eclipse](#n9.3)

<a id="n1"></a>
## 1. Objectif

<p style='text-align: justify;'>
Nous devons programmer et débugger un µC ARM, sur la carte LPC1766 de chez Olimex.</br>
Pour cela nous devons utiliser Eclipse qui est un IDE (Integrated Development Environment) open source.
</p>

<a id="n2"></a>
## 2. Logiciels de développement

<p style='text-align: justify;'>
Afin de rendre opérationnel l'environnement de travail nous devons utiliser plusieurs logiciels car Eclipse n'est qu'un IDE, et n'intègre pas nativement la compilation, le débuggage et la liaison PC/µC.
</p>

Voici les différents logiciels à utiliser :

 - Eclipse CDT : Environnement de développement
 - OpenOCD : On-Chip Debugger
 - Yagarto : Chaine de compilation ARM (Toolchain)
 - Zylin : Extension Eclipse pour le GDB server
 - Zadig : Logiciel d'installation de drivers pour la sonde JTAG

<a id="n3"></a>
## 3. Installation des logiciels

 - Télécharger et installer la dernière version de "Eclipse for Olimex Openocd development suite" à cette adresse : https://www.olimex.com/Products/ARM/JTAG/_resources/OpenOCD/
Cette version intègre tout les logiciels cités ci-dessus, sauf Zadig.
 - Télécharger et installer Zadig à cette adresse : http://zadig.akeo.ie/

<a id="n4"></a>
## 4. Installation des drivers pour la sonde JTAG

<p style='text-align: justify;'>
Nous utilisons la sonde ARM-USB-TINY de chez Olimex, mais les 2 méthodes d'installation reste valable pour d'autres sondes JTAG.
</p>

 - 1ere méthode : Lancer le logiciel Zadig, connecter la sonde JTAG, et installer le driver WinUSB(LibUSB) pour l'interface 0 et 1.
 - 2nd méthode :
  - Connecter la sonde JTAG
  - Ouvrir le gestionnaire de périphériques
  - Installer manuellement les drivers, aller dans le répertoire d'installation "C:\OlimexODS\DRIVERS\olimex-libusb-1.2.2.0"*
  - Opération précèdente à répéter 2 fois pour la sonde ARM-USB-TINY, si une autre sonde est utilisée lire le fichier ReadMe.txt dans le dossier DRIVERS

  /!\ Si windows détecte une erreur de signature de pilote, voir partie 6. /!\

<a id="n5"></a>
## 5. Débug de la carte avec Eclipse

<a id="n5.1"></a>
### 5.1 Lancement d'Openocd

 - Lancer la fenêtre de commande
 - Taper :
  - "cd c:\olimexods\openocd-0.6.1\bin" pour windows 32bits ou
    "cd c:\olimexods\openocd-0.6.1\bin-x64" pour windows 64bits
  - "openocd-0.6.1.exe –f /interface/olimex-jtag-tiny.cfg –f /target/lpc1766.cfg" pour windows 32bits ou
    "openocd-x64-0.6.1.exe –f /interface/olimex-jtag-tiny.cfg –f /target/lpc1766.cfg" pour windows 64bits

Si aucun problème le serveur GDB se lance et la carte est reconnue. Voici le résultat obtenu :

![Alt Text](/images/CMD.png)

<a id="n5.2"></a>
### 5.2 Configuration de Eclipse

- Run->Debug configuration
- Sélectionner l’add-on Zylin Embedded debug (Native)
- Dans l’onglet Main, sélectionner le projet et l’application
- Dans l’onglet Debugger, sélectionner Embedded GDB et l’exécutable du GDB debugger est "arm-none-eabi-gdb.exe" situé dans le dossier \OlimexODS\yagarto\bin
- Dans l’onglet Commande, complétez le champ "run" comme ci-dessous :

	target remote localhost:3333
	monitor reset halt
	monitor wait_halt
	monitor sleep 100
	monitor poll
	monitor load_image main.bin 0x20000000
	monitor sleep 200
	monitor soft_reset_halt
	monitor wait_halt
	monitor reg pc 0x2000010c
	break main
	continue

- Cliquer sur "Apply" puis "Debug", si tout se passe bien le programme se met en attente sur la première ligne

<a id="n5.3"></a>
### 5.3 Moyens de débug

<p style='text-align: justify;'>
Eclipse nous permet en mode debug de pouvoir voir la configuration des registres, la mémoire ainsi que les variables en RAM.
</p>

<a id="n6"></a>
## 6. Débug de la carte avec Keil

<p style='text-align: justify;'>
Keil est un logiciel propriétaire qui intégre l'IDE, le compilateur et le débug.</br>
En mode débug, il permet de vérifier rapidement si les différents registres sont correctements configurés, en nous indiquant par exemple, la vitesse d'une liaison série, si les interruptions sont activées ou non, les configurations des convertisseurs AN et autres ...</br>
On peut aussi, via l'écriture de scripts, simuler par exemple une EEPROM, cela peut être très pratique si nous disposons pas de la carte de développement.
</p>

<a id="n7"></a>
## 7. Avantages et inconvénients entre Eclipse et Keil

![Alt Text](/images/Comparatif.png)

<a id="n8"></a>
## 8. JTAG

<p style='text-align: justify;'>
JTAG pour Joint Test Action Group, est utilisé à la base pour faire des tests de court-circuit et de continuité entre puces compatibles pour vérifier la qualité des pistes et des soudures.</br>
Maintenant cette technique est aussi utilisée pour programmer et débugger les circuits numérique telle que les FPGA et les µC (ICD : In-Circuit-Debugger), mais également pour vérifier et/ou pour programmer des mémoires non volatile (EEPROM, ...).</br>
En mettant plusieurs composants en série compatible avec le JTAG (appelé chaine JTAG) on peut choisir de les programmer individuellement ou simultanément, mais aussi de faire reconnaître cette chaine par les logiciels de programmation.
</p>

Exemple de chaine JTAG : ![Alt Text](/images/jtag-chain.png)

<a id="n9"></a>
## 9. Problèmes rencontrés

<a id="n9.1"></a>
### 9.1 Problème d'installation des pilotes de la sonde JTAG

L'installation des pilotes de la sonde JTAG était bloquée par Windows, voici la méthode pour désactiver le contrôle de la signature des pilotes :

- "menu Démarrer" puis "Paramètres".
- mise à jour et la sécurité.
- récupération.
- Cliquez sur redémarrer maintenant sous démarrage avancé.
- Dépannage.
- options avancées.
- paramètres.
- redémarrer.
- Appuyer sur la touche 7 pour désactiver le contrôle de la signature des pilotes, l'ordinateur redémarre.

<a id="n9.2"></a>
### 9.2 Problème de compatibilité avec linux

<p style='text-align: justify;'>
Certaines sondes JTAG intégrées aux cartes de développement ne sont pas compatibles avec linux, les drivers sont destinés uniquement à windows. Il faut donc utiliser une sonde JTAG externe.
</p>

 <a id="n9.3"></a>
### 9.3 Programmes de démo pour la carte LPC1766 incompatible avec Eclipse

<p style='text-align: justify;'>
Les programmes de démonstration de la carte, téléchargés sur le site Olimex sont des projets IAR Embedded Workbench qui est un logiciel prorpiétaire.</br>
Pour rendre les projets compatible avec Eclipse il faut installer le plugin "IAR Embedded Workbench" dans Eclipse :
</p>

- Ouvrir Eclipse
- Onglet "help" puis "Install new software"
- Entrer l'adresse : http://eclipse-update.iar.com/plugin-manager/1.0
- Puis installer IAR Systems
