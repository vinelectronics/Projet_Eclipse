# Programmation de �C avec Eclipse
## UE : Programmation orient� objet
## Auteurs : FRANCOIS K�vin/ANICIC Jean-Baptiste
## Universit� : INSSET/UPJV - M1SE - Semestre 1

## 1. Objectif :

Nous devons programmer et d�bugger un �C ARM, sur la carte LPC1766 de chez Olimex.
Pour cela nous devons utiliser Eclipse qui est un IDE (Integrated Development Environment) open source.

## 2. Logiciels de d�veloppement :

Afin de rendre op�rationnel l'environnement de travail nous devons utiliser plusieurs logiciels car Eclipse n'est qu'un IDE, et n'int�gre pas nativement la compilation, le d�buggage et la liaison PC/�C.

Voici les diff�rents logiciels � utiliser :

	- Eclipse CDT : Environnement de d�veloppement 
	- OpenOCD : On-Chip Debugger
	- Yagarto : Chaine de compilation ARM (Toolchain)
	- Zylin : Extension eclipse pour le GDB server
	- Zadig : Logiciel d'installation de drivers pour la sonde JTAG

## 3. Installation des logiciels :

	- T�l�charger et installer la derni�re version de "Eclipse for Olimex Openocd development suite" � cette adresse : https://www.olimex.com/Products/ARM/JTAG/_resources/OpenOCD/
          Cette version int�gre tout les logiciels cit�s ci-dessus, sauf Zadig.
	- T�l�charger et installer Zadig � cette adresse : http://zadig.akeo.ie/

## 4. Installation des drivers pour la sonde JTAG :

Nous utilisons la sonde ARM-USB-TINY de chez Olimex, mais les 2 m�thodes d'installation reste valable pour d'autres sondes JTAG.

	- 1ere m�thode : Lancer le logiciel Zadig puis connecter la sonde JTAG, et installer le driver WinUSB(LibUSB) pour l'interface 0 et 1.
	- 2nd m�thode : - Connecter la sonde JTAG
			- Ouvrir le gestionnaire de p�riph�riques 
			- Installer manuellement les drivers, aller dans le r�pertoire d'installation "C:\OlimexODS\DRIVERS\olimex-libusb-1.2.2.0"*
			- Op�ration pr�c�dente � r�p�ter 2 fois pour la sonde ARM-USB-TINY, si une autre sonde est utilis�e lire le fichier ReadMe.txt dans le dossier DRIVERS

		/!\ Si windows d�tecte une erreur de signature de pilote, voir partie 6. /!\

## 5. D�bug de la carte :

	## Avec Eclipse :

	### 5.1 Lancement d'Openocd

		- Lancer la fen�tre de commande
		- Taper : - "cd c:\olimexods\openocd-0.6.1\bin" pour windows 32bits ou 
		    	    "cd c:\olimexods\openocd-0.6.1\bin-x64" pour windows 64bits
			  - "openocd-0.6.1.exe �f /interface/olimex-jtag-tiny.cfg �f /target/lpc1766.cfg" pour windows 32bits ou 
		  	    "openocd-x64-0.6.1.exe �f /interface/olimex-jtag-tiny.cfg �f /target/lpc1766.cfg" pour windows 64bits

Si aucun probl�me le serveur GDB se lance et la carte est reconnue. Voici le r�sultat obtenu :

	C:\Users\K�vin>cd c:\olimexods\openocd-0.6.1\bin-x64

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
		- S�lectionner l�add-on Zylin Embedded debug (Native)
		- Dans l�onglet Main, s�lectionner le projet et l�application
		- Dans l�onglet Debugger, s�lectionner Embedded GDB et l�ex�cutable du GDB debugger est arm-none-eabi-gdb.exe situ� dans le dossier \OlimexODS\yagarto\bin
		- Dans l�onglet Commande, compl�ter le champ run comme ci-dessous :

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
			monitor poll
			break main
			continue

		- Cliquer sur "Apply" puis "Debug", si tout se passe bien le programme se met en attente sur la premi�re ligne

	### 5.3 Moyens de d�bug

	## Avec Keil :

Keil est un logiciel propri�taire qui int�gre l'IDE, le compilateur et le d�bug.
En mode d�bug, il permet de v�rifier rapidement si les diff�rents registres sont correctement configur�s, en nous indiquant par exemple, la vitesse d'une liaison s�rie, si les interruptions sont activ�es ou non, les configurations des convertisseurs AN et autres ...
On peut aussi via l'�criture de scripts simuler par exemple une EEPROM, cela peut �tre tr�s pratique si nous disposont pas de la carte de d�veloppement.

## 6. JTAG :

JTAG pour Joint Test Action Group, est utilis� � la base pour faire des tests de court-circuit et de continuit� entre puces compatibles pour v�rifier la qualit� des pistes et des soudures.
Maintenant cette technique est utilis�e pour programmer et d�bugger les circuits num�rique telle que les FPGA et les �C (ICD : In-Circuit-Debugger), mais aussi de v�rifier et/ou de programmer des m�moires non volatile (EEPROM, ...).
En mettant plusieurs composants en s�rie compatible avec le JTAG (appel� chaine JTAG) on peut choisir de les programmer individuellement ou simultan�ment, mais aussi de faire reconna�tre cette chaine par les logiciels de programmation.
Exemple de chaine JTAG : https://upload.wikimedia.org/wikipedia/commons/thumb/c/c9/Jtag_chain.svg/654px-Jtag_chain.svg.png

## 7. Probl�mes rencontr�s :

	### 7.1 Probl�me d'installation des pilotes de la sonde JTAG

		- "menu D�marrer" puis "Param�tres".
		- mise � jour et la s�curit�.
		- r�cup�ration.
		- Cliquez sur red�marrer maintenant sous d�marrage avanc�.
		- D�pannage.
		- options avanc�es.
		- param�tres.
		- red�marrer.
		- Appuyer sur la touche 7 pour d�sactiver le contr�le de la signature des pilotes, l'ordinateur red�marre.

	### 7.2 Probl�me de compatibilit� avec linux

		Certaine sonde JTAG int�gr� aux cartes de d�vellopement ne sont pas compatible avec linux, les drivers sont fournit uniquement pour windows. Il faut donc utiliser une sonde JTAG externe.

	### 7.3 Programmes de d�mo pour la carte LPC1766 incompatible avec Eclipse

Les programmes de d�monstration de la carte, t�l�charg�s sur le site Olimex sont des projets IAR Embedded Workbench qui est un logiciel prorpi�taire.
Pour rendre les projets compatible avec Eclipse suivre les instructions suivantes /

		- Ouvrir Eclipse
		- Onglet "help" puis "Install new software"
		- Entrer l'adresse : http://eclipse-update.iar.com/plugin-manager/1.0
		- Puis installer IAR Systems


