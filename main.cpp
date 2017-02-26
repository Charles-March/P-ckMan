#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <time.h>
#include <ctime>
#define Xfenetre 3000
#define Yfenetre 3000
#define WT 2500
#define NBP 2500
#define lvlmax 10
#define mob 10

int hasard(int n)
{
    int partSize   = 1 + (n == RAND_MAX ? 0 : (RAND_MAX - n) / (n + 1));
    int maxUsefull = partSize * n + (partSize - 1);
    int draw;

    do {
        draw = rand();
    } while (draw > maxUsefull);

    return draw / partSize;
}

int CP(SDL_Rect a,SDL_Rect b[NBP], int comptP)
{
int i;
int rep=0;
int c=0;
    for(i=0;(i<=comptP)&&((rep==0)||(rep==-1))&&(c==0);i++)
    {
     if(a.y+30==b[i].y){c=1;}
     if(((a.x<b[i].x+30)&&(a.x>b[i].x-30)&&((a.y<b[i].y+30)&&(a.y>b[i].y-30))))
     {rep=i;}
     else {rep=-1;}
    }
return rep;
}

int mur(SDL_Rect a, SDL_Rect b[WT],int comptW)
{
int i;
int rep=0;
int c=0;
    for(i=0;(i<=comptW-1)&&(rep==0)&&(c==0);i++)
    {
     if(a.y+30<b[i].y){c=1;}
     if(((a.x<b[i].x+30)&&(a.x>b[i].x-25)&&((a.y<b[i].y+30)&&(a.y>b[i].y-25))))
     {rep=1;}
    }
return rep;
}

int col(SDL_Rect a, SDL_Rect b)
{
if(((a.x<=b.x)&&(a.x+29>=b.x)&&((a.y<=b.y)&&(a.y+29>=b.y))))
{return 1;}
else
return 0;
}

int Mouvement(SDL_Rect c,SDL_Rect d[WT],int b)
{
int a=1;
char i=0;
if(b==0){b=hasard(3)+1;}
else if(b==1){b=hasard(3)+1;}
else if(b==2){b=hasard(3)+1;}
else if(b==3){b=hasard(3)+1;}
else if(b==4){b=hasard(3)+1;}
return b;
}

int Mouvement2(SDL_Rect a,SDL_Rect w[WT],int b)
{

}

int main(int argc, char *argv[])
{

time_t timer=0;
time_t timer2=0;
int mvtR=0;
int Sx=0,Sy=0,SAx=0,SAy=0;
int direction=0,directionB[mob];
int ammo=0, p=0;
int comptW,comptP;
char chaine[30];
int speed=1;
int mapx,mapy;
int mouseX,mouseY;
int mb=0,mb2=0,menu=1;
int lvl=1;
int continuerL=1;
int perdu=0;
int b3;
int nb=0;
int b,b2[mob],nb1=0,c;
int pts=0;
int a=0;
int j=0,k=0;
int i,i2;
char Fireball[30]="Fireball :       ";

for(i=0;i<mob;i++)
{directionB[i]=0;}

SDL_Surface *fontL=NULL;
SDL_Surface *SAVE=NULL;
SDL_Surface *LOAD=NULL;
SDL_Surface *Title=NULL;
SDL_Surface *QUIT=NULL;
SDL_Surface *ecran=NULL;
SDL_Surface *bouton1=NULL;
SDL_Surface *mob1=NULL;
SDL_Surface *PLAY=NULL;
SDL_Surface *Wall=NULL;
SDL_Surface *piece=NULL;
SDL_Surface *GO=NULL;
SDL_Surface *Chargement=NULL;
SDL_Surface *mob2=NULL;
SDL_Surface *BDF=NULL;
SDL_Surface *PIMENT=NULL;
SDL_Surface *BOSS1=NULL;

SDL_Surface *ERROR=NULL;
SDL_Color noir={0,0,0};

SDL_Surface *LVL=NULL;
SDL_Surface *FIREBALL=NULL;

SDL_Event event;
FILE *fichier;

SDL_Rect chargement;

SDL_Rect pb1[mob];

SDL_Rect Lvl;
SDL_Rect fireball;

SDL_Rect piment[mob];
SDL_Rect bdf[mob];
for (i=0;i<mob;i++)
{piment[i].x=0;piment[i].y=0;
bdf[i].x=0;bdf[i].y=0;}

SDL_Rect fontl;
fontl.x=0;
fontl.y=0;
SDL_Rect save;
SDL_Rect load;

SDL_Rect title;

SDL_Rect play;
play.x=(Xfenetre/2-55);
play.y=(Xfenetre/2-27);

SDL_Rect quit;
quit.x=0;
quit.y=0;

SDL_Rect W[WT];
W[WT].x={0};
W[WT].y={0};
for(i=0;i<WT;i++)
{W[i].x=0;W[i].y=0;}

SDL_Rect P[NBP];
P[NBP].x={0};
P[NBP].y={0};
for(i=0;i<NBP;i++)
{P[i].x=1500;P[i].y=1500;}

SDL_Rect text;

SDL_Rect pp1;
pp1.x=30;
pp1.y=30;

SDL_Rect pm[mob];
pm[mob].x;
pm[mob].y;
for(i=0;i<mob;i++)
{pm[i].x=Xfenetre*2;pm[i].y=Yfenetre*2;}

SDL_Rect pm2[mob];
for(i=0;i<mob;i++)
{pm2[i].x=15000;pm2[i].y=15000;}

SDL_Rect go;
go.x=0;
go.y=0;
int continuerG = 1;

SDL_Init(SDL_INIT_EVERYTHING);
if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
        exit(EXIT_FAILURE);
    }
