/*
    https://exame.com/tecnologia/como-vencer-qualquer-um-no-pedra-papel-tesoura/
    https://www.wikihow.com/Win-at-Rock,-Paper,-Scissors

    O algoritmo básico se baseia nos seguintes pontos:
    
    - Jogadores vencedores tendem a manter o mesmo símbolo.
    - Jogadores perdedores tendem a trocar na sequência ‘pedra-papel-tesoura’
    - Homens costumam iniciar com pedra
    - Mulheres costumam iniciar com tesoura
    - Jogadores tendem a jogar pedra depois de perderem muitas vezes.
    - Pedra é a jogada mais feita. Em último caso, jogue papel.

    O algoritmo avançado tenta prever a próxima jogada com base nos resultados das partidas anteriores.
    O computador guarda o resultado da partida anterior e a jogada feita na próxima. Ou seja, se na
    partida anterior o humano perdeu jogando tesoura, o computador vai analisar qual jogada ele fez depois
    numa partida anterior do mesmo cenário, então jogar um contra-ataque.
    Por exemplo, se depois de perder com pedra, a jogada mais feita for tesoura, a máquina saberá e jogará 
    papel da próxima vez que o humano perder com pedra.
    Se não houver registro de determinado cenário, o computador realiza o algoritmo básico.

    0 = pedra, 1 = papel, 2 = tesoura
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define PEDRA 0
#define PAPEL 1
#define TESOURA 2

#define EMPATE 0
#define VITORIA 1
#define DERROTA 2

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

char emoji[][9] = {
    "\U0001FAA8 ",
    "\U0001F4C4",
    "✂️"
};

int rodada;
int genero;

//cenarios em relação ao humano
// resultado[jogada nesta partida][jogada na proxima]
int derrota[3][3] = {0};
int vitoria[3][3] = {0};
int empate[3][3] = {0};

int historico[MAX][3] = {0}; //guarda jogada do humano, da maquina, e o resultado, na ordem

int resultado(int a, int b){
    if(a == b) return 0;
    if(a == PEDRA){
        if(b == PAPEL) return 2;
        return 1;
    }
    if(a == PAPEL){
        if(b == PEDRA) return 1;
        return 2;
    }
    if(b == PEDRA) return 2;
    return 1;
}

int contra_ataque(int n){
    return (n == 2) ? 0 : n+1;
}

void processar_historico(int a, int b, int r){
    memcpy(historico[rodada], (int[3]){a, b, r}, sizeof(historico[rodada]));

    if(rodada > 0) switch(historico[rodada-1][2]){
        case EMPATE: empate[historico[rodada-1][0]][a]++; break;
        case VITORIA: vitoria[historico[rodada-1][0]][a]++; break;
        case DERROTA: derrota[historico[rodada-1][0]][a]++; break;
    }
}

int algoritmo_base(){//humano repete se ganha, muda na sequencia se perde. papel por padrão

    if(historico[rodada-1][2] == DERROTA){ //esperar que o humano jogue a proxima da sequencia
        int x = (historico[rodada-1][0]+1 < 3) ? historico[rodada-1][0]+1 : 0;
        return contra_ataque(x);
    }
    if(historico[rodada-1][2] == VITORIA) return contra_ataque(historico[rodada-1][0]); //repetir a ultima se ganhou
    
    int x = rand()%2;
    if(x) return contra_ataque(historico[rodada-1][0]);
    return PAPEL;
}

int jogada_maquina(){
    if(rodada == 0){
        if(genero == 2) return 0;
        return 1;
    }
    if(rodada == 1) return algoritmo_base();

    int maior=0, m=0;
    int x = historico[rodada-1][0];

    switch(historico[rodada-1][2]){
        //ver qual foi a jogada mais feita depois de cada cenario
        case EMPATE: 
            for(int i=0; i<3; i++) if(empate[x][i] > maior){
                maior = empate[x][i]; m = i;
            }
            break;

        case VITORIA: 
            for(int i=0; i<3; i++) if(vitoria[x][i] > maior){
                maior = vitoria[x][i]; m = i;
            }
            break;
            
        case DERROTA:             
            for(int i=0; i<3; i++) if(derrota[x][i] > maior){
                maior = derrota[x][i]; m = i;
            }     
            break;       
    }
    
    if(!maior) return algoritmo_base();
    return contra_ataque(m);
};

int main(){
    srand(time(NULL));
    rodada = 0;

    printf("PEDRA %s\nPAPEL %s\nTESOURA %s\n\n", emoji[PEDRA], emoji[PAPEL], emoji[TESOURA]);

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
        printf(
            "PEDRA %s\n"
            "PAPEL %s\n"
            "TESOURA %s\n"
            "\n"
            "Rodada %d\n"
            "Voce %d x %d Maquina\n"
            "\n"
            "Jogue 1, 2 ou 3. Insira qualquer outra coisa para sair.\n"
            "Sua jogada: ",
            emoji[PEDRA], emoji[PAPEL], emoji[TESOURA], 
            rodada+1, humano, maquina
        );
        
        int a; 
        if(!scanf("%d", &a) || a < 1 || a > 3) break;
        a--;

        int b = jogada_maquina();

        int r = resultado(a, b);
        if(r == VITORIA) humano++;
        if(r == DERROTA) maquina++;

        processar_historico(a, b, r);

        printf("\n%s X %s\n", emoji[a], emoji[b]);
        printf("%s %s %s\n", jogada[a], result[r], jogada[b]);

        printf("\nAperte enter para continuar.\n");
        getchar(); getchar();
        rodada++;
        
        if(rodada >= MAX){
            printf("Calma aí amigo, você já jogou %d vezes, vai descansar um pouco...\n", MAX);
        }

        system("clear");
    }while(1);
    printf("Bom jogo!\n");

    return 0;
}