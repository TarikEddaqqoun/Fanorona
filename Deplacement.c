#include <SDL/SDL.h>
#include <SDL_image.h>
#include <time.h>
#include <windows.h>
#include "Deplacement.h"
#include "variable.h"



int capturation_exist(int a,int b){

    int cap1=0,cap2=0,cap3=0,cap4=0,cap5=0,cap6=0,cap7=0,cap8=0;
    if(!board_etat_temporaire[a+1][b] && dir!=dir_capt(a,b,a+1,b) && a+1<5) cap1=capturations_possibles(a,b,a+1,b);
    if(!board_etat_temporaire[a][b+1]&& dir!=dir_capt(a,b,a,b+1) && b+1<9) cap2=capturations_possibles(a,b,a,b+1);
    if(!board_etat_temporaire[a+1][b+1]&& dir!=3 && a+1<5 && b+1 <9) cap3=capturations_possibles(a,b,a+1,b+1);
    if(!board_etat_temporaire[a-1][b]&& dir!=dir_capt(a,b,a-1,b) && a-1>=0) cap4=capturations_possibles(a,b,a-1,b);
    if(!board_etat_temporaire[a][b-1]&& dir!=dir_capt(a,b,a,b-1) && b-1>=0) cap5=capturations_possibles(a,b,a,b-1);
    if(!board_etat_temporaire[a-1][b-1]&& dir!=3 && a-1>=0 && b-1>=0) cap6=capturations_possibles(a,b,a-1,b-1);
    if(!board_etat_temporaire[a-1][b+1]&& dir!=4 && a-1>=0 && b+1<9) cap7=capturations_possibles(a,b,a-1,b+1);
    if(!board_etat_temporaire[a+1][b-1]&& dir!=4 && a+1<5 && b-1>=0) cap8=capturations_possibles(a,b,a+1,b-1);

    return !(cap1==0 && cap2==0 && cap3==0 && cap4==0 && cap5==0 && cap6==0 && cap7==0 && cap8==0);

}

void capturer(int a,int b,SDL_Rect pos[])
{
    pos[abs(board_etat[a][b])-1].x=1366;
    pos[abs(board_etat[a][b])-1].y=766;
    if(board_etat[a][b]>0) n_noir--;
    else if(board_etat[a][b]<0) n_blanc--;
    board_etat[a][b]=0;
}

int doit_capturer(int tour){
    int signe;
    if (tour%2==0) signe=1;
    else signe=-1;
    int i;
    int j;
    for (i=0;i<9;i++){
        for (j=0;j<5;j++){
            if (board_etat[j][i]*signe>0){
                if (capturation_exist(j,i)) return 1;
            }
        }
    }
    return 0;

}

int capturations_possibles(int a,int b,int a2,int b2){ /* fonction qui retourne 0 s'il n y a rien a capturer
    et retoune -1 s'il existe une capturation derrier ,
    retourne 1 s'il exsiste une capturation en avant, et 2 s'il existe 2 capturations*/

    if (!deplacement_est_possible(a,b,a2,b2)) return 0;

    else {
            int a_derrier=a-(a2-a),b_derrier=b-(b2-b);
            int a_avant=a2+(a2-a),b_avant=b2+(b2-b);
            //printf("%d %d // %d %d // %d %d\n b*b=%d\n",a_derrier,b_derrier,board_etat[a][b],board_etat[0][0],a_avant,b_avant,board_etat[a_derrier][b_derrier]*board_etat[a][b]);
            int r=0;
            if (a_derrier>=0 && a_derrier<=4 && b_derrier>=0 && b_derrier<=8 && board_etat[a_derrier][b_derrier]*board_etat[a][b]<0) {
                    r=-1;

            }
            if (a_avant>=0 && a_avant<=4 && b_avant>=0 && b_avant<=8 && board_etat[a_avant][b_avant]*board_etat[a][b]<0){
                if (r==-1) r=2;
                else r=1;
            }
            return r;
    }
}

int dir_capt(int a,int b, int c, int d)  // retourne la direction de capture
{
    if(abs(c-a)==0 && abs(d-b)==1) return 1;
    if(abs(c-a)==1 && abs(d-b)==0) return 2;
    if((c-a)*(d-b)>0) return 3;
    else return 4;

}