TTF_Init();
TTF_Font *police=NULL;
police = TTF_OpenFont("JackI.ttf", 13);

ecran = SDL_SetVideoMode(Xfenetre, Yfenetre, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);  //| SDL_NOFRAME);
SDL_WM_SetCaption("Fuck man",NULL);
SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 17, 206, 112));

Wall=SDL_LoadBMP("img/wall.bmp");


bouton1 = SDL_LoadBMP("img/R.bmp");
mob1 = SDL_LoadBMP("img/mob.bmp");

fontL=SDL_LoadBMP("img/fontL.bmp");
SAVE=SDL_LoadBMP("img/boutonSAVE.bmp");
LOAD=SDL_LoadBMP("img/boutonLOAD.bmp");
Title=SDL_LoadBMP("img/Title.bmp");
PLAY= SDL_LoadBMP("img/boutonPLAY.bmp");
QUIT= SDL_LoadBMP("img/boutonQUIT.bmp");
Chargement=SDL_LoadBMP("img/Chargement.bmp");
piece=SDL_LoadBMP("img/piece.bmp");
mob2=SDL_LoadBMP("img/mob2.bmp");
BDF=SDL_LoadBMP("img/BDF.bmp");
PIMENT=SDL_LoadBMP("img/piment.bmp");

SDL_EnableKeyRepeat(1,50);
event.type=NULL;
b=0;
lvl=1;
while (continuerL)
{
ecran = SDL_SetVideoMode(800, 800, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 17, 206, 112));
    while (menu==1)
    {
     chargement.x=10;chargement.y=297;
     fontl.x=0;fontl.y=0;
     load.x=2;load.y=210;
     save.x=118;save.y=210;
     title.x=5;title.y=0;
     play.x=60;play.y=90;
     quit.x=60;quit.y=150;
     ecran = SDL_SetVideoMode(230, 350, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_NOFRAME);
     SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
     SDL_SetColorKey(Title, SDL_SRCCOLORKEY, SDL_MapRGB(Title->format, 255, 255, 255));
     SDL_SetColorKey(fontL, SDL_SRCCOLORKEY, SDL_MapRGB(fontL->format, 255, 255, 255));
     SDL_SetColorKey(Chargement, SDL_SRCCOLORKEY, SDL_MapRGB(Chargement->format, 255, 255, 255));
     SDL_BlitSurface(Chargement,NULL,ecran,&chargement);
     SDL_BlitSurface(fontL,NULL,ecran,&fontl);
     SDL_BlitSurface(QUIT,NULL,ecran,&quit);
     SDL_BlitSurface(SAVE,NULL,ecran,&save);
     SDL_BlitSurface(LOAD,NULL,ecran,&load);
     SDL_BlitSurface(Title,NULL,ecran,&title);
     SDL_BlitSurface(PLAY,NULL,ecran,&play);
     SDL_BlitSurface(ERROR, NULL, ecran, &text);
     SDL_Flip(ecran);

     while(event.type!=SDL_MOUSEBUTTONDOWN)
     {
     SDL_WaitEvent(&event);
     }

     if (event.type==SDL_MOUSEBUTTONDOWN)
     {
         SDL_Delay(200);
         event.type=NULL;
         SDL_WaitEvent(&event);
         if(event.button.button==SDL_BUTTON_LEFT)
         {
             SDL_GetMouseState(&mouseX, &mouseY);
             if ((mouseX>(60))&&(mouseX<((60)+111))&&(mouseY>(90))&&(mouseY<=((90)+55)))
             {SDL_Delay(100);menu=0;continuerG=1;pts=0;continuerL=0;}
             if ((mouseX>(60))&&(mouseX<(60+111))&&(mouseY>(150))&&(mouseY<=(150+55)))
             {SDL_Delay(500);menu=0;continuerG=0;continuerL=0;}
             if ((mouseX>(2))&&(mouseX<(2+111))&&(mouseY>(210))&&(mouseY<=(210+55)))//load
            {
             fichier=fopen("SDL.dat","r");
             if(fichier==NULL){text.x=15;text.y=300;
             ERROR=TTF_RenderText_Blended(police,"Aucune sauvegarde trouvée !",noir);
             TTF_SetFontStyle(police, TTF_STYLE_UNDERLINE);
             SDL_BlitSurface(ERROR, NULL, ecran, &text);SDL_Flip(ecran);}
             else {fscanf(fichier,"%d",&lvl);
            text.x=15;text.y=300;
            ERROR=TTF_RenderText_Blended(police,"Load Complete !",noir);}}
             if ((mouseX>(118))&&(mouseX<(118+111))&&(mouseY>(210))&&(mouseY<=(210+55)))//save
            {text.x=600;text.y=600;
            fichier=fopen("SDL.dat","w");
            fprintf(fichier,"%d",lvl);
            text.x=15;text.y=300;
            ERROR=TTF_RenderText_Blended(police,"Save Complete !",noir);}
            event.type=NULL;
         }
     }
    }

