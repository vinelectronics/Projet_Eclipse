﻿# Sujet : Programmation de µC avec Eclipse
#### UE : Programmation orienté objet
#### Auteurs : FRANCOIS Kévin/ANICIC Jean-Baptiste
#### Université : INSSET/UPJV - M1SE - Semestre 1

## 1. Objectif :

<p style='text-align: justify;'>
Nous devons programmer et débugger un µC ARM, sur la carte LPC1766 de chez Olimex.
Pour cela nous devons utiliser Eclipse qui est un IDE (Integrated Development Environment) open source.
</p>

## 2. Logiciels de développement :

<p style='text-align: justify;'>
Afin de rendre opérationnel l'environnement de travail nous devons utiliser plusieurs logiciels car Eclipse n'est qu'un IDE, et n'intègre pas nativement la compilation, le débuggage et la liaison PC/µC.
</p>

Voici les différents logiciels à utiliser :

 - Eclipse CDT : Environnement de développement 
 - OpenOCD : On-Chip Debugger
 - Yagarto : Chaine de compilation ARM (Toolchain)
 - Zylin : Extension eclipse pour le GDB server
 - Zadig : Logiciel d'installation de drivers pour la sonde JTAG

## 3. Installation des logiciels :

 - Télécharger et installer la dernière version de "Eclipse for Olimex Openocd development suite" à cette adresse : https://www.olimex.com/Products/ARM/JTAG/_resources/OpenOCD/
Cette version intègre tout les logiciels cités ci-dessus, sauf Zadig.
 - Télécharger et installer Zadig à cette adresse : http://zadig.akeo.ie/

## 4. Installation des drivers pour la sonde JTAG :

<p style='text-align: justify;'>
Nous utilisons la sonde ARM-USB-TINY de chez Olimex, mais les 2 méthodes d'installation reste valable pour d'autres sondes JTAG.
</p>

 - 1ere méthode : Lancer le logiciel Zadig puis connecter la sonde JTAG, et installer le driver WinUSB(LibUSB) pour l'interface 0 et 1.
 - 2nd méthode : 
  - Connecter la sonde JTAG
  - Ouvrir le gestionnaire de périphériques 
  - Installer manuellement les drivers, aller dans le répertoire d'installation "C:\OlimexODS\DRIVERS\olimex-libusb-1.2.2.0"*
  - Opération précèdente à répéter 2 fois pour la sonde ARM-USB-TINY, si une autre sonde est utilisée lire le fichier ReadMe.txt dans le dossier DRIVERS

  /!\ Si windows détecte une erreur de signature de pilote, voir partie 6. /!\

## 5. Débug de la carte avec eclipse:

### 5.1 Lancement d'Openocd

 - Lancer la fenêtre de commande
 - Taper : 
  - "cd c:\olimexods\openocd-0.6.1\bin" pour windows 32bits ou   
    "cd c:\olimexods\openocd-0.6.1\bin-x64" pour windows 64bits
  - "openocd-0.6.1.exe –f /interface/olimex-jtag-tiny.cfg –f /target/lpc1766.cfg" pour windows 32bits ou   
    "openocd-x64-0.6.1.exe –f /interface/olimex-jtag-tiny.cfg –f /target/lpc1766.cfg" pour windows 64bits

Si aucun problème le serveur GDB se lance et la carte est reconnue. Voici le résultat obtenu :

	C:\Users\Kévin>cd c:\olimexods\openocd-0.6.1\bin-x64

	c:\OlimexODS\openocd-0.6.1\bin-x64>openocd-x64-0.6.1.exe -f /interface/olimex-jtag-tiny.cfg -f /target/lpc1766.cfg
	Open On-Chip Debugger 0.6.1 (2012-10-07-10:39)
	Licensed under GNU GPL v2
	For bug reports, read
       		http://openocd.sourceforge.net/doc/doxygen/bugs.html
	Info : only one transport option; autoselect 'jtag'
	adapter_nsrst_delay: 200
	jtag_ntrst_delay: 200
	adapter speed: 10 kHz
	cortex_m3 reset_config vectreset
	Info : clock speed 10 kHz
	Info : JTAG tap: lpc1766.cpu tap/device found: 0x4ba00477 (mfg: 0x23b, part: 0xba00, ver: 0x4)
	Info : lpc1766.cpu: hardware has 6 breakpoints, 4 watchpoints

### 5.2 Configuration de Eclipse
	
- Run->Debug configuration
- Sélectionner l’add-on Zylin Embedded debug (Native)
- Dans l’onglet Main, sélectionner le projet et l’application
- Dans l’onglet Debugger, sélectionner Embedded GDB et l’exécutable du GDB debugger est arm-none-eabi-gdb.exe situé dans le dossier \OlimexODS\yagarto\bin
- Dans l’onglet Commande, compléter le champ run comme ci-dessous :

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

### 5.3 Moyens de débug

## 6. Débug de la carte avec Keil :

<p style='text-align: justify;'>
Keil est un logiciel propriétaire qui intégre l'IDE, le compilateur et le débug.  
En mode débug, il permet de vérifier rapidement si les différents registres sont correctement configurés, en nous indiquant par exemple, la vitesse d'une liaison série, si les interruptions sont activées ou non, les configurations des convertisseurs AN et autres ...  
On peut aussi via l'écriture de scripts simuler par exemple une EEPROM, cela peut être très pratique si nous disposont pas de la carte de développement.  
</p>

## 7. JTAG :
<p style='text-align: justify;'>
JTAG pour Joint Test Action Group, est utilisé à la base pour faire des tests de court-circuit et de continuité entre puces compatibles pour vérifier la qualité des pistes et des soudures.  
Maintenant cette technique est utilisée pour programmer et débugger les circuits numérique telle que les FPGA et les µC (ICD : In-Circuit-Debugger), mais aussi de vérifier et/ou de programmer des mémoires non volatile (EEPROM, ...).  
En mettant plusieurs composants en série compatible avec le JTAG (appelé chaine JTAG) on peut choisir de les programmer individuellement ou simultanément, mais aussi de faire reconnaître cette chaine par les logiciels de programmation.
</p>

Exemple de chaine JTAG : ![alt text](C:\Users\Kévin\Documents\GitHub\Projet_Eclipse\images\jtag-chain.png)

## 8. Problèmes rencontrés :

### 8.1 Problème d'installation des pilotes de la sonde JTAG

- "menu Démarrer" puis "Paramètres".
- mise à jour et la sécurité.
- récupération.
- Cliquez sur redémarrer maintenant sous démarrage avancé.
- Dépannage.
- options avancées.
- paramètres.
- redémarrer.
- Appuyer sur la touche 7 pour désactiver le contrôle de la signature des pilotes, l'ordinateur redémarre.

### 8.2 Problème de compatibilité avec linux

<p style='text-align: justify;'>
Certaine sonde JTAG intégré aux cartes de dévellopement ne sont pas compatible avec linux, les drivers sont fournit uniquement pour windows. Il faut donc utiliser une sonde JTAG externe.
</p>

### 8.3 Programmes de démo pour la carte LPC1766 incompatible avec Eclipse

<p style='text-align: justify;'>
Les programmes de démonstration de la carte, téléchargés sur le site Olimex sont des projets IAR Embedded Workbench qui est un logiciel prorpiétaire.   
Pour rendre les projets compatible avec Eclipse suivre les instructions suivantes :
</p>

- Ouvrir Eclipse
- Onglet "help" puis "Install new software"
- Entrer l'adresse : http://eclipse-update.iar.com/plugin-manager/1.0
- Puis installer IAR Systems
