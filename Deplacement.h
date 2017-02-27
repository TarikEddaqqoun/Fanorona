#ifndef DEPLACEMENT_H_INCLUDED
#define DEPLACEMENT_H_INCLUDED

void find_pos(Uint16 xp, Uint16 yp,int *x_res,int *y_res);
// retourne la direction de capture
int dir_capt(int a,int b, int c, int d);
// retourne 1 s'il exist une capturation
int capturation_exist(int a,int b);
// permet de capturer plusieurs pions adjacents
void capturer_plusieurs(int a2,int b2,int a_temp,int b_temp,SDL_Rect pos1[]);
// trace une croit sur les choix possibles de capturations s'ils existent plusieurs
void tracer_choix(int a2,int b2,int a_temp,int b_temp,SDL_Rect pos1[],SDL_Surface *capture);
// retourne 1 si si le deplacement est possible return 0 sinon
int deplacement_est_possible(int a, int b,int a2,int b2);
// Capture 1 pion
void capturer(int a,int b,SDL_Rect pos[]);
// retourne la direction de capture
int dir_capt(int a,int b, int c, int d);

/* fonction qui retourne 0 s'il n y a rien a capturer
    et retoune -1 s'il existe une capturation derrier ,
    retourne 1 s'il exsiste une capturation en avant, et 2 s'il existe 2 capturations*/
int capturations_possibles(int a,int b,int a2,int b2);
// Combine les fonctions précedentes pour gérrer le déplacement d'un pion par l'utlisateur
void deplacer_pion(SDL_Surface *pions[],SDL_Surface *pions1[],SDL_Rect pos[],SDL_Rect pos1[] ,Uint16 x0,Uint16 y0,int k,int *capt,int *xprec,int *yprec);
// Combine les fonctions précédentes pour gérrer le déplacement en mode 1 joueur en difficulté facile
void deplacer_pion_machine(SDL_Surface *pions[],SDL_Surface *pions1,SDL_Rect pos[],SDL_Rect pos1[]);
// retounre le nombre de pions possibles à capturer pour déplacement
int nombre_captures(int x,int y,int next_x,int next_y);
// permet de calculer le maximum des captures possibles et enregistre le déplacement correspondant
void calcul_max_capture(int x_pion,int y_pion,int x_next,int y_next,int *max,int *x_dest,int *y_dest,int *a,int *b);
// Permet de déterminer la position auquelle le pion ne sera pas capturé
int safe_to_move(int x_pion,int y_pion,int x,int y);
// Combine les fonctions précédentes pour déplacer les pions en mode 1 joueur en difficulté normal
void deplacer_pion_machine2(SDL_Surface *pions[],SDL_Surface *pions1,SDL_Rect pos[],SDL_Rect pos1[]);
// Retourne 1 s'il est obligé de capturé 0 sinon
int doit_capturer(int tour);

#endif