if (lvl==1){fichier = fopen("map/map.map","r");}
if (lvl==2){fichier = fopen("map/map2.map","r");}
if (lvl==3){fichier = fopen("map/map3.map","r");}
if (lvl==4){fichier = fopen("map/map4.map","r");}
if (lvl==5){fichier = fopen("map/map5.map","r");}
if (lvl==6){fichier = fopen("map/map6.map","r");}
if (lvl==7){fichier = fopen("map/map7.map","r");}
if (lvl==8){fichier = fopen("map/map8.map","r");}
if (lvl==9){fichier = fopen("map/map9.map","r");}
if (lvl==10){fichier = fopen("map/map10.map","r");}
if (lvl==11){fichier = fopen("map/map11.map","r");}
if (lvl==12){fichier = fopen("map/map12.map","r");}
if (lvl==13){fichier = fopen("map/map13.map","r");}
if (lvl==14){fichier = fopen("map/map14.map","r");}
if (lvl==15){fichier = fopen("map/map15.map","r");}
if (lvl==16){fichier = fopen("map/map16.map","r");}
if (lvl==17){fichier = fopen("map/map17.map","r");}
if (lvl==18){fichier = fopen("map/map18.map","r");}
if (lvl==19){fichier = fopen("map/map19.map","r");}
if (lvl==20){fichier = fopen("map/map20.map","r");}
if (lvl==21){fichier = fopen("map/map21.map","r");}
if (lvl==22){fichier = fopen("map/map22.map","r");}
if (lvl==23){fichier = fopen("map/map23.map","r");}
if (lvl==24){fichier = fopen("map/map24.map","r");}
if (lvl==25){fichier = fopen("map/map25.map","r");}
if (lvl==26){fichier = fopen("map/map26.map","r");}
if (lvl==27){fichier = fopen("map/map27.map","r");}
if (lvl==28){fichier = fopen("map/map28.map","r");}
if (lvl==29){fichier = fopen("map/map29.map","r");}
if (lvl==30){fichier = fopen("map/map30.map","r");}
if (lvl==31){fichier = fopen("map/map31.map","r");}