void capturer_plusieurs(int a2,int b2,int a_temp,int b_temp,SDL_Rect pos1[] )
{
            while (board_etat[a2][b2]*board_etat[a_temp][b_temp]<0 && b_temp>=0 && b_temp<=8 && a_temp>=0 && a_temp<=4)
            {
                capturer(a_temp,b_temp,pos1);
                if (a_temp-a2<0) a_temp--;
                if (a_temp-a2>0) a_temp++;
                if (b_temp-b2<0) b_temp--;
                if (b_temp-b2>0) b_temp++;
            }
}

void tracer_choix(int a2,int b2,int a_temp,int b_temp,SDL_Rect pos1[],SDL_Surface *capture)
{
                            while (board_etat[a2][b2]*board_etat[a_temp][b_temp]<0 && b_temp>=0 && b_temp<=8 && a_temp>=0 && a_temp<=4)
                            {
                                SDL_Rect position;
                                position.x=board_x+(b_temp)*board_w/8-35;
                                position.y=board_y+(a_temp)*board_h/4-35;
                                SDL_BlitSurface(capture,NULL,ecran,&position);
                                SDL_Flip(ecran);
                                if (a_temp-a2<0) a_temp--;
                                if (a_temp-a2>0) a_temp++;
                                if (b_temp-b2<0) b_temp--;
                                if (b_temp-b2>0) b_temp++;
                            }
                        }

void deplacer_pion_machine(SDL_Surface *pions[],SDL_Surface *pions1,SDL_Rect pos[],SDL_Rect pos1[])
{
    int x_pion,y_pion,x_dest,y_dest;
    int len=0,pion_possible[22];
    int d_capt=0,choix=0;
    int i,r;
    for( i=0;i<22;i++)
    {
        find_pos(pos[i].x+35,pos[i].y+35,&x_pion,&y_pion);
        if(capturation_exist(x_pion,y_pion)) pion_possible[len]=i,len++;
    }
    if(len==0)
    {
        while(!choix)
        {
            r=rand()%22,find_pos(pos[r].x+35,pos[r].y+35,&x_pion,&y_pion);
            if(x_pion!=-1 || y_pion!=-1) choix=1;
        }
    }
    else r=rand()%len,find_pos(pos[pion_possible[r]].x+35,pos[pion_possible[r]].y+35,&x_pion,&y_pion),d_capt=1;
    choix = 0;
    while(!choix)
    {
        int r=rand()%8;
        if(r==0 && deplacement_est_possible(x_pion,y_pion,x_pion+1,y_pion))
        {
            if(d_capt && capturations_possibles(x_pion,y_pion,x_pion+1,y_pion)==0)
                continue;
            else
                x_dest=x_pion+1,y_dest=y_pion,choix=1;
        }
        if(r==1 && deplacement_est_possible(x_pion,y_pion,x_pion-1,y_pion))
        {
            if(d_capt && capturations_possibles(x_pion,y_pion,x_pion-1,y_pion)==0)
                continue;
            else
                x_dest=x_pion-1,y_dest=y_pion,choix=1;
        }
        if(r==2 && deplacement_est_possible(x_pion,y_pion,x_pion,y_pion+1))
        {
            if(d_capt && capturations_possibles(x_pion,y_pion,x_pion,y_pion+1)==0)
                continue;
            else
                x_dest=x_pion,y_dest=y_pion+1,choix=1;
        }
        if(r==3 && deplacement_est_possible(x_pion,y_pion,x_pion,y_pion-1))
        {
            if(d_capt && capturations_possibles(x_pion,y_pion,x_pion,y_pion-1)==0)
                continue;
            else
                x_dest=x_pion,y_dest=y_pion-1,choix=1;
        }
        if(r==4 && deplacement_est_possible(x_pion,y_pion,x_pion+1,y_pion+1))
        {
            if(d_capt && capturations_possibles(x_pion,y_pion,x_pion+1,y_pion+1)==0)
                continue;
            else
                x_dest=x_pion+1,y_dest=y_pion+1,choix=1;
        }
        if(r==5 && deplacement_est_possible(x_pion,y_pion,x_pion+1,y_pion-1))
        {

            if(d_capt && capturations_possibles(x_pion,y_pion,x_pion+1,y_pion-1)==0)
                continue;
            else
                x_dest=x_pion+1,y_dest=y_pion-1,choix=1;
        }
        if(r==6 && deplacement_est_possible(x_pion,y_pion,x_pion-1,y_pion+1))
        {
            if(d_capt && capturations_possibles(x_pion,y_pion,x_pion-1,y_pion+1)==0)
                continue;
            else
                x_dest=x_pion-1,y_dest=y_pion+1,choix=1;
        }
        if(r==7 && deplacement_est_possible(x_pion,y_pion,x_pion-1,y_pion-1))
        {
            if(d_capt && capturations_possibles(x_pion,y_pion,x_pion-1,y_pion-1)==0)
                continue;
            else
                x_dest=x_pion-1,y_dest=y_pion-1,choix=1;
        }
    }

    pos[abs(board_etat[x_pion][y_pion])-1].x=board_x+(y_dest)*board_w/8-35;
    pos[abs(board_etat[x_pion][y_pion])-1].y=board_y+(x_dest)*board_h/4-35;


    if (capturations_possibles(x_pion,y_pion,x_dest,y_dest)==1 || capturations_possibles(x_pion,y_pion,x_dest,y_dest)==2 ) // s'il y a capturation par percussion
    {
        int b_temp=y_dest+(y_dest-y_pion),a_temp=x_dest+(x_dest-x_pion);
        capturer_plusieurs(x_pion,y_pion,a_temp,b_temp,pos1);
    }
    else if (capturations_possibles(x_pion,y_pion,x_dest,y_dest)==-1) // s'il y a capturation par aspiration
    {
        int b_temp=y_pion-(y_dest-y_pion),a_temp=x_pion-(x_dest-x_pion);
        capturer_plusieurs(x_pion,y_pion,a_temp,b_temp,pos1);
    }

    board_etat[x_dest][y_dest]=board_etat[x_pion][y_pion];
    board_etat[x_pion][y_pion]=0;
}

