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
int px, py,flag=0;

void randomizaMonstro(){
    int i,j,k=0,AUX,AUX1;
    for(i=0;i<=2;){
        AUX = (rand()%6);
        monstros[i].x = AUX;
        for(j=0;j<=2;j++){
            if(AUX == monstros[j].x){
                k++;
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
    for(i=0;i<=2;i++){
        monstros[i].y += (monstros[i].deslocamento);
        mapa[monstros[i].x][monstros[i].y] = 'T';
        mapa[monstros[i].x][monstros[i].y - (monstros[i].deslocamento)] = '°';
        if(monstros[i].y == 0){
            monstros[i].deslocamento = 1;
        }
        else{
            if(monstros[i].y == 13){
                monstros[i].deslocamento = -1;
            }
        }
    }
}

void verificaColisoes(){
    int i;
    for(i=0;i<=2;i++){
        if((monstros[i].x == px)&&(monstros[i].y == py)){
            flag = 1;
        }
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
    srand (time(NULL));
    inicia_Mapa();
    mapa[px][py]='\0';
    Moldura();
    randomizaMonstro();
    do{
        mostra_Mapa();
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
        mapa[px][py] = 'P';
        movimentaMonstro();
        verificaColisoes();
    }while((tecla != 27)&&(flag != 1));
}
