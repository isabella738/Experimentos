/*
    Como definem as regras do jogo da vida:
    1. Celulas com 1 ou nenhum vizinho morrem
    2. Celulas com 4 ou mais vizinhos morrem 
    3. Celulas com 2 ou 3 vizinhos sobrevivem
    4. Toda celula vazia com 3 vizinhos se torna habitada

    Comandos:
    awsd: andar pelas casas
    k: marcar uma casa
    j: começar
*/

#include <stdio.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>//verifica se houve tecla
#define RESET  "\033[0m"
#define CINZA "\033[90m"

struct termios velho_terminal, novo_terminal;
void mudar_terminal(){
    tcgetattr(STDIN_FILENO, &velho_terminal);
    novo_terminal = velho_terminal;

    novo_terminal.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &novo_terminal);
}
void restaurar_terminal(){
    tcsetattr(STDIN_FILENO, TCSANOW, &velho_terminal);
}

typedef struct{
    int x, y;
}coordenada;

char mapa[15][26]={
    ".........................",
    ".........................",
    ".........................",
    ".........................",
    ".........................",
    ".........................",
    ".........................",
    ".........................",
    ".........................",
    ".........................",
    ".........................",
    ".........................",
    ".........................",
    ".........................",
    ".........................",
};

int vizinhos(int x, int y){
    int contador = 0;

    if(x < 24 && mapa[y][x+1]=='O') contador++;
    if(x > 0  && mapa[y][x-1]=='O') contador++;

    if(y < 14 && mapa[y+1][x]=='O') contador++;
    if(y > 0  && mapa[y-1][x]=='O') contador++;

    if(x < 24 && y < 14 && mapa[y+1][x+1]=='O') contador++;
    if(x < 24 && y > 0  && mapa[y-1][x+1]=='O') contador++;
    if(x > 0  && y < 14 && mapa[y+1][x-1]=='O') contador++;
    if(x > 0  && y > 0  && mapa[y-1][x-1]=='O') contador++;

    return contador;
}

int main(){
    mudar_terminal();
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
    coordenada user;
    user.x=0; user.y=0;
    
    do{
        usleep(100000);
        printf("\033[H");
        int marcar=0, comecar=0;

        char comando;
        if(read(STDIN_FILENO, &comando, 1) > 0){
            switch(comando){
                case 'a': if(user.x>0) user.x--; break;
                case 'd': if(user.x<24) user.x++; break;
                case 's': if(user.y<24) user.y++; break;
                case 'w': if(user.y>0) user.y--; break;
                case 'k': marcar = 1; break;
                case 'l': comecar=1; break;
            }
        }
        if(comecar)break;

        if(marcar) mapa[user.y][user.x]='O';

        for(int y=0; y<15; y++){
            for(int x=0; x<25; x++){
                if(x==user.x && y==user.y) printf("%c", mapa[y][x]);
                else printf(CINZA"%c"RESET, mapa[y][x]);
            }
            printf("\n");
        }


    }while(1);

    restaurar_terminal();

    //Algoritmo de fato
    do{ 
        printf("\033[H"); 
        coordenada mortes[15*25], vidas[15*25];
        int m=0, v=0;

        for(int y=0; y<15; y++){
            for(int x=0; x<25; x++){
                int morrer=0, viver=0;
                int n = vizinhos(x, y);

                if(mapa[y][x]=='O'){
                    if(n<2) morrer=1; //1. Um ou nenhum vizinho
                    else if (n>=4) morrer=1; //2. 4 ou mais vizinhos
                }
                else{
                    if(n==3) viver=1; //4
                }

                if(morrer){ mortes[m].x=x; mortes[m].y=y; m++;}
                if(viver){ vidas[v].x=x; vidas[v].y=y; v++;}
            }
        }

        for(int i=0; i<m; i++){
            int x = mortes[i].x, y = mortes[i].y;
            mapa[y][x]='.';
        }
        for(int i=0; i<v; i++){
            int x = vidas[i].x, y = vidas[i].y;
            mapa[y][x]='O';
        }


        //Impressão
        for(int y=0; y<15; y++){
            for(int x=0; x<25; x++){
                printf("%c", mapa[y][x]);
            }
            printf("\n");
        }
        usleep(1000000);

    }while(1);

    
}