int nombre_captures(int x,int y,int next_x,int next_y)
{
    int cnt=0;
    while (board_etat[x][y]*board_etat[next_x][next_y]<0 && next_y>=0 && next_y<=8 && next_x>=0 && next_x<=4)
            {
                if (next_x-x<0) next_x--;
                if (next_x-x>0) next_x++;
                if (next_y-y<0) next_y--;
                if (next_y-y>0) next_y++;
                cnt++;
            }
    return cnt;
}

void calcul_max_capture(int x_pion,int y_pion,int x_next,int y_next,int *max,int *x_dest,int *y_dest,int *a,int *b)
{
    switch(capturations_possibles(x_pion,y_pion,x_next,y_next)){
                int a_temp,b_temp,cnt;
                case 1:
                    b_temp=y_next+(y_next-y_pion),a_temp=x_next+(x_next-x_pion);
                    cnt=nombre_captures(x_pion,y_pion,a_temp,b_temp);
                    if(cnt>*max) *max=cnt,*x_dest=x_next,*y_dest=y_next,*a=x_pion,*b=y_pion;
                break;
                case -1:
                    b_temp=y_pion-(y_next-y_pion),a_temp=x_pion-(x_next-x_pion);
                    cnt=nombre_captures(x_pion,y_pion,a_temp,b_temp);
                    if(cnt>*max) *max=cnt,*x_dest=x_next,*y_dest=y_next,*a=x_pion,*b=y_pion;
                break;
                case 2:
                    b_temp=y_next+(y_next-y_pion),a_temp=x_next+(x_next-x_pion);
                    cnt=nombre_captures(x_pion,y_pion,a_temp,b_temp);
                    if(cnt>*max) *max=cnt,*x_dest=x_next,*y_dest=y_next,*a=x_pion,*b=y_pion;
                    b_temp=y_pion-(y_next-y_pion),a_temp=x_pion-(x_next-x_pion);
                    cnt=nombre_captures(x_pion,y_pion,a_temp,b_temp);
                    if(cnt>*max) *max=cnt,*x_dest=x_next,*y_dest=y_next,*a=x_pion,*b=y_pion;
                break;
        }
}

