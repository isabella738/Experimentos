/*
    https://exame.com/tecnologia/como-vencer-qualquer-um-no-pedra-papel-tesoura/
    https://www.wikihow.com/Win-at-Rock,-Paper,-Scissors

    O algoritmo se baseia nos seguintes pontos:
    
    - Jogadores vencedores tendem a manter o mesmo símbolo.
    - Jogadores perdedores tendem a trocar na sequência ‘pedra-papel-tesoura’
    - Homens costumam iniciar com pedra
    - Mulheres costumam iniciar com tesoura
    - Jogadores tendem a jogar pedra depois de perderem muitas vezes.
    - Pedra é a jogada mais feita. Em último caso, jogue papel.

    O projeto ainda está em desenvolvimento.

    0 = pedra, 1 = papel, 2 = tesoura
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define PEDRA "\U0001FAA8 "
#define PAPEL "\U0001F4C4"
#define TESOURA "✂️"

char jogada[][8] = {
    "PEDRA",
    "PAPEL",
    "TESOURA"
};

char result[][12] = {
    "empata com",
    "vence",
    "perde para"
};

char emoji[][8] = {
    PEDRA,
    PAPEL,
    TESOURA
};

int genero;
int historico[100][3] = {0}; //guarda jogada do humano, da maquina, e o resultado, na ordem
int rodada;

int resultado(int a, int b){
    if(a == b) return 0;
    if(a == 0){
        if(b == 1) return 2;
        return 1;
    }
    if(a == 1){
        if(b == 0) return 1;
        return 2;
    }
    if(b == 0) return 2;
    return 1;
}

void retomar_partida(int i, int *a, int *b, int *r){
    (*a) = historico[rodada-i][0];
    (*b) = historico[rodada-i][1];
    (*r) = historico[rodada-i][2];
}

int oposto(int n){
    if(n == 2) return 0;
    return n+1;
}

int jogada_maquina(){
    int a, b, r;
    if(rodada == 0){
        if(genero == 2) return 0;
        return 1;
    }

    retomar_partida(1, &a, &b, &r);
    if(r == 1){//se humano ganhou, vai repetir a jogada
        return oposto(a);
    }
    if(r == 2){//se perdeu, vai escolher o proximo
        (a < 2) ? (a += 1) : (a = 0);
        return oposto(a);
    }

    return 1;
};

int main(){
    srand(time(NULL));
    rodada = 0;

    printf("PEDRA %s\nPAPEL %s\nTESOURA %s\n\n", PEDRA, PAPEL, TESOURA);

    printf(
        "Você é:\n"
        "[0] Prefiro não informar.\n"
        "[1] Homem\n"
        "[2] Mulher\n"
        "> "
    );
    scanf("%d", &genero);

    //
    int humano=0, maquina=0;
    system("clear");
    do{
        printf("PEDRA %s\nPAPEL %s\nTESOURA %s\n\n", PEDRA, PAPEL, TESOURA);
        printf("Rodada %d\n", rodada+1);
        printf("Você %d X %d Máquina\n\n", humano, maquina);

        printf("Sua jogada (1, 2 ou 3): ");
        
        int a; scanf("%d", &a); a--;
        int b = jogada_maquina();

        int r = resultado(a, b);
        if(r == 1) humano++;
        if(r == 2) maquina++;

        memcpy(historico[rodada], (int[3]){a, b, r}, sizeof(historico[rodada]));

        printf("\n%s X %s\n", emoji[a], emoji[b]);
        printf("%s %s %s\n", jogada[a], result[r], jogada[b]);

        printf("\nAperte enter para continuar.\n");
        getchar(); getchar();
        rodada++;

        system("clear");
    }while(1);

    return 0;
}