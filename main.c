#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include "chargement.h"
#include "variable.h"
#include "deplacement.h"

double err=0.05; // erreur tolérée pour le clic du joueur sur un pion
int board_x=184,board_y=192,board_h=381,board_w=980; // position et dimension de la grille du jeu



int main(int argc,char *argv[])
{

    int i,j;

    pos_board.x=0;
    pos_board.y=0;

    pos.x=800;
    pos.y=600;

    pos_tr1.x=200;
    pos_tr1.y=600;

    pos_tr2.x=200;
    pos_tr2.y=60;

    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO); // initialisation de SDL
    ecran=SDL_SetVideoMode(1366,766,32,SDL_HWSURFACE | SDL_DOUBLEBUF|SDL_FULLSCREEN);

    //Chargement des images;
    board=IMG_Load("images/board.jpg");
    pion_passe=IMG_Load("images/pion_passe.png");
    fin1=IMG_Load("images/fin1.png");
    fin2=IMG_Load("images/fin2.png");
    difficulte=IMG_Load("images/diff.jpg");
    white_transparent=IMG_Load("images/white_transparant.png");
    indicateur_tour1=IMG_Load("images/tr_noir.png");
    indicateur_tour2=IMG_Load("images/tr_blanc.png");

    jouer = 1;
    int rejouer=1;
    while(jouer)
    {

    initialiser_board(); // On initialise la matrice  board_etat
    int xres,yres;
    tour=rand()%2;     // variable pour savoir le tour de quel joueur
    int capt=0;       // bool temporaire s' il a capturé
    acapt=0;     // bool s'il a capturé quelque chose le tour précedent
    int xprec,yprec; // position du pion qui a deja  capturer pour faire une capturation multiple
    rem_bet(); // initialiser la matrice board_etat_temporaire
    dir=0; // initialiser la variable de direction
    test=1; // bool la boucle du jeu
    SDL_Event event; // l'evenement principale du jeu
    charger_pions(pions_noir,pions_blanc,pos_noir,pos_blanc,board_x,board_y,board_w,board_h);// charger les images des pions et les placer dans leurs positions
    // initialiser le nombre de pions
    n_blanc=22;
    n_noir=22;
    int diff;

    if (rejouer) mode_jeu=start_menu();// si l'utilisateur choisi de rejoeur on commence dirrectement le jeu sans changer le mode_jeu
    if(mode_jeu==1) diff=choisir_diff();
    afficher_tour();
    if(tour==1)         // si c'est l'ordinateur qui commence on doit afficher les surfaces et utiliser
                        // la fonction sleep pour montrer le mouvement de l'ordinateur
    {
        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
        SDL_BlitSurface(board,NULL,ecran,&pos_board);

        if(tour%2==0)SDL_BlitSurface(indicateur_tour1,NULL,ecran,&pos_tr1);
        else  SDL_BlitSurface(indicateur_tour2,NULL,ecran,&pos_tr2);

        for(i=0;i<22;i++) SDL_BlitSurface(pions_noir[i],NULL,ecran,&pos_noir[i]);
        for(i=0;i<22;i++) SDL_BlitSurface(pions_blanc[i],NULL,ecran,&pos_blanc[i]);

        SDL_Flip(ecran);

        Sleep(1000);

        if(mode_jeu==1 && tour%2==1 && diff==1)
        {
            deplacer_pion_machine(pions_blanc,pions_noir,pos_blanc,pos_noir);
            tour++,acapt=0,dir=0,rem_bet();
        }
        else if(mode_jeu==1 && tour%2==1 && diff==2)
        {
            deplacer_pion_machine2(pions_blanc,pions_noir,pos_blanc,pos_noir);
            tour++,acapt=0,dir=0,rem_bet();
        }
    }
    while(test)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                test=0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:           // si le joueur a cliqué sur espace pour passer son tour
                        test=0,rejouer=1;
                        break;
                    case SDLK_SPACE:
                        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                        SDL_BlitSurface(board,NULL,ecran,&pos_board);

                        if(tour%2==0)SDL_BlitSurface(indicateur_tour1,NULL,ecran,&pos_tr1);
                        else  SDL_BlitSurface(indicateur_tour2,NULL,ecran,&pos_tr2);

                        for(i=0;i<22;i++) SDL_BlitSurface(pions_noir[i],NULL,ecran,&pos_noir[i]);
                        for(i=0;i<22;i++) SDL_BlitSurface(pions_blanc[i],NULL,ecran,&pos_blanc[i]);
                        SDL_Flip(ecran);
                        Sleep(500);
                        if(acapt)
                        {
                            tour++,acapt=0,dir=0,rem_bet();
                        }
                        if(mode_jeu==1 && tour%2==1 && diff==1)
                        {
                            deplacer_pion_machine(pions_blanc,pions_noir,pos_blanc,pos_noir);
                            tour++,acapt=0,dir=0,rem_bet();
                        }
                        else if(mode_jeu==1 && tour%2==1 && diff==2)
                        {
                            deplacer_pion_machine2(pions_blanc,pions_noir,pos_blanc,pos_noir);
                            tour++,acapt=0,dir=0,rem_bet();
                        }
                        break;
                }

                break;
            case SDL_MOUSEBUTTONDOWN:

                find_pos(event.button.x,event.button.y,&xres,&yres);

                if(acapt) // s'il a capturé qlq chose le tour précedent
                {
                    if(xres!=xprec || yres!=yprec) // s'il le joueur a cliqué sur un autre pion que celui qui a capturé le tour précedent
                    continue;
                }
                int board_etat_temp=board_etat[xres][yres];
                capt=0;
                if (tour%2==0) {
                        int k=board_etat[xres][yres];
                        deplacer_pion(pions_noir,pions_blanc,pos_noir,pos_blanc,event.button.x,event.button.y,board_etat[xres][yres],&capt,&xprec,&yprec);
                        if (capt) dir=dir_capt(xres,yres,xprec,yprec);
                        if (board_etat[xres][yres]==0 && board_etat_temp>0 && !capt) tour++,acapt=0,dir=0,rem_bet();
                        else if(capt && !capturation_exist(xprec,yprec)) acapt=0,tour++,dir=0,rem_bet(); // s'il a capturé qlq chose mais il n'as plus de capture possible
                        else if(capt && capturation_exist(xprec,yprec))
                        {
                            acapt=1;        // le joueur a capturé
                            board_etat_temporaire[xres][yres]=1; // enregistrer la position du pion pour qu'il ne passe plus par cette case
                        }
                }
                else if (tour%2==1 && mode_jeu==2) {
                        deplacer_pion(pions_blanc,pions_noir,pos_blanc,pos_noir,event.button.x,event.button.y,board_etat[xres][yres],&capt,&xprec,&yprec);
                        if(capt) dir=dir_capt(xres,yres,xprec,yprec);
                        if (board_etat[xres][yres]==0 && board_etat_temp<0 && !capt) tour++,acapt=0,dir=0,rem_bet();
                        else if(capt && !capturation_exist(xprec,yprec)) {acapt=0,dir=0,tour++,rem_bet();}
                        else if(capt && capturation_exist(xprec,yprec))
                        {
                            acapt=1;
                            board_etat_temporaire[xres][yres]=1;
                        }
                }
                break;
        }

        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
        SDL_BlitSurface(board,NULL,ecran,&pos_board);
        if(tour%2==0)SDL_BlitSurface(indicateur_tour1,NULL,ecran,&pos_tr1);
        else if(mode_jeu==2)  SDL_BlitSurface(indicateur_tour2,NULL,ecran,&pos_tr2);

        for(i=0;i<22;i++) SDL_BlitSurface(pions_noir[i],NULL,ecran,&pos_noir[i]);
        for(i=0;i<22;i++) SDL_BlitSurface(pions_blanc[i],NULL,ecran,&pos_blanc[i]);
        for(i=0;i<5;i++)
        {
            for(j=0;j<9;j++)
            {
                if(board_etat_temporaire[i][j]==1)
                {
                    ppasse.x=board_x+(j)*board_w/8-35;
                    ppasse.y=board_y+(i)*board_h/4-35;
                    SDL_BlitSurface(pion_passe,NULL,ecran,&ppasse);
                }
            }
        }
        if (!n_noir || !n_blanc) SDL_BlitSurface(white_transparent,NULL,ecran,&pos_board);
        if(!n_noir) {

                SDL_BlitSurface(fin2,NULL,ecran,&pos_board);  // Les blancs ont gagné
                SDL_Flip(ecran);
        }
        if(!n_blanc) {

                SDL_BlitSurface(fin1,NULL,ecran,&pos_board); // Les noirs ont gagné
                SDL_Flip(ecran);

        }
        if (!n_noir || !n_blanc) finpartie_menu(&rejouer,&test); // Afficher le gagnant et le menu pour rejouer, revenir au menu principal ou bien quitter

        SDL_Flip(ecran);

    }

    }
    SDL_FreeSurface(board);
    for(i=0;i<22;i++) SDL_FreeSurface(pions_blanc[i]);
    for(i=0;i<22;i++) SDL_FreeSurface(pions_noir[i]);
    SDL_FreeSurface(pion_passe);
    SDL_Quit();

    return 0;
}
