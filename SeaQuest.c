#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <conio.c>
//#include "conio.c"
//#include <conio2.h>

struct coordenada {
    int x, y, deslocamento;
    char tipo;
};

void menu(){
    int tecla;
    do{
        printf("\n");
        printf("1) Pressione '1' para INICIAR.  \n");
        printf("2) Pressione '2' para ver o RANK.  \n");
        printf("3) Pressione '3' para SAIR.  \n");
        tecla=getch();
        switch(tecla){
                    case '1':
                    sea();
                 break;

                  case '3':
                exit(3);
                return 0;
                  default:
                    menu();
        }
                 //break;}
// }while((tecla != '1')||(tecla != '2')||(tecla != '3'));
  }while(tecla = 0);

}


void gotoxy (int x, int y){
COORD c;
c.X = x-1;
c.Y = y-1;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void HideCursor()
{
  CONSOLE_CURSOR_INFO cursor = {1, FALSE};
  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

char mapa[10][20];
struct coordenada monstros[4];
int px, py,x,y,flag=0,flag2=0;

void randomizaMonstro(){
    int i,j,k=0,AUX,AUX1;
    for(i=0;i<=3;){
        switch(i){
            case 0:
                monstros[i].x = 0;
                monstros[i].tipo = 'B';
                break;
            case 1:
                monstros[i].tipo = 'T';
                AUX = (rand()%10);
                monstros[i].x = AUX;
                for(j=0;j<=3;j++){
                    if((AUX == monstros[j].x)||(AUX == 0)){
                        k++;
                    }
                }
                break;
            default:
                monstros[i].tipo = 'S';
                AUX = (rand()%10);
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
                monstros[i].y = 19;
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
        mapa[monstros[i].x][monstros[i].y] = monstros[i].tipo;
        mapa[monstros[i].x][monstros[i].y - (monstros[i].deslocamento)] = '°';
        if((monstros[i].y == 0)||(monstros[i].y == 19)){
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
        if(x<=9){
           x++;
           mapa[x][y] = bomba;
           mapa[x-1][y] = '°';
        }
    }
    if(x==9){
            mapa[x][y]='°';
            x=0;
            flag2=0;
        }
}

void sea(){

    gotoxy(35, 8);
    system("color 03");
    printf("///// ///// ///// \n");
    gotoxy(35, 9);
    printf("//    //    // // \n");
    gotoxy(35, 10);
    printf("//    //    // //   \n");
    gotoxy(35, 11);
    printf("///// ///// /////     \n");
    gotoxy(35, 12);
    printf("   // //    // //  \n");
    gotoxy(35, 13);
    printf("   // //    // //          \n");
    gotoxy(35, 14);
    printf("///// ///// // //            \n");
    Sleep(3000);
    inicia_Mapa();
}

void inicia_Mapa(){
    close(menu);
    int l, c;
    for(l=0;l<10;l++){
        for(c=0;c<20;c++){
            mapa[l][c] = '°';
        }
    }
}

void mostra_Mapa(){
    int l, c;
    for(l=0;l<10;l++){
        for(c=0;c<20;c++){
            gotoxy(33+c,8+l);
            printf("%c", mapa[l][c]);
        }
    }
}

    void Moldura(){;
        int i;
        gotoxy(32, 7);
        printf("%c", 201); // ╔
        gotoxy(53, 18);
        printf("%c", 188); // ╝
        gotoxy(53, 7);
        printf("%c", 187); // ╗
        gotoxy(32, 18);
        printf("%c", 200); // ╚
        for(i = 0 ; i <= 19 ; i++){
            gotoxy(33+i, 7);
            printf("%c", 205); // ═
            gotoxy(33+i, 18);
            printf("%c", 205); // ═
            if(i<=9){
            gotoxy(32, 8+i);
            printf("%c", 186); // ║
            gotoxy(53, 8+i);
            printf("%c", 186); // ║
            }
        }
    }

main(){
    menu();
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
                case 's': if(px<9){
                    px++;
                } break;
                case 'd': if(py<19){
                    py++;
                } break;
                case 'a': if(py>0){
                    py--;
                } break;
            }
        }
        mapa[px][py] = 'P';
        if(cont%10==0){
           movimentaMonstro();
           tiroBarco();
           cont=0;
        }
        cont++;
        gotoxy(1, 1);
        printf("%d\n%d",x,y);
        verificaColisoes();
        HideCursor();
    }while((tecla != 27)&&(flag != 1));
}