nb1=0;
comptP=0;
comptW=0;
mb2=0;
mb=0;
k=0;
j=0;
pts=0;
nb=0;
p=0;
mvtR=0;
for(i=0;i<NBP;i++)
{P[i].x=0;P[i].y=0;}
for(i=0;i<WT;i++)
{W[i].x=0;W[i].y=0;}
for(i=0;i<mob;i++)
{pm[i].x=8000;pm[i].y=8000;
pm2[i].x=8000;pm2[i].y=8000;}

if (fichier==NULL)
{
    continuerG=-1;
}
        mapx=0;
        mapy=0;
    if (fichier != NULL)
    {

        i=0;
        do
        {

               a = fgetc(fichier);
               if(a=='c')
               {pp1.x=30*j;pp1.y=30*k;j++;}
               if (a=='1')
                {W[comptW].x=30*j;W[comptW].y=30*k;j++;comptW=comptW+1;}
               if (a=='0')
               {P[nb].x=30*j;P[nb].y=30*k;j++;nb++;}
               if (a=='2')
               {k++;j=0;}
               if(a=='3')
               {pm[mb].x=30*j;pm[mb].y=30*k;mb++;}
               if(a=='4')
               {pm2[mb2].x=30*j;pm2[mb2].y=30*k;mb2++;}
               if(a=='b')
               {pb1[nb1].x=30*j;pb1[nb1].y=30*k;nb1++;}
               if(a=='p')
               {piment[p].x=30*j;piment[p].y=30*k;p++;j++;}
               i++;
               if(a=='v')
               {j++;}
               if(j>mapx){mapx=j;}
               if(k>mapy){mapy=k;}
        } while (a != EOF);

        fclose(fichier);
    }
