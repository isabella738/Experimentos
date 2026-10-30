/*
    Algoritmo para encontrar o menor caminho para a saída de um labirinto.
    Inspirado em BFS, mas não exatamente.

    Faça seu teste fazendo qualquer desenho na variável 'mapa'. Só lembre de ajustar a altura, largura, e as
    coordenadas de spawn e saída.
*/

#include <iostream>
#include <stack>
#include <array>

#define FUNDO_PRETO "\033[40m"
#define RESET  "\033[0m"
#define MAX 100

struct Coordenada{
    int y, x;
    bool operator>=(int n) const {
        return y >= n && x >= n;
    }
    bool operator==(const Coordenada& outro) const {
        return y == outro.y && x == outro.x;
    }
    Coordenada operator+(const Coordenada& outro) const {
        return {y + outro.y, x + outro.x};
    }
};

Coordenada d[4] = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1}
};

#define ALT 15
#define LARG 24
char mapa[ALT][LARG+1] = {
    //6, 11
    /*
    "###########",
    "E     #   S",//(1, 0), (1, 10)
    "# ### # # #",
    "### # # # #",
    "#          ",
    "###########",
    */

    //11, 10
    /*
    "##########",
    "E        #",//(1, 0)
    "# ###### #",
    "# #      #",
    "# # ######",
    "# #      #",
    "# ###### #",
    "# #      #",
    "# # ######",
    "#        S",//(9, 9)
    "##########"
    */

    //15, 24
    "########################",
    "E                      #",//(1, 0)
    "##### ###### # ####### #",
    "# #   #    # #       # #",
    "# # ###### # ####### # #",
    "# #      # #       # # #",
    "# ###### # ####### # # #",
    "#      # #         # # #",
    "###### # ######## ## # #",
    "#      #        # #    #",
    "# ########### # # #### #",
    "#           # # #    # #",
    "# ######### # # #### # #",
    "#         #   #        S",//(13, 23)
    "########################",
};

bool matriz[ALT][LARG] = {0};

void caminhos(Coordenada p, Coordenada caminho[4], std::array<Coordenada, MAX> vetor , int tam);

int main(){

    //inicializar matriz
    for(int i=0; i<ALT; i++){
        for(int j=0; j<LARG; j++){
            if(mapa[i][j] == '#') matriz[i][j] = 1;
        }
    }

    Coordenada inicio = {1, 0};
    Coordenada saida = {13, 23};

    std::stack<std::array<Coordenada, MAX>> pilha1;
    std::stack<std::array<Coordenada, MAX>> pilha2;

    int p=0;
    std::array<Coordenada, MAX> vetor;
    vetor[0] = inicio;
    pilha1.push(vetor);

    while(p<MAX && !pilha1.empty()){
        int achou=0;

        while(!pilha1.empty()){

            Coordenada caminho[4];
            vetor = pilha1.top();

            caminhos(vetor[p], caminho, vetor, p+1);

            for(int i=0; i<4; i++){
                if(caminho[i] >= 0){
                    vetor[p+1] = caminho[i];
                    pilha2.push(vetor);
                    if(caminho[i] == saida){
                        achou=1; break;
                    }
                }
            }
            pilha1.pop();
            if(achou)break;
        }
        pilha1.swap(pilha2);//pilha com mais um passo
        p++;
        if(achou) break;
    }
    if(pilha1.empty()){
        std::cout << "Nao existe saida para este labirinto." << std::endl;
        return 0;
    }

    //impressao
    vetor = pilha1.top();
    for(int i=0; i<ALT; i++){
        for(int j=0; j<LARG; j++){
            int imp=0;
            for(int k=0; k<p; k++){
                if(vetor[k] == Coordenada{i, j}){
                    std::cout << "* ";
                    imp=1;
                    break;
                }
            }
            if(!imp){ 
                if(matriz[i][j])
                    std::cout << FUNDO_PRETO << "  " << RESET;
                else std::cout << "  ";
            }
        }
        std::cout << '\n';
    }
}

void caminhos(Coordenada p, Coordenada caminho[4], std::array<Coordenada, MAX> vetor , int tam){
    //gera os caminhos possiveis para a coordenada p, ve se não bate com alguma posição já registrada
    //em vetor, e armazena os resultados em caminho

    for(int i=0; i<4; i++){ 

        int continuar=1;
        caminho[i] = p + d[i];

        for(int j=0; j<tam; j++){//se já passou por este caminho
            if(caminho[i] == vetor[j]){
                caminho[i] = {-1, -1}; 
                continuar=0; break;
            }
        }

        if(continuar){//se é parede
            if(matriz[caminho[i].y][caminho[i].x]){
                caminho[i] = {-1, -1};
            }
        }

    }
}
