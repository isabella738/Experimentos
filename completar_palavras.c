/*
    Este algoritmo se propõe a imitar o comportamento de uma Inteligência Artificial (a MUITO grosso modo)

    Com base em um banco de frases, o algoritmo pega uma palavra e calcula qual palavra é mais provável de vir depois dela,
    depois faz o mesmo com esta nova, até formar uma frase.

    Este projeto ainda será melhorado.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 500
#define TAM 150

void tratar(char p[]){
    int x = strlen(p);
    p[x] = ' ';
    p[x+1] = '\0';

    for(int i=strlen(p); i>=0; i--){
        p[i+1] = p[i];
    }
    p[0] = ' ';

}

int main(){

    FILE *arq = fopen("banco_de_frases.txt", "r");
    if(arq == NULL){
        printf("Erro ao abrir arquivo\n");
        return 1;
    }
    char banco[MAX][TAM];
    int total = 0;

    while(total < MAX && fgets(banco[total], TAM, arq) != NULL){
        banco[total][strcspn(banco[total], "\n")] = '\0';
        total++;
    }

    fclose(arq);
    printf("Foram carregadas %d frases\n", total);
    srand(time(NULL));

    if(total == 0){
        printf("Nenhuma palavra carregada\n");
        return 1;
    }

    //

    printf("Escreva uma palavra: ");
    char palavra[100]; fgets(palavra, 100, stdin);
    palavra[strlen(palavra)-1] = '\0';
    tratar(palavra);

    int loop=20;

    printf("\n%s", palavra);

    while(loop){
        char frase[TAM];

        strcpy(frase, banco[rand()%total]);

        char *p = strstr(frase, palavra);
        if(p != NULL){

            char novo[100]; int n=0;

            p += strlen(palavra);
            while(*p != ' ' && *p != '\0' && *p != '\n'){
                novo[n] = *p;
                p++; n++;
            }
            if(strlen(novo) == 0) continue;
            novo[n] = '\0';
            tratar(novo);
            
            strcpy(palavra, novo);
            printf("%s", palavra);
            loop--;
        }
    }
    printf("\n");

    return 0;
}