Sx=0;Sy=0;
SAx=0;SAy=0;
mapx=mapx*30;
mapy=mapy*30;
pp1.x=30;
pp1.y=30;
if(mapx>600){mapx=600;SAx=1;}
if(mapy>600){mapy=600;SAy=1;}
if(SAx==1){pp1.x=mapx/2;Sx=-pp1.x+30;}
if(SAy==1){pp1.y=mapy/2;Sy=-pp1.y+30;}
ecran = SDL_SetVideoMode(mapx, mapy, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
speed=1;
P[0].x=Xfenetre+60;P[0].y=Yfenetre+60;pts=1;
for (i=0;i<mob;i++){b2[i]=1;}
for(i=0;i<mob;i++){bdf[i].x=8000;bdf[i].y=8000;}
ammo=0;
chaine[0]='C';chaine[1]='u';chaine[2]='r';chaine[3]='r';chaine[4]='e';chaine[5]='n';chaine[6]='t';chaine[7]=' ';
chaine[8]='l';chaine[9]='e';chaine[10]='v';chaine[11]='e';chaine[12]='l';chaine[13]=' ';chaine[14]=':';chaine[15]=' ';
chaine[16]='0'+(lvl/100);chaine[17]='0'+(lvl/10);if(lvl>=10){lvl=lvl-10;chaine[18]='0'+lvl;lvl=lvl+10;}else{chaine[18]='0'+lvl;}
timer=0;timer2=0;

Lvl.x=mapx-150;Lvl.y=5;
fireball.x=mapx-150;fireball.y=19;

LVL=TTF_RenderText_Blended(police,chaine,noir);
Fireball[11]='0';
c=hasard(3)+1;

while (continuerG==1)
{
Fireball[11]='0'+ammo;
FIREBALL=TTF_RenderText_Blended(police,Fireball,noir);
time(&timer);
time(&timer2);

if(mvtR>0)
{
if(direction==1){pp1.y=pp1.y-30;
                if ((pp1.y>=0)&&(mur(pp1,W,comptW)==0))
                {bouton1 = SDL_LoadBMP("img/U.bmp");direction=1;
                if(SAy==1){Sy=Sy-30;pp1.y=pp1.y+30;}}
                else {pp1.y=pp1.y+30;}
                if (col(pp1,pm[i])==1){continuerG =0;perdu=1;}
                while((a=(CP(pp1,P,nb+1)))!=-1){P[a].x=Xfenetre+30;P[a].y=Yfenetre+30;pts++;}
                if((pts==nb)&&(continuerG!=-1)){continuerG=0;perdu=-1;}}
if(direction==2){pp1.x=pp1.x-30;
                if ((pp1.x>=0)&&(mur(pp1,W,comptW)==0))
                {bouton1 = SDL_LoadBMP("img/L.bmp");direction=2;
                if(SAx==1){Sx=Sx-30;pp1.x=pp1.x+30;}}
                else {pp1.x=pp1.x+30;}
                if (col(pp1,pm[i])==1){continuerG =0;perdu=1;}
                while ((a=(CP(pp1,P,nb+1)))!=-1){P[a].x=Xfenetre+30;P[a].y=Yfenetre+30;pts++;}
                if((pts==nb)&&(continuerG!=-1)){continuerG=0;perdu=-1;}}
if(direction==3){pp1.y=pp1.y+30;
                if((pp1.y<Yfenetre-30)&&(mur(pp1,W,comptW)==0))
                {bouton1 = SDL_LoadBMP("img/D.bmp");direction=3;
                if(SAy==1){Sy=Sy+30;pp1.y=pp1.y-30;}}
                else {pp1.y=pp1.y-30;}
                if (col(pp1,pm[i])==1){continuerG =0;perdu=1;}
                while ((a=(CP(pp1,P,nb+1)))!=-1){P[a].x=Xfenetre+30;P[a].y=Yfenetre+30;pts++;}
                if((pts==nb)&&(continuerG!=-1)){continuerG=0;perdu=-1;}}
if(direction==4){pp1.x=pp1.x+30;
                if ((pp1.x<Xfenetre-30)&&(mur(pp1,W,comptW)==0))
                {bouton1 = SDL_LoadBMP("img/R.bmp");direction=4;
                if(SAx==1){Sx=Sx+30;pp1.x=pp1.x-30;}}
                else {pp1.x=pp1.x-30;}
                if (col(pp1,pm[i])==1)
                {continuerG =0;perdu=1;}
                while ((a=(CP(pp1,P,nb+1)))!=-1){P[a].x=Xfenetre+30;P[a].y=Yfenetre+30;pts++;}
                if((pts==nb)&&(continuerG!=-1)){continuerG=0;perdu=-1;}}
mvtR--;
}

for(i=0;i<mob;i++)
{

if(directionB[i]!=0){
if (directionB[i]==1){bdf[i].y=bdf[i].y-30;}
else if (directionB[i]==2){bdf[i].x=bdf[i].x-30;}
else if (directionB[i]==3){bdf[i].y=bdf[i].y+30;}
else if (directionB[i]==4){bdf[i].x=bdf[i].x+30;}
if(mur(bdf[i],W,comptW)==1){bdf[i].x=6000;bdf[i].y=6000;directionB[i]=0;}}
    for(i2=0;i2<mob;i2++)
    {
        if(col(bdf[i],pm[i2])==1){pm[i2].x=6000;pm[i2].y=6000;}
    }

if(i<mb)
{
b=Mouvement(pm[i],W,b);
if (b==1){for(i2=0;i2<10;i2++){pm[i].y=pm[i].y-3;if(mur(pm[i],W,comptW+1)==1){pm[i].y=pm[i].y+3;}
else{if((pm[i].x>=0)&&(pm[i].y>=0)){SDL_BlitSurface(mob1,NULL,ecran,&pm[i]);SDL_Flip(ecran);}}}}//else{pm[i].y=pm[i].y+1;}//else{pm1.y=pm1.y+29;}}/*monte*/
if (b==2){for(i2=0;i2<10;i2++){pm[i].x=pm[i].x-3;if(mur(pm[i],W,comptW+1)==1){pm[i].x=pm[i].x+3;}
else{if((pm[i].x>=0)&&(pm[i].y>=0)){SDL_BlitSurface(mob1,NULL,ecran,&pm[i]);SDL_Flip(ecran);}}}}
if (b==3){for(i2=0;i2<10;i2++){pm[i].y=pm[i].y+3;if(mur(pm[i],W,comptW+1)==1){pm[i].y=pm[i].y-3;}
else if((pm[i].x>=0)&&(pm[i].y>=0)){SDL_BlitSurface(mob1,NULL,ecran,&pm[i]);SDL_Flip(ecran);}}}//else{pm[i].y=pm[i].y-1;}//else{pm1.y=pm1.y-29;}}/*Descent*/
if (b==4){for(i2=0;i2<10;i2++){pm[i].x=pm[i].x+3;if(mur(pm[i],W,comptW+1)==1){pm[i].x=pm[i].x-3;}
else if((pm[i].x>=0)&&(pm[i].y>=0)){SDL_BlitSurface(mob1,NULL,ecran,&pm[i]);SDL_Flip(ecran);}}}//else{pm[i].x=pm[i].y-1;}//else{pm1.x=pm1.x-29;}}/*Droite*/
}

if(i<mb2){
if(b2[i]==1){for(i2=0;i2<6;i2++){pm2[i].y=pm2[i].y-5;if(mur(pm2[i],W,comptW)==1){b2[i]=4;pm2[i].y=pm2[i].y+5;}}}
else if(b2[i]==2){for(i2=0;i2<6;i2++){pm2[i].x=pm2[i].x-5;if(mur(pm2[i],W,comptW)==1){b2[i]=1;pm2[i].x=pm2[i].x+5;}}}
else if(b2[i]==3){for(i2=0;i2<6;i2++){pm2[i].y=pm2[i].y+5;if(mur(pm2[i],W,comptW)==1){b2[i]=2;pm2[i].y=pm2[i].y-5;}}}
else if(b2[i]==4){for(i2=0;i2<6;i2++){pm2[i].x=pm2[i].x+5;if(mur(pm2[i],W,comptW)==1){b2[i]=3;pm2[i].x=pm2[i].x-5;}}}
if (col(pp1,pm2[i])==1){continuerG =0;perdu=1;}}
        if (col(pp1,pm[i])==1)
    {continuerG =0;perdu=1;}

if(i<p)
{
    if(col(pp1,piment[i])==1){piment[i].x=6000;piment[i].y=6000;ammo=ammo+2;}
}

if(i<nb1){
if(c==1){pb1[i].x=pb1[i].x+1;pb1[i].y=pb1[i].y-1;if(mur(pb1[i],W,comptW)==1){pb1[i].x-1;pb1[i].y+1;c=4;}}
if(c==2){pb1[i].x=pb1[i].x+1;pb1[i].y=pb1[i].y+1;if(mur(pb1[i],W,comptW)==1){pb1[i].x-1;pb1[i].y-1;c=3;}}
if(c==3){pb1[i].x=pb1[i].x-1;pb1[i].y=pb1[i].y+1;if(mur(pb1[i],W,comptW)==1){pb1[i].x+1;pb1[i].y-1;c=2;}}
if(c==4){pb1[i].x=pb1[i].x-1;pb1[i].y=pb1[i].y-1;if(mur(pb1[i],W,comptW)==1){pb1[i].x+1;pb1[i].y+1;c=1;}}
}

}

SDL_PollEvent(&event);

  if ((a=(CP(pp1,P,nb)))!=-1){P[a].x=Xfenetre+30;P[a].y=Yfenetre+30;pts++;}
  if((pts==nb)&&(continuerG!=-1)){continuerG=0;perdu=-1;}

        if(event.type == SDL_KEYDOWN)
        {
        //SDL_WaitEvent(&event);
        switch(event.type)
        {

        case SDL_KEYDOWN:

            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
            menu=1;
            continuerG=0;
            continuerL=1;
            break;

            case SDLK_SPACE:
            if(ammo>0)
            {
            for(i=0;i<mob;i++){if(directionB[i]==0){i=i+mob+1;}}
            if(i>mob){i=i-mob-1;bdf[i].x=pp1.x;bdf[i].y=pp1.y;directionB[i]=direction;ammo--;}
            }
            break;

            case SDLK_UP:
                if(speed!=1){mvtR--;}
                pp1.y=pp1.y-30;
                if ((pp1.y>=0)&&(mur(pp1,W,comptW)==0))
                {bouton1 = SDL_LoadBMP("img/U.bmp");direction=1;
                if(SAy==1){if(pp1.y<200){
                Sy=Sy-30;pp1.y=pp1.y+30;}}}
                else {pp1.y=pp1.y+30;}
                if (col(pp1,pm[i])==1){continuerG =0;perdu=1;}
                while((a=(CP(pp1,P,nb+1)))!=-1){P[a].x=Xfenetre+30;P[a].y=Yfenetre+30;pts++;}
                if((pts==nb)&&(continuerG!=-1)){continuerG=0;perdu=-1;}
                break;

            case SDLK_LEFT:
                if(speed!=1){mvtR--;}
                pp1.x=pp1.x-30;
                if ((pp1.x>=0)&&(mur(pp1,W,comptW)==0))
                {bouton1 = SDL_LoadBMP("img/L.bmp");direction=2;
                if(SAx==1){if(pp1.x<200){
                Sx=Sx-30;pp1.x=pp1.x+30;}}}
                else {pp1.x=pp1.x+30;}
                if (col(pp1,pm[i])==1){continuerG =0;perdu=1;}
                while ((a=(CP(pp1,P,nb+1)))!=-1){P[a].x=Xfenetre+30;P[a].y=Yfenetre+30;pts++;}
                if((pts==nb)&&(continuerG!=-1)){continuerG=0;perdu=-1;}
                break;

            case SDLK_RIGHT:
                if(speed!=1){mvtR--;}
                pp1.x=pp1.x+30;
                if ((pp1.x<Xfenetre-30)&&(mur(pp1,W,comptW)==0))
                {bouton1 = SDL_LoadBMP("img/R.bmp");direction=4;
                if(SAx==1){if(pp1.x>400){
                Sx=Sx+30;pp1.x=pp1.x-30;}}}
                else {pp1.x=pp1.x-30;}
                if (col(pp1,pm[i])==1)
                {continuerG =0;perdu=1;}
                while ((a=(CP(pp1,P,nb+1)))!=-1){P[a].x=Xfenetre+30;P[a].y=Yfenetre+30;pts++;}
                if((pts==nb)&&(continuerG!=-1)){continuerG=0;perdu=-1;}
                break;

            case SDLK_DOWN:
                if(speed!=1){mvtR--;}
                pp1.y=pp1.y+30;
                if((pp1.y<Yfenetre-30)&&(mur(pp1,W,comptW)==0))
                {bouton1 = SDL_LoadBMP("img/D.bmp");direction=3;
                if(SAy==1){if(pp1.y>400){
                Sy=Sy+30;pp1.y=pp1.y-30;}}}
                else {pp1.y=pp1.y-30;}
                if (col(pp1,pm[i])==1){continuerG =0;perdu=1;}
                while ((a=(CP(pp1,P,nb+1)))!=-1){P[a].x=Xfenetre+30;P[a].y=Yfenetre+30;pts++;}
                if((pts==nb)&&(continuerG!=-1)){continuerG=0;perdu=-1;}
                break;

            }
        break;
        }
        event.type=NULL;
        }
SDL_SetColorKey(bouton1, SDL_SRCCOLORKEY, SDL_MapRGB(bouton1->format, 255, 255, 255));
SDL_SetColorKey(mob1, SDL_SRCCOLORKEY, SDL_MapRGB(mob1->format, 255, 255, 255));
SDL_SetColorKey(piece,SDL_SRCCOLORKEY, SDL_MapRGB(piece->format,255,255,255));
SDL_SetColorKey(mob2,SDL_SRCCOLORKEY, SDL_MapRGB(mob2->format,255,255,255));
SDL_SetColorKey(PIMENT,SDL_SRCCOLORKEY, SDL_MapRGB(PIMENT->format,255,255,255));
SDL_SetColorKey(BDF,SDL_SRCCOLORKEY, SDL_MapRGB(BDF->format,255,255,255));

if (perdu!=1){SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,17,206,112));}


for(i=0;((i<=nb)||(i<=comptW));i++)
{
if(i<comptW){W[i].x=W[i].x-Sx;W[i].y=W[i].y-Sy;
if((W[i].x>=0)&&(W[i].y>=0)){SDL_BlitSurface(Wall,NULL,ecran,&W[i]);}}
if(i<nb) {P[i].x=P[i].x-Sx;P[i].y=P[i].y-Sy;
if((P[i].x>=0)&&(P[i].y>=0)){SDL_BlitSurface(piece,NULL,ecran,&P[i]);}}
if(i<p){piment[i].x=piment[i].x-Sx;piment[i].y=piment[i].y-Sy;
if((piment[i].x>=0)&&(piment[i].y>=0)){SDL_BlitSurface(PIMENT,NULL,ecran,&piment[i]);}}
}
for(i=0;i<mob;i++)
{
if(i<mob){pm[i].x=pm[i].x-Sx;pm[i].y=pm[i].y-Sy;
if((pm[i].x>=0)&&(pm[i].y>=0)){SDL_BlitSurface(mob1,NULL,ecran,&pm[i]);}
pm2[i].x=pm2[i].x-Sx;pm2[i].y=pm2[i].y-Sy;
if((pm2[i].x>=0)&&(pm2[i].y>=0)){SDL_BlitSurface(mob2,NULL,ecran,&pm2[i]);}
pb1[i].x=pb1[i].x-Sx;pb1[i].y=pb1[i].y-Sy;
if((pb1[i].x>=0)&&(pb1[i].y>=0)){SDL_BlitSurface(BOSS1,NULL,ecran,&pb1[i]);}
if(i<mob){bdf[i].x=bdf[i].x-Sx;bdf[i].y=bdf[i].y-Sy;
if((bdf[i].x>=0)&&(bdf[i].y>=0)){SDL_BlitSurface(BDF,NULL,ecran,&bdf[i]);}}
}
}

Sx=0;Sy=0;

SDL_BlitSurface(bouton1,NULL,ecran,&pp1);

if((W[0].x>=0)&&(W[0].y>=0)){SDL_BlitSurface(Wall,NULL,ecran,&W[0]);}

SDL_BlitSurface(LVL,NULL,ecran,&Lvl);
SDL_BlitSurface(FIREBALL,NULL,ecran,&fireball);
SDL_Flip(ecran);
time(&timer);
timer=timer-timer2;
if(timer<60){SDL_Delay(60-timer);}
}


while(perdu==1)
{
SDL_Delay(1500);
for(i=0;i<mob;i++)
{
pm[i].x=Xfenetre+30;pm[i].y=Yfenetre+30;
}
pp1.x=Xfenetre+30;pp1.y=Yfenetre+30;
for (i=0;i<comptW;i++)
{
if(i<nb){P[i].x=Xfenetre+30;P[i].y=Yfenetre+30;}
W[i].x=Xfenetre+30;W[i].y=Yfenetre+30;
}
SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));

for(i=0;i<WT;i++)
{
if(i<NBP) {SDL_BlitSurface(piece,NULL,ecran,&P[i]);}
SDL_BlitSurface(Wall,NULL,ecran,&W[i]);
}
ecran = SDL_SetVideoMode(750, 421, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_NOFRAME );

GO=SDL_LoadBMP("img/GO.bmp");

SDL_BlitSurface(GO,NULL,ecran,&go);
SDL_BlitSurface(bouton1,NULL,ecran,&pp1);
SDL_BlitSurface(mob1,NULL,ecran,&pm[0]);
SDL_BlitSurface(mob1,NULL,ecran,&pm[1]);
SDL_BlitSurface(mob1,NULL,ecran,&pm[2]);
SDL_BlitSurface(mob1,NULL,ecran,&pm[3]);
SDL_BlitSurface(mob1,NULL,ecran,&pm[4]);
SDL_BlitSurface(mob1,NULL,ecran,&pm[5]);
SDL_BlitSurface(mob1,NULL,ecran,&pm[6]);
SDL_BlitSurface(mob1,NULL,ecran,&pm[7]);
SDL_BlitSurface(mob1,NULL,ecran,&pm[8]);
SDL_BlitSurface(mob1,NULL,ecran,&pm[9]);
SDL_Flip(ecran);
SDL_Delay(1000);
continuerL=1;
menu=1;
perdu=0;
}

if (perdu==-1)
{
lvl++;
continuerG =1;
continuerL =1;
perdu=0;
}
while (continuerG==-1)
{
SDL_Delay(1000);
menu=1;
continuerG=1;
lvl=1;
}


}
SDL_FreeSurface(bouton1);
SDL_FreeSurface(Wall);
TTF_CloseFont(police);
TTF_Quit();
SDL_Quit();
return 0;
}