int safe_to_move(int x_pion,int y_pion,int x,int y)
{
    if(deplacement_est_possible(x_pion,y_pion,x,y))
    {
        int i,j;
        int pion=board_etat[x_pion][y_pion];
        board_etat[x_pion][y_pion]=0;
        board_etat[x][y]=pion;
        for(i=x-1;i<=x+1;i++)
        {
            for(j=y-1;j<=y+1;j++)
            {
                // dial aspiration int b_temp=y_tomove-(y_dest-y_tomove),a_temp=x_tomove-(x_dest-x_tomove);
                // dial percussion int b_temp=y_dest+(y_dest-y_tomove),a_temp=x_dest+(x_dest-x_tomove);
                if(i>=0 && i<=4 && j>=0 && j<=8)
                {
                    int b_temp=j-(y-j),a_temp=i-(x-i);
                    if(board_etat[i][j]*pion<0 && capturations_possibles(i,j,a_temp,b_temp))
                    {
                        board_etat[x_pion][y_pion]=pion;
                        board_etat[x][y]=0;
                        return 0;
                    }
                    if(a_temp>=0 && a_temp<=4 && b_temp>=0 && b_temp<=8 && board_etat[a_temp][b_temp]*pion<0)
                    {
                        if(capturations_possibles(a_temp,b_temp,i,j))
                        {
                            board_etat[x_pion][y_pion]=pion;
                            board_etat[x][y]=0;
                            return 0;
                        }
                    }
                }

            }
        }
        board_etat[x_pion][y_pion]=pion;
        board_etat[x][y]=0;
        return 1;
    }
    return 0;
}

