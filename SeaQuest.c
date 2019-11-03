#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

void gotoxy (int x, int y){
COORD c;
c.X = x-1;
c.Y = y-1;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

char mapa[7][14];
int px, py;

void inicia_Mapa(){
    int l, c;
    for(l=0;l<7;l++){
        for(c=0;c<14;c++){
            mapa[l][c] = 'A';
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
    do{
        mostra_Mapa();
        tecla = getch();
        mapa[px][py] = 'A';
        switch(tecla){
            case 'w': px--; break;
            case 's': px++; break;
            case 'd': py++; break;
            case 'a': py--; break;
        }
        mapa[px][py] = 'P';
    }while(tecla != 27);
}
