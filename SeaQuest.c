#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

struct coordenada {
    int x, y, deslocamento;
    char tipo;
};

void gotoxy (int x, int y){
COORD c;
c.X = x-1;
c.Y = y-1;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

char mapa[7][14];
struct coordenada monstros[4];
int px, py,x,y,flag=0,flag2=0;

void randomizaMonstro(){
    int i,j,k=0,AUX,AUX1;
    for(i=0;i<=3;){
        if(i == 0){
            monstros[i].x = 0;
            monstros[i].tipo = 'B';
        }
        else{
            monstros[i].tipo = 'T';
            AUX = (rand()%7);
            monstros[i].x = AUX;
            for(j=0;j<=3;j++){
                if((AUX == monstros[j].x)||(AUX == 0)){
                    k++;
                }
            }
        }
        if(k < 2){
            AUX1 = (rand()%2);
            if(AUX1 == 0){
                monstros[i].y = 13;
                monstros[i].deslocamento = -1;
            }
            else{
                monstros[i].y = 0;
                monstros[i].deslocamento = 1;
            }
            i++;
        }
        k = 0;
    }
}

void movimentaMonstro(){
    int i;
    for(i=0;i<=3;i++){
        monstros[i].y += (monstros[i].deslocamento);
        if(i == 0){
            mapa[monstros[i].x][monstros[i].y] = 'B';
        }
        else{
            mapa[monstros[i].x][monstros[i].y] = 'T';
        }
        mapa[monstros[i].x][monstros[i].y - (monstros[i].deslocamento)] = '°';
        if((monstros[i].y == 0)||(monstros[i].y == 13)){
            monstros[i].deslocamento *= -1;
        }
    }
}

void verificaColisoes(){
    int i;
    for(i=0;i<=3;i++){
        if((monstros[i].x == px)&&(monstros[i].y == py)){
            flag = 1;
        }
    }
}

void tiroBarco(){
    char bomba='*';
    if(flag2==0){
        if((monstros[0].y)==(py)){
            x = monstros[0].x;
            y = monstros[0].y;
            mapa[x+1][y] = bomba;
            flag2=1;
        }
    }
    else{
        if(x<=6){
           x++;
           mapa[x][y] = bomba;
           mapa[x-1][y] = '°';
        }
    }
    if(x==6){
            mapa[x][y]='°';
            x=0;
            flag2=0;
        }
}

void inicia_Mapa(){
    int l, c;
    for(l=0;l<7;l++){
        for(c=0;c<14;c++){
            mapa[l][c] = '°';
        }
    }
}

void mostra_Mapa(){
    int l, c;
    for(l=0;l<7;l++){
        for(c=0;c<14;c++){
            gotoxy(33+c,8+l);
            printf("%c", mapa[l][c]);
        }
    }
}

    void Moldura(){;
        int i;
        gotoxy(32, 7);
        printf("%c", 201); // ╔
        gotoxy(47, 15);
        printf("%c", 188); // ╝
        gotoxy(47, 7);
        printf("%c", 187); // ╗
        gotoxy(32, 15);
        printf("%c", 200); // ╚
        for(i = 0 ; i <= 13 ; i++){
            gotoxy(33+i, 7);
            printf("%c", 205); // ═
            gotoxy(33+i, 15);
            printf("%c", 205); // ═
            if(i<=6){
            gotoxy(32, 8+i);
            printf("%c", 186); // ║
            gotoxy(47, 8+i);
            printf("%c", 186); // ║
            }
        }
    }

main(){
    char tecla;
    int cont=0;
    px = 3;
    py = 6;
    srand (time(NULL));
    inicia_Mapa();
    mapa[px][py]='\0';
    Moldura();
    randomizaMonstro();
    do{
        mostra_Mapa();
        if(kbhit()){
            tecla = getch();
            mapa[px][py] = '°';
            switch(tecla){
                case 'w': if(px>0){
                    px--;
                } break;
                case 's': if(px<6){
                    px++;
                } break;
                case 'd': if(py<13){
                    py++;
                } break;
                case 'a': if(py>0){
                    py--;
                } break;
            }
        }
        mapa[px][py] = 'P';
        for(cont=0;cont<=16450000;cont++){
            if(cont%16450000000==0){
                movimentaMonstro();
                tiroBarco();
            }
        }
        gotoxy(1, 1);
        printf("%d\n%d",x,y);
        verificaColisoes();
    }while((tecla != 27)&&(flag != 1));
}
