#include <SDL/SDL.h>
#include <SDL_image.h>
#include "chargement.h"
#include "variable.h"

void initialiser_board() /* initialiser la matrice board_etat par les indices des pions, négatifs pour les blancs et positifs pour les noirs */
{
    int i=1;
    for (i=0;i<18;i++){
        board_etat[4-i/9][i%9]=i+1; /* On pose les pions noir */
        board_etat[i/9][i%9]=-(i+1);/* On pose les pions blancs */
    }
    /* Cette partie pose les pions blancs et noirs dans la ligne millieu de la grille */
    board_etat[2][0]=-19;
    board_etat[2][1]=19;
    board_etat[2][2]=-20;
    board_etat[2][3]=20;
    board_etat[2][4]=0;
    board_etat[2][5]=-21;
    board_etat[2][6]=21;
    board_etat[2][7]=-22;
    board_etat[2][8]=22;

}

void rem_bet()
{
    int i,j;
    for(i=0;i<5;i++)
    {
        for(j=0;j<9;j++) board_etat_temporaire[i][j]=0;
    }
}

void charger_pions(SDL_Surface *pions_noir[],SDL_Surface *pions_blanc[],SDL_Rect pos_noir[],SDL_Rect pos_blanc[],int x,int y,int board_w, int board_h)
{

    int i;
    int dist_w = board_w/8;
    int dist_h = board_h/4;

    for (i=0;i<9;i++){
        pions_blanc[i]=IMG_Load("images/pion_blanc.png");
        pos_blanc[i].x=x+i*(dist_w)-35;
        pos_blanc[i].y=y-35;
    }
    for(i=9;i<18;i++)
    {
        pions_blanc[i]=IMG_Load("images/pion_blanc.png");
        pos_blanc[i].x=x+(i-9)*dist_w-35;
        pos_blanc[i].y=y+dist_h-35;
    }
    for(i=0;i<9;i++)
    {
        pions_noir[i]=IMG_Load("images/pion_noir.png");
        pos_noir[i].x=x+i*dist_w-35;
        pos_noir[i].y=y+4*dist_h-35;
    }
    for(i=9;i<18;i++)
    {
        pions_noir[i]=IMG_Load("images/pion_noir.png");
        pos_noir[i].x=x+(i-9)*dist_w-35;
        pos_noir[i].y=y+3*dist_h-35;
    }

    pions_noir[18]=IMG_Load("images/pion_noir.png");
    pos_noir[18].x=x+(19-18)*dist_w-35;
    pos_noir[18].y=y+2*dist_h-35;

    pions_noir[19]=IMG_Load("images/pion_noir.png");
    pos_noir[19].x=x+(21-18)*dist_w-35;
    pos_noir[19].y=y+2*dist_h-35;

    pions_noir[20]=IMG_Load("images/pion_noir.png");
    pos_noir[20].x=x+(24-18)*dist_w-35;
    pos_noir[20].y=y+2*dist_h-35;

    pions_noir[21]=IMG_Load("images/pion_noir.png");
    pos_noir[21].x=x+(26-18)*dist_w-35;
    pos_noir[21].y=y+2*dist_h-35;

    pions_blanc[18]=IMG_Load("images/pion_blanc.png");
    pos_blanc[18].x=x-35;
    pos_blanc[18].y=y+2*dist_h-35;

    pions_blanc[19]=IMG_Load("images/pion_blanc.png");
    pos_blanc[19].x=x+(20-18)*dist_w-35;
    pos_blanc[19].y=y+2*dist_h-35;

    pions_blanc[20]=IMG_Load("images/pion_blanc.png");
    pos_blanc[20].x=x+(23-18)*dist_w-35;
    pos_blanc[20].y=y+2*dist_h-35;

    pions_blanc[21]=IMG_Load("images/pion_blanc.png");
    pos_blanc[21].x=x+(25-18)*dist_w-35;
    pos_blanc[21].y=y+2*dist_h-35;

}

void finpartie_menu(int *rejouer,int *test){
        SDL_Event finpartie;
        int check_menu_finpartie=1;
        while (check_menu_finpartie){

                    SDL_WaitEvent(&finpartie);
                    switch (finpartie.type){
                        case SDL_QUIT:
                            check_menu_finpartie=0;
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if (finpartie.button.x>365 && finpartie.button.x<985 && finpartie.button.y>315 && finpartie.button.y<375){
                                // l'utilisateur décide de rejouer
                                check_menu_finpartie=0;
                                *rejouer=0;
                                *test=0;
                            }
                            if (finpartie.button.x>365 && finpartie.button.x<985 && finpartie.button.y>390 && finpartie.button.y<455){
                                // l'utilisateur décide de revenir au menu
                                check_menu_finpartie=0;
                                *test=0;
                                *rejouer=1;
                            }
                            if (finpartie.button.x>365 && finpartie.button.x<985 && finpartie.button.y>475 && finpartie.button.y<535){
                                // l'utilisateur décide de quiter le jeu
                                exit(0);
                            }
                            break;

                    }
            }
}


int start_menu()
{
    menu=IMG_Load("images/menu.jpg");
    regles[0]=IMG_Load("images/presentation.jpg");
    regles[1]=IMG_Load("images/deplacement.jpg");
    regles[2]=IMG_Load("images/capture.jpg");
    regles[3]=IMG_Load("images/capture_multiple.jpg");

    test=1;

    SDL_Event event_menu;

    int t=1;
    int x,y;
    while(t)
    {
        SDL_WaitEvent(&event_menu);
        switch(event_menu.type)
        {
            case SDL_QUIT:
                t=0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                x=event_menu.button.x,y=event_menu.button.y;
                if(x>285 && x<1050 && y>595 && y<665) {exit(0);}
                else if(x>285 && x<1050 && y>385 && y<455) {return 2;}
                else if (x>285 && x<1050 && y>285 && y<355 ) {return 1;}
                else if (x>285 && x<1050 && y>485 && y<555)
                {
                    int page=0,retour=0;
                    SDL_Event event_regles;
                    int x2,y2;
                    while(!retour)
                    {
                        SDL_WaitEvent(&event_regles);
                        switch(event_regles.type){
                        case SDL_MOUSEBUTTONDOWN:
                            x2=event_regles.button.x,y2=event_regles.button.y;
                            if(x2>15 && x2<400 && y2>675 && y2<745)
                            {
                                if(!page) retour=1;
                                else page--;
                            }
                            else if(x2>965 && x2<1355 && y2>675 && y2<745)
                            {
                                if(page==3) retour=1;
                                else page++;
                            }
                            break;
                        }
                        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                        SDL_BlitSurface(regles[page],NULL,ecran,&pos_board);
                        SDL_Flip(ecran);
                    }
                }
                break;

        }
        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
        SDL_BlitSurface(menu,NULL,ecran,&pos_board);
        SDL_Flip(ecran);
    }
}

void afficher_tour()
{
    j1=IMG_Load("images/j1.jpg");
    j2=IMG_Load("images/j2.jpg");

    SDL_Event event_menu;

    int t=1;

    while(t)
    {
        SDL_WaitEvent(&event_menu);
        switch(event_menu.type)
        {
            case SDL_QUIT:
                t=0;
                break;
            case SDL_KEYDOWN:
                switch(event_menu.key.keysym.sym)
                {
                    case SDLK_RETURN:
                        t=0;
                        break;
                }


            break;

        }
        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
        if(tour==0) SDL_BlitSurface(j1,NULL,ecran,&pos_board);
        else SDL_BlitSurface(j2,NULL,ecran,&pos_board);
        SDL_Flip(ecran);
    }

}

int choisir_diff()
{
    test=1;

    SDL_Event event_menu;

    int t=1;
    int x,y;
    while(t)
    {
        SDL_WaitEvent(&event_menu);
        switch(event_menu.type)
        {
            case SDL_QUIT:
                t=0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                x=event_menu.button.x,y=event_menu.button.y;

                if(x>325 && x<1020 && y>405 && y<505) {return 1;}
                else if (x>325 && x<1020 && y>595 && y<700) {return 2;}

            break;

        }
        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
        SDL_BlitSurface(difficulte,NULL,ecran,&pos_board);
        SDL_Flip(ecran);
    }

}
