#ifndef VARIABLE_H_INCLUDED
#define VARIABLE_H_INCLUDED
//Les surfaces SDL
SDL_Surface *ecran;
SDL_Surface *menu;
SDL_Surface *regles[4];
SDL_Surface *fin1, *fin2;
SDL_Surface *white_transparent;
SDL_Surface *difficulte;
SDL_Surface *j1,*j2;
SDL_Surface *indicateur_tour1,*indicateur_tour2;
SDL_Surface *board;
SDL_Surface *pions_blanc[22];
SDL_Surface *pions_noir[22];
SDL_Surface *pion_passe;
//Les positions SDL
SDL_Rect pos;
SDL_Rect pos_tr1;
SDL_Rect pos_noir[22];
SDL_Rect pos_blanc[22];
SDL_Rect pos_board;
SDL_Rect pos_tr2;
SDL_Rect ppasse;
int board_etat[5][9];// La matrice principale du jeu
int board_etat_temporaire[5][9];// Matrice temporaire qui enregistre les intersections deja empruntées par un pion
double err; //Précision du clique sur un pion
int board_x,board_y,board_h,board_w; // Dimensions de la table
int dir;//stock la direction de capturation précedente
int tour;
int acapt;// Vaut 0 si le joeur n'as pas capturé dans le tour précédent 1 sinon
// des booléens
int jouer;
int test;
// nombre de pions
int n_blanc;
int n_noir;
// mode de jeu : 2 joueurs / 1 joueur
int mode_jeu;
#endif
