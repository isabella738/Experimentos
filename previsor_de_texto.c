/*
    Digite uma palavra e o algoritmo tentará completar a frase.
    Depende do arquivo: banco_de_texto.txt em /dados

    Descrição:
    O objetivo é colocar as palavras de um banco de frases tratado (sem acentos, nem letras maiusculas 
    nem pontuações) em uma estruturas de grafos, uma lista de adjacências. Cada palavra é um vertice
    que se liga ao vertice das palavras que aparecem depois dela, somente.

    Aqui, um vertice possui os seguintes elementos:
    (principais)
        - char palavra[]: a palavra de fato
        - Vertices **adj: lista dos vertices adjacentes (seus endereços)
        - int tam: qantidade de vertices adjacentes
    (temporarios)
        - char proxima[]: a palavra que vem imediatamente depois (util no inicio, na leitura dos dados
        brutos)
        - char **strings: o equivalente de adj, mas armazena diretamente o conteudo da palavra (util
        enquanto o vetor vertices ainda está sendo organizado)

    O algoritmo: 
    1. Leitura dos dados 
        Ler todas as palavras de um banco e armazenar cada uma como um vertice diferente. Este também
        armazena a palavra imediatamente depois, se não estiver no final da frase.

    2. Organizar alfabeticamente
        São organizadas por algoritmo de quick sort. Assim, as palavras iguais ficam juntas e facilitam
        o processo da etapa 3 e a busca na etapa 5
    
    3. Remover duplicatas e juntar todas as palavras 'proxima'
        Os vertices iguais são mesclados, e as palavras que vem depois são guardadas no campo 'strings'.
        Assim, um vertice possui o conteudo de todos os seus vertices adjacentes
    
    4. Remover vertices isolados e palavras vazias do campo 'strings'
        Também é possível remover duplicatas do campo strings, mas acho interessante manter pela questão 
        de probabilidade na escolha
    
    5. Anexar aos vertices os endereços dos seus vertices adjacentes
        Para cada palavra em strings, procura-se onde ela está no vetor de vertices e, se existir, 
        coloca o endereço dela no vetor adj. Ou seja, no fim, 'strings' deve estar vazio
    
    6. Colocar na prática
        Insira uma palavra. O codigo tentará encontrá-la em no vetor de vertices e, se encontrar, vai pegar 
        aleatoriamente um de seus vertices adjacentes, imprimir a palavra, e repetir o processo por um 
        numero de vezes determinado no codigo (definido como 10 por padrão)
    
    (Obs: experimente escrever um verbo, as frases fazem um pouco mais de sentido)
    
    O projeto pode ser atualizado.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Vertices{
    char palavra[100];
    char proxima[100];
    char **strings;
    struct Vertices **adj;
    int tam;
}Vertices;

void quick_sort(Vertices vetor[], int inicio, int fim);
int adicionar_string(Vertices *d, char *palavra);
Vertices* busca_binaria(Vertices vetor[], char palavra[], int inicio, int fim);
void apagar_string(char **string, int x, int *max);
void apagar_vertice(Vertices *vetor, int x, int *max);

int main(){
    srand(time(NULL));
    FILE *arquivo = fopen("dados/banco_de_texto.txt", "r");
    if(arquivo == NULL){
        printf("Erro ao abrir arquivo\n");
        return 1;
    }

    Vertices *vertice = calloc(1, sizeof(Vertices)); //iniciar com 0
    int n=0;

    char palavra[100];
    int ler_anterior = 0;//para não ler a proxima de palavras no final do texto

    //ler as palavras e as próximas do banco
    while(fscanf(arquivo, "%s", palavra) != EOF){
        if(palavra[0] == '\n') continue;

        if(ler_anterior)
            strcpy(vertice[n-1].proxima, palavra);
        ler_anterior = 1;

        strcpy(vertice[n].palavra, palavra);

        char c;
        if((c = fgetc(arquivo)) == '\n') ler_anterior = 0;

        n++;
        Vertices *novo = realloc(vertice, sizeof(Vertices)*(n+1));
        if(novo == NULL){
            printf("Ocorreu erro em realloc.\nn = %d\n", n);
            return 1;
        }
        vertice = novo;
    }
    fclose(arquivo);

    //reorganizar alfabeticamente
    quick_sort(vertice, 0, n-1);

    //inicializar strings; acrescentar o campo 'proxima' ao campo de strings
    for(int i=0; i<n; i++){
        vertice[i].strings = NULL;
        vertice[i].tam = 0;

        if(vertice[i].proxima[0] != '\0' || vertice[i].proxima[0] != '\n'){
            if(!adicionar_string(&vertice[i], vertice[i].proxima)){
                printf("Erro de alocacao em adicionar strings da inicializacao.\n");
                return 1;
            }
        }
    }

    //juntar as strings dos vertices que são iguais
    for(int i=0; i<n; i++){

        if(strcmp(vertice[i].palavra, vertice[i+1].palavra) == 0){
            if(!adicionar_string(&vertice[i], vertice[i+1].proxima)){
                printf("Erro de alocacao em adicionar em juntar vertices iguais.\n");
                return 1;
            }
            
            //remover duplicata
            free(vertice[i+1].strings);
            apagar_vertice(vertice, i+1, &n);
            i--;
        }
    }

    //remover strings iguais e vazias, e palavras sem adjacentes
    for(int i=0; i<n; i++){

        for(int j=0; j<vertice[i].tam; j++){
            //apagar strings vazias
            if(vertice[i].strings[j][0] == '\n' || vertice[i].strings[j][0] == '\0'){
                free(vertice[i].strings[j]);
                apagar_string(vertice[i].strings, j, &vertice[i].tam);
                j--;
                continue;
            }

            /*
            //apagar strings duplicadas
                //pode ser removido para manter os pesos de probabilidade

            for(int k=j+1; k<vertice[i].tam; k++){
                if(strcmp(vertice[i].strings[j], vertice[i].strings[k]) == 0){
                    apagar_string(vertice[i].strings, k, vertice[i].tam);

                    k--;
                }
            }
            */
        }
        
        //remover palavras isoladas
        if(vertice[i].tam == 0){
            apagar_vertice(vertice, i, &n);
            i--;
            continue;
        }
    }

    //buscar o endereço das strings no vetor de vertices (busca binaria)
    //e coloca-los no campo adj
    for(int i=0; i<n; i++){
        int contador = 0;
        vertice[i].adj = malloc(sizeof(Vertices*)*vertice[i].tam);
        if(vertice[i].adj == NULL){
            printf("Erro de alcacao em transformar strings.\n");
            return 1;
        }

        //buscas de fato
        for(int j=0; j<vertice[i].tam; j++){
            Vertices *p = busca_binaria(vertice, vertice[i].strings[j], 0, n-1);
            free(vertice[i].strings[j]);

            //se retornou null, a palavra não existe, ou é vazia
            if(p == NULL){
                for(int k=j; k<vertice[i].tam-1; k++) vertice[i].strings[k] = vertice[i].strings[k+1];
                vertice[i].tam--;
                j--;
                continue;
            }
            vertice[i].adj[contador++] = p;
        }
        //liberar alocacoes para o campo strings
        free(vertice[i].strings);
        vertice[i].strings = NULL;

        if(contador == 0){
            //se nao achou nenhuma palavra, deve desalocar a memoria de adj
            free(vertice[i].adj);
            vertice[i].adj = NULL;
        }
        else if(contador != vertice[i].tam){
            //alocar menos espaço se existem menos ponteiros que strings
            Vertices **novo = realloc(vertice[i].adj, sizeof(Vertices *)*contador);
            if(novo == NULL){
                printf("Erro de realoc em adj\n");
                return 1;
            }
            vertice[i].adj = novo;
        }
        vertice[i].tam = contador;
    }

    /*
    //ver se funcionou
    for(int i=0; i<n; i++){
        printf("%s (%d)\n", vertice[i].palavra, vertice[i].tam);
        
        if(vertice[i].tam > 0)
            for(int j=0; j<vertice[i].tam; j++){
                printf("%d. %s\n", j, vertice[i].adj[j]->palavra);
            }
        
        printf("\n");
    }
    printf("\nn = %d\n", n);
    //obs: funcinou!!
    */

    int quantidade = 10; // quantidade de palavras geradas na frase
    printf("Escreva uma palavra. O algoritmo completará com uma frase.\n> ");
    char p[100]; scanf("%s", p);
    Vertices *v = busca_binaria(vertice, p, 0, n-1);

    if(v == NULL){
        printf("Desculpe, esta palavra não existe no nosso banco.\n");
        return 0;
    }

    for(int i=0; i<quantidade; i++){
        printf("%s ", v->palavra);
        int indice = rand()%v->tam;
        v = v->adj[indice];
    }

    free(vertice);
    return 0;
}

