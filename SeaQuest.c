#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

struct coordenada {
    int x, y, deslocamento;
};

void gotoxy (int x, int y){
COORD c;
c.X = x-1;
c.Y = y-1;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

char mapa[7][14];
struct coordenada monstros[3];
int px, py;


void randomizaMonstro(){
    int i;
    srand (time(NULL));
    for(i=0;i<=2;i++){
        monstros[i].x = (rand()%5) + 1;
        if((i%2) == 0){
            monstros[i].y = 13;
            monstros[i].deslocamento = -1;
        }
        else{
            monstros[i].y = 0;
            monstros[i].deslocamento = 1;
        }
    }
}

void movimentaMonstro(){
    int i,x,y,des;
    for(i=0;i<=2;i++){
        x = monstros[i].x;
        y = monstros[i].y;
        des = monstros[i].deslocamento;
        y = y + (des);
        monstros[i].y = y;
        mapa[x][y] = 'T';
        mapa[x][y-(des)] = '°';
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
    px = py = 3;
    inicia_Mapa();
    mapa[px][py]='\0';
    Moldura();
    randomizaMonstro();
    do{
        mostra_Mapa();
        tecla = getch();
        mapa[px][py] = '°';
        switch(tecla){
            case 'w': if((px>0)&&(py>=0)){
                px--;
            } break;
            case 's': if((px<6)&&(py<=13)){
                px++;
            } break;
            case 'd': if((px>=0)&&(py<13)){
                py++;
            } break;
            case 'a': if((px>=0)&&(py>0)){
                py--;
            } break;
        }
        mapa[px][py] = 'P';
        movimentaMonstro();
        //verificaColisoes();
    }while(tecla != 27);
}