void deplacer_pion_machine2(SDL_Surface *pions[],SDL_Surface *pions1,SDL_Rect pos[],SDL_Rect pos1[])
{
    int x_pion,y_pion,x_dest,y_dest,x_tomove,y_tomove;
    int len=0,pion_possible[22];
    int max=0;
    int d_capt=0,choix=0;
    int i,r;

    int capt2=1;
    int acapt2=0;

    while(capt2)
    {
    max=0;
    if(acapt2)
    {

        if(!capturation_exist(x_tomove,y_tomove))
        {
            return;
        }
        else
        {
            calcul_max_capture(x_tomove,y_tomove,x_tomove+1,y_tomove,&max,&x_dest,&y_dest,&x_tomove,&y_tomove);
            calcul_max_capture(x_tomove,y_tomove,x_tomove-1,y_tomove,&max,&x_dest,&y_dest,&x_tomove,&y_tomove);
            calcul_max_capture(x_tomove,y_tomove,x_tomove,y_tomove+1,&max,&x_dest,&y_dest,&x_tomove,&y_tomove);
            calcul_max_capture(x_tomove,y_tomove,x_tomove,y_tomove-1,&max,&x_dest,&y_dest,&x_tomove,&y_tomove);
            calcul_max_capture(x_tomove,y_tomove,x_tomove+1,y_tomove+1,&max,&x_dest,&y_dest,&x_tomove,&y_tomove);
            calcul_max_capture(x_tomove,y_tomove,x_tomove+1,y_tomove-1,&max,&x_dest,&y_dest,&x_tomove,&y_tomove);
            calcul_max_capture(x_tomove,y_tomove,x_tomove-1,y_tomove+1,&max,&x_dest,&y_dest,&x_tomove,&y_tomove);
            calcul_max_capture(x_tomove,y_tomove,x_tomove-1,y_tomove-1,&max,&x_dest,&y_dest,&x_tomove,&y_tomove);
        }

    }
    else{
    for( i=0;i<22;i++)
    {
        find_pos(pos[i].x+35,pos[i].y+35,&x_pion,&y_pion);
        if(capturation_exist(x_pion,y_pion))
        {
            calcul_max_capture(x_pion,y_pion,x_pion+1,y_pion,&max,&x_dest,&y_dest,&x_tomove,&y_tomove);
            calcul_max_capture(x_pion,y_pion,x_pion-1,y_pion,&max,&x_dest,&y_dest,&x_tomove,&y_tomove);
            calcul_max_capture(x_pion,y_pion,x_pion,y_pion+1,&max,&x_dest,&y_dest,&x_tomove,&y_tomove);
            calcul_max_capture(x_pion,y_pion,x_pion,y_pion-1,&max,&x_dest,&y_dest,&x_tomove,&y_tomove);
            calcul_max_capture(x_pion,y_pion,x_pion+1,y_pion+1,&max,&x_dest,&y_dest,&x_tomove,&y_tomove);
            calcul_max_capture(x_pion,y_pion,x_pion+1,y_pion-1,&max,&x_dest,&y_dest,&x_tomove,&y_tomove);
            calcul_max_capture(x_pion,y_pion,x_pion-1,y_pion+1,&max,&x_dest,&y_dest,&x_tomove,&y_tomove);
            calcul_max_capture(x_pion,y_pion,x_pion-1,y_pion-1,&max,&x_dest,&y_dest,&x_tomove,&y_tomove);
        }

    }
    }
    if(max==0)
    {
        capt2=0;

        int moved=0;
        for( i=0;i<22;i++)
        {
        find_pos(pos[i].x+35,pos[i].y+35,&x_pion,&y_pion);
        if(x_pion!=-1 || y_pion!=-1)
        {
            if(safe_to_move(x_pion,y_pion,x_pion+1,y_pion)) x_tomove=x_pion,y_tomove=y_pion,x_dest=x_pion+1,y_dest=y_pion,moved=1;
            else if(safe_to_move(x_pion,y_pion,x_pion-1,y_pion)) x_tomove=x_pion,y_tomove=y_pion,x_dest=x_pion-1,y_dest=y_pion,moved=1;
            else if(safe_to_move(x_pion,y_pion,x_pion,y_pion+1)) x_tomove=x_pion,y_tomove=y_pion,x_dest=x_pion,y_dest=y_pion+1,moved=1;
            else if(safe_to_move(x_pion,y_pion,x_pion,y_pion-1)) x_tomove=x_pion,y_tomove=y_pion,x_dest=x_pion,y_dest=y_pion-1,moved=1;
            else if(safe_to_move(x_pion,y_pion,x_pion+1,y_pion+1)) x_tomove=x_pion,y_tomove=y_pion,x_dest=x_pion+1,y_dest=y_pion+1,moved=1;
            else if(safe_to_move(x_pion,y_pion,x_pion+1,y_pion-1)) x_tomove=x_pion,y_tomove=y_pion,x_dest=x_pion+1,y_dest=y_pion-1,moved=1;
            else if(safe_to_move(x_pion,y_pion,x_pion-1,y_pion+1)) x_tomove=x_pion,y_tomove=y_pion,x_dest=x_pion-1,y_dest=y_pion+1,moved=1;
            else if(safe_to_move(x_pion,y_pion,x_pion-1,y_pion-1)) x_tomove=x_pion,y_tomove=y_pion,x_dest=x_pion-1,y_dest=y_pion-1,moved=1;
        }
        }
        if(!moved)
        { int choix=0;
        while(!choix)
        {
            r=rand()%22,find_pos(pos[r].x+35,pos[r].y+35,&x_pion,&y_pion);
            if(x_pion!=-1 || y_pion!=-1) choix=1;
        }

        choix = 0;
        while(!choix)
        {
            int r=rand()%8;
            if(r==0 && deplacement_est_possible(x_pion,y_pion,x_pion+1,y_pion)) x_tomove=x_pion,y_tomove=y_pion,x_dest=x_pion+1,y_dest=y_pion,choix=1;
            if(r==1 && deplacement_est_possible(x_pion,y_pion,x_pion-1,y_pion)) x_tomove=x_pion,y_tomove=y_pion,x_dest=x_pion-1,y_dest=y_pion,choix=1;
            if(r==2 && deplacement_est_possible(x_pion,y_pion,x_pion,y_pion+1)) x_tomove=x_pion,y_tomove=y_pion,x_dest=x_pion,y_dest=y_pion+1,choix=1;
            if(r==3 && deplacement_est_possible(x_pion,y_pion,x_pion,y_pion-1)) x_tomove=x_pion,y_tomove=y_pion,x_dest=x_pion,y_dest=y_pion-1,choix=1;
            if(r==4 && deplacement_est_possible(x_pion,y_pion,x_pion+1,y_pion+1)) x_tomove=x_pion,y_tomove=y_pion,x_dest=x_pion+1,y_dest=y_pion+1,choix=1;
            if(r==5 && deplacement_est_possible(x_pion,y_pion,x_pion+1,y_pion-1)) x_tomove=x_pion,y_tomove=y_pion,x_dest=x_pion+1,y_dest=y_pion-1,choix=1;
            if(r==6 && deplacement_est_possible(x_pion,y_pion,x_pion-1,y_pion+1)) x_tomove=x_pion,y_tomove=y_pion,x_dest=x_pion-1,y_dest=y_pion+1,choix=1;
            if(r==7 && deplacement_est_possible(x_pion,y_pion,x_pion-1,y_pion-1)) x_tomove=x_pion,y_tomove=y_pion,x_dest=x_pion-1,y_dest=y_pion-1,choix=1;


        }

        }
    }
    else
    {
        dir=dir_capt(x_tomove,y_tomove,x_dest,y_dest);
        board_etat_temporaire[x_tomove][y_tomove]=1;
        acapt2=1;
    }
    pos[abs(board_etat[x_tomove][y_tomove])-1].x=board_x+(y_dest)*board_w/8-35;
    pos[abs(board_etat[x_tomove][y_tomove])-1].y=board_y+(x_dest)*board_h/4-35;

    if (capturations_possibles(x_tomove,y_tomove,x_dest,y_dest)==1 || capturations_possibles(x_tomove,y_tomove,x_dest,y_dest)==2 ) // s'il y a capturation par percussion
    {
        int b_temp=y_dest+(y_dest-y_tomove),a_temp=x_dest+(x_dest-x_tomove);
        capturer_plusieurs(x_tomove,y_tomove,a_temp,b_temp,pos1);
    }
    else if (capturations_possibles(x_tomove,y_tomove,x_dest,y_dest)==-1) // s'il y a capturation par aspiration
    {
        int b_temp=y_tomove-(y_dest-y_tomove),a_temp=x_tomove-(x_dest-x_tomove);
        capturer_plusieurs(x_tomove,y_tomove,a_temp,b_temp,pos1);
    }

    board_etat[x_dest][y_dest]=board_etat[x_tomove][y_tomove];
    board_etat[x_tomove][y_tomove]=0;
    int j;
    x_tomove=x_dest,y_tomove=y_dest;
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
        SDL_BlitSurface(board,NULL,ecran,&pos_board);

        for(i=0;i<22;i++) SDL_BlitSurface(pions_noir[i],NULL,ecran,&pos_noir[i]);
        for(i=0;i<22;i++) SDL_BlitSurface(pions_blanc[i],NULL,ecran,&pos_blanc[i]);
        SDL_BlitSurface(indicateur_tour2,NULL,ecran,&pos_tr2);
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

        SDL_Flip(ecran);
        Sleep(1000);
    }

}

void deplacer_pion(SDL_Surface *pions[],SDL_Surface *pions1[],SDL_Rect pos[],SDL_Rect pos1[] ,Uint16 x0,Uint16 y0,int k,int* capt,int *xprec,int *yprec)
{

    if(y0<pos[abs(k)-1].y+5 || y0>(pos[abs(k)-1].y+65) || x0<pos[abs(k)-1].x+5 || x0>pos[abs(k)-1].x+60)
    {
        return;
    }

    SDL_Event event1;
    SDL_Rect p;
    p.x=0;
    p.y=0;

    int i,j,t=1;

    while(t)
    {
        SDL_WaitEvent(&event1);
        switch(event1.type)
        {
            case SDL_MOUSEBUTTONUP:
                t=0;
                int a1,b1;
                int a2,b2;
                find_pos(event1.button.x,event1.button.y,&a1,&b1);
                find_pos(x0,y0,&a2,&b2); // possibilité de faire direct a2 et b2 sont xres et yres
                if (deplacement_est_possible(a2,b2,a1,b1) && dir!=dir_capt(a2,b2,a1,b1) && !(abs(capturations_possibles(a2,b2,a1,b1))<doit_capturer(tour) && acapt==0 ) && !(acapt>0 && capturations_possibles(a2,b2,a1,b1)==0 && capturation_exist(a2,b2))) // si deplacement possible et si madazch mnha 9bel
                {
                    // si le deplacement est possible on change la position du pion
                    pos[abs(k)-1].x=board_x+(b1)*board_w/8-35;
                    pos[abs(k)-1].y=board_y+(a1)*board_h/4-35;

                    // on enregistre la position du pion
                    *xprec=a1;
                    *yprec=b1;

                    if (capturations_possibles(a2,b2,a1,b1)==1) // s'il y a capturation par percussion
                    {
                        *capt=1;
                        int b_temp=b1+(b1-b2),a_temp=a1+(a1-a2);
                        capturer_plusieurs(a2,b2,a_temp,b_temp,pos1);
                    }

                    if (capturations_possibles(a2,b2,a1,b1)==-1) // s'il y a capturation par aspiration
                    {
                        *capt=1;
                        int b_temp=b2-(b1-b2),a_temp=a2-(a1-a2);
                        capturer_plusieurs(a2,b2,a_temp,b_temp,pos1);
                    }

                    if (capturations_possibles(a2,b2,a1,b1)==2) // s'il y a capturations par percussion et aspiration
                    {
                        *capt=1;
                        SDL_Event choix;
                        SDL_Surface *capture=NULL;

                        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
                        SDL_BlitSurface(board,NULL,ecran,&pos_board);

                        capture=IMG_Load("images/pion_capture.png");
                        for(i=0;i<22;i++) SDL_BlitSurface(pions[i],NULL,ecran,&pos[i]);
                        for(i=0;i<22;i++) SDL_BlitSurface(pions1[i],NULL,ecran,&pos1[i]);


                        int b_temp=b2-(b1-b2),a_temp=a2-(a1-a2);
                        tracer_choix(a2,b2,a_temp,b_temp,pos1,capture);

                        b_temp=b1+(b1-b2),a_temp=a1+(a1-a2);
                        tracer_choix(a2,b2,a_temp,b_temp,pos1,capture);

                        SDL_Flip(ecran);

                        int pause=1;
                        while (pause){

                            SDL_WaitEvent(&choix);
                            int a_choix,b_choix;
                            switch (choix.type)
                            {
                                case SDL_MOUSEBUTTONDOWN:

                                    find_pos(choix.button.x,choix.button.y,&a_choix,&b_choix);
                                    if (b_choix==b1+(b1-b2) && a_choix==a1+(a1-a2)){
                                        pause=0;
                                        int b_temp=b1+(b1-b2),a_temp=a1+(a1-a2);
                                        capturer_plusieurs(a2,b2,a_temp,b_temp,pos1);
                                    }
                                    if (b_choix==b2-(b1-b2) && a_choix==a2-(a1-a2)){
                                        pause=0;
                                        int b_temp=b2-(b1-b2),a_temp=a2-(a1-a2);
                                        capturer_plusieurs(a2,b2,a_temp,b_temp,pos1);
                                    }
                                    break;
                            }
                        }
                    }
                    board_etat[a1][b1]=k;
                    board_etat[a2][b2]=0;
                }
                else
                {
                    pos[abs(k)-1].x=board_x+(b2)*board_w/8-35;
                    pos[abs(k)-1].y=board_y+(a2)*board_h/4-35;
                }
                break;

            case SDL_MOUSEMOTION:
                pos[abs(k)-1].x=event1.motion.x-35;
                pos[abs(k)-1].y=event1.motion.y-35;
                break;
        }
        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
        SDL_BlitSurface(board,NULL,ecran,&p);
        for(i=0;i<22;i++) SDL_BlitSurface(pions[i],NULL,ecran,&pos[i]);
        for(i=0;i<22;i++) SDL_BlitSurface(pions1[i],NULL,ecran,&pos1[i]);

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
        if(tour%2==0)SDL_BlitSurface(indicateur_tour1,NULL,ecran,&pos_tr1);
        else  SDL_BlitSurface(indicateur_tour2,NULL,ecran,&pos_tr2);
        SDL_Flip(ecran);
    }
}


int deplacement_est_possible(int a, int b,int a2,int b2) //foction qui test si le deplacement de la case (a,b) vers (a2,b2) est possible
{

    if(board_etat_temporaire[a2][b2]) return 0;
    if(a2<0 || a2>4 || b2<0 || b2>8) return 0;
    if (board_etat[a2][b2]!=0 || a2==-1 || b2==-1) return 0;
    if(abs(a-a2)>1 || abs(b-b2)>1) return 0;
    if ((a+b) % 2==1)
    {
        if ((abs(a-a2)==1 && abs(b-b2)==1)) return 0;
    }
    return 1;
}


void find_pos(Uint16 xp, Uint16 yp,int *x_res,int *y_res)
{
    xp=abs(xp-board_x);
    yp=abs(yp-board_y);
    int i,j;

    double a=(double)xp/(double)board_w;
    double b=(double)yp/(double)board_h;

    *x_res=-1;
    *y_res=-1;
    for(j=0;j<9;j++)
    {
        for(i=0;i<5;i++)
        {

            if(fabs(a-(double)j/8.0)<err && fabs(b-(double)i/4.0)<err)
            {
                *x_res=i;
                *y_res=j;
                break;
            }
        }
    }
}