//funções auxiliares

void quick_sort(Vertices vetor[], int inicio, int fim){
    char pivo[100];
    strcpy(pivo, vetor[inicio].palavra);
    int p = inicio, i = fim;
    
    if(fim <= inicio) return;

    int sentido = -1;
    int continuar = 1;
    do{
        if(sentido == -1){
            if(strcmp(vetor[p].palavra, vetor[i].palavra) > 0){
                Vertices a = vetor[p];
                vetor[p] = vetor[i];
                vetor[i] = a;

                int aux = p;
                p = i;
                i = aux;

                sentido = 1;
            }
        }
        else{
            if(strcmp(vetor[i].palavra, vetor[p].palavra) > 0){
                Vertices a = vetor[p];
                vetor[p] = vetor[i];
                vetor[i] = a;

                int aux = p;
                p = i;
                i = aux;

                sentido = -1;
            }
        }
        i += sentido;
    }while(i != p);

    quick_sort(vetor, inicio, p-1);
    quick_sort(vetor, p+1, fim);

}

int adicionar_string(Vertices *d, char *palavra){
    //adiciona palava ao campo string do vertice
    char **novo = realloc(d->strings, sizeof(char*)*(d->tam+1));
    if(novo == NULL)return 0;

    d->strings = novo;

    d->strings[d->tam] = malloc(strlen(palavra) + 1);

    if(d->strings[d->tam] == NULL)return 0;

    strcpy(d->strings[d->tam], palavra);

    d->tam++;
    return 1;
}

Vertices* busca_binaria(Vertices vetor[], char palavra[], int inicio, int fim){
    if(inicio > fim){
        return NULL;
    }

    int m = (inicio+fim)/2;
    int cmp = strcmp(palavra, vetor[m].palavra);

    if(cmp == 0){ //achou
        return &vetor[m];
    }
    
    if(cmp < 0) fim = m-1;
    else inicio = m+1;

    return busca_binaria(vetor, palavra, inicio, fim);
}

void apagar_string(char **string, int x, int *max){
    for(int i=x; i<(*max)-1; i++)
        string[i] = string[i+1];
    (*max)--;
}

void apagar_vertice(Vertices *vetor, int x, int *max){
    for(int i=x; i<(*max)-1; i++)
        vetor[i] = vetor[i+1];
    (*max)--;
}