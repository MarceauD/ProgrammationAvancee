#include <stdio.h>
#include <stdlib.h>
#include "h/file.h"
#include <time.h>//pr faire un random
	int Level; //on déclare le niveau
	
	if (Level == 1)
	{
		int Left = 500; // on dit qu'en tout on a 500 ennemis à gauche
		
	}
	
	fighter *enemy;
	
	/*on défini le type d'ennemis, ici par exemple notre type 1 c'est ce qu'on a pr l'instant*/
	enemy[1] = init_fighter(1);//init_fighter(0) c'est le personnage au cas ou


	/*on initialise notre file*/
    File *enemysLeft = initialiser();
	
	While (Left)//tant qu'on a des ennemis dans ce niveau
	{
		//on enfile 500 ennemis (de type 1 pr l'instant), on mettra le reste soit aleatoirement ou on verra...
		enfiler(enemysLeft, enemy[1]);
		Left--;
	}
	
	//on a maintenant notre file d'ennemis prete à etre déssinée
	int alea_ennemy; // variable aleatoire
	int relancer  = 1;//relancer des ennemis
	srand(time(NULL)); /*to randomize the colors*/
	alea_ennemy=rand() % 3;// qui servira a envoyer par exemple si c'est 2: deux ennemis à la fois à gauche, maximum 3
	
	while (ennemysLeft != NULL)	//tant qu'on a notre file d'ennemis, ici 500
	{
		while (alea_ennemy)//tant qu'on a notre nombre aleatoire a afficher
		{	
			//on dessine l'ennemi
			if(isAlive(premFile(enemysLeft)))
			{
    			SDL_BlitSurface((tete(enemysLeft).sprite),&(tete(enemysLeft).source),screen,&(tete(enemysLeft).rcSprite));
			}
			if(!isAlive(premFile(enemysLeft)))
			{
				relancer++;
			}
			//on l'enleve de la file
			defiler(ennemysLeft);
			//et on incrémente alea_ennemy
			if (relancer == alea_enemy)
			{
				alea_enemy = 0;
			}
		}
		alea_ennemy=rand() % 3;//on refait un random pour relancer des ennemis
	}
	



