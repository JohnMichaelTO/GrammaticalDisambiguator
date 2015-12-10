	----------------------------
	| L3 C TP LC2  - MORA - TO |
	----------------------------
	
	Ce fichier est à lire de préférence sous Notepad++
	
	Auteurs
	-------
	
		Benjamin MORA
		John-Michaël TO
	
	Dates
	---------------
	
		Début 	:	07/01/2014
		Fin 	:	08/01/2014
	
	Préambule
	---------
	
		Dans le cadre du TP n°2 de Langages et Compilation,
		nous devions réaliser en C/C++ un désambigueur grammatical.
	
	Représentation du symbole "epsilon"
	------------------------------------
	
		La console ne nous permet pas d'utiliser simplement le caractère "epsilon",
		c'est pourquoi, nous avons décidé de représenter ce caractère par un dièse "#".
		
	Détail des fichiers
	-------------------
	
		README.txt						Ce fichier
		main.cpp						Fichier source en C++
	
	Aide à la compilation
	---------------------

		1)	Au préalable, se munir de Code Blocks 12.11 (dernière version actuelle) sur un PC Windows

		2)	De préférence, la compilation doit se faire sous GNU GCC Compiler

		3)	Ouvrir le fichier main.cpp
		
		3)	Compiler le fichier sous Code Blocks, l'exécutable devrait se trouver directement dans le répertoire courant
	
	Compatibilité
	-------------
	
		Ce programme a été testé et compilé à partir de Code Blocks 12.11 sous Windows 7.
		Des disfonctionnements ne sont pas négligeables sous une autre version de Code Blocks et/ou du système d'exploitation.
		
	Etat d'avancement
	-----------------
	
		- Structure de données choisie		Fait
		- Lecture de fichier				Fait
		- Ecriture de fichier				Fait
		- Récursivité gauche directe		Fait
		- Récursivité gauche indirecte		Fait
		- Factorisation à gauche			Fait
	
	Références & Sources
	--------------------
	
		- Dragon Book, sections 4.3.3 et 4.3.4 (pages 195-197)
		- http://fr.wikipedia.org/wiki/Récursivité gauche
		- http://www.linguist.jussieu.fr/~amsili/Ens06/poly-li324-1.pdf
		- https://madelaine.users.greyc.fr/l3/langetcompil/2012/CM4.pdf
		- http://lipn.univ-paris13.fr/~guerrini/old/Compil/support/2.AnSynt.pdf
	
	Fonctionnalités optionnelles
	----------------------------
	
		- Affichage des règles de la grammaire amélioré
		- Choix pour l'enregistrement du fichier à générer
		- Génération d'un fichier de traces d'exécution du programme (traces.txt)
	