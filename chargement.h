#ifndef CHARGEMENT_H_INCLUDED
#define CHARGEMENT_H_INCLUDED

/* Cette procedure permet de charger les surfaces des pions */
void charger_pions(SDL_Surface *pions_noir[],SDL_Surface *pions_blnc[],SDL_Rect pos_noir[],SDL_Rect pos_blanc[],int x,int y,int board_w, int board_h);
/* Cette procedure permet d'initialiser la grille */
void initialiser_board();
/* Cette procedure permet d'initilaiser la grille temporaire */
void rem_bet();
/*Cette fonction retourn la valeur de l'option choisie dans le menu du démarrage*/
int start_menu();
/*Cette procedure est le menu de la fin de partie*/
void finpartie_menu(int *rejouer,int *test);
/*Cette fonction affiche le menu le choix de difficulté*/
int choisir_diff();
#endif
