#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
int main(){
    srand(time(NULL));
    char string[100];
    int contador=0;
    printf("\n------------------------------------------------------------TEOREMA-DO-MACACO-INFINITO------------------------------------------------------------\n\n");
    printf("O Teorema do Macaco Infinito diz que, teoricamente, se um macaco imortal digitar aleatoriamente em um computador por um periodo infinito de tempo, ele seria\n");
    printf("capaz de reescrever Hamlet com todas os espacos, letras e pontuacoes da obra original de Shakespare (mesmo que levasse bilhoes de anos...).\n");
    printf("Podemos estender essa ideia para qualquer palavra/frase/texto. Isso e o que este programa se propoe a simular.\n");
    printf("\nVamos testar. Diga algo e veremos se Macaco sera capaz de reescrever sua sentenca.\n");
    printf("(Escreva uma sentenca sem espacos, pontuacoes, numeros e nem letras maiusculas.)\n");
    printf("(Aviso: sentencas com mais de 5 letras podem demorar alguns minutos, ate horas.)");
    printf("\nEscreva: ");
    scanf("%s", string);
    printf("\nMacaco acabou de sentar na cadeira. De frente a um computador ligado a uma fonte de energia infinita, e ao lado de uma pilha infinita de bananas, Macaco comeca a digitar.\n");
    char temp = getchar();

    char tent[strlen(string)+1];
    while(1){
        for(int i=0; i<strlen(string); i++){
            tent[i] = (rand() % 26) + 'a'; 
            contador++;
        }
        tent[strlen(string)]='\0';
        printf("%s", tent);

        if(strcmp(tent, string)==0){
            break;
        }
    }
    printf("\n\nMacaco teclou %d letras ate formar a palavra %s.\n", contador, string);

    double seg = contador/3; //assumindo media de 3 caracteres por segundo
    double horas = seg/(3600);
    printf("Isso equivale a %.2lf horas teclando sem parar\n", horas);
    printf("Puxa, Macaco vai tirar um descanso depois dessa.\n");

    return 0;
}