	----------------------------
	| L3 C TP LC2  - MORA - TO |
	----------------------------
	
	Ce fichier est � lire de pr�f�rence sous Notepad++
	
	Auteurs
	-------
	
		Benjamin MORA
		John-Micha�l TO
	
	Dates
	---------------
	
		D�but 	:	07/01/2014
		Fin 	:	08/01/2014
	
	Pr�ambule
	---------
	
		Dans le cadre du TP n�2 de Langages et Compilation,
		nous devions r�aliser en C/C++ un d�sambigueur grammatical.
	
	Repr�sentation du symbole "epsilon"
	------------------------------------
	
		La console ne nous permet pas d'utiliser simplement le caract�re "epsilon",
		c'est pourquoi, nous avons d�cid� de repr�senter ce caract�re par un di�se "#".
		
	D�tail des fichiers
	-------------------
	
		README.txt						Ce fichier
		main.cpp						Fichier source en C++
	
	Aide � la compilation
	---------------------

		1)	Au pr�alable, se munir de Code Blocks 12.11 (derni�re version actuelle) sur un PC Windows

		2)	De pr�f�rence, la compilation doit se faire sous GNU GCC Compiler

		3)	Ouvrir le fichier main.cpp
		
		3)	Compiler le fichier sous Code Blocks, l'ex�cutable devrait se trouver directement dans le r�pertoire courant
	
	Compatibilit�
	-------------
	
		Ce programme a �t� test� et compil� � partir de Code Blocks 12.11 sous Windows 7.
		Des disfonctionnements ne sont pas n�gligeables sous une autre version de Code Blocks et/ou du syst�me d'exploitation.
		
	Etat d'avancement
	-----------------
	
		- Structure de donn�es choisie		Fait
		- Lecture de fichier				Fait
		- Ecriture de fichier				Fait
		- R�cursivit� gauche directe		Fait
		- R�cursivit� gauche indirecte		Fait
		- Factorisation � gauche			Fait
	
	R�f�rences & Sources
	--------------------
	
		- Dragon Book, sections 4.3.3 et 4.3.4 (pages 195-197)
		- http://fr.wikipedia.org/wiki/R�cursivit� gauche
		- http://www.linguist.jussieu.fr/~amsili/Ens06/poly-li324-1.pdf
		- https://madelaine.users.greyc.fr/l3/langetcompil/2012/CM4.pdf
		- http://lipn.univ-paris13.fr/~guerrini/old/Compil/support/2.AnSynt.pdf
	
	Fonctionnalit�s optionnelles
	----------------------------
	
		- Affichage des r�gles de la grammaire am�lior�
		- Choix pour l'enregistrement du fichier � g�n�rer
		- G�n�ration d'un fichier de traces d'ex�cution du programme (traces.txt)
	