/*
    A Teoria da Evolução de Darwin aplicada para o aprendizado de máquina.

    Este é um modelo simplificado de aprendizado. Através e somente através da aleatoriedade, este código deve ser capaz de
    chegar a uma certa sequência de caracteres através dos principios evolutivos, isto é, cruzamentos e mutações. 
    Ocorre seguinte forma:

    1. Foram estabelecidos 8 membros para cada geração. A 1a geração é formada por uma sequência totalmente aleatória de
        caracteres.

    2. Os 2 membros desta geração com maiores semelhanças à frase original são escolhidos para gerar a próxima geração.

    3. 8 novas sequências são geradas a partir de cruzamentos (crossing-over) e mutações (inicialmente, à uma taxa de 10%).

    4. 2 dessas 8 novas sequências são selecionadas para gerar a próxima geração.

    A frase original e a taxa de mutação podem ser alteradas diretamente no código, na função main.
    São válidos somente os caracteres: a-z minusculos, espaco, virgula, ponto final e hífen (30 no total). Novos caracteres
    podem ser facilmente adicionados na função "letra_aleatória"

    *Contrapontos: depois de umas 10 gerações o avanço acaba dependendo totalmente das mutações... por isso parece demorar
    tanto. Era de se esperar, pois os cruzamentos são consanguíneos. Devo melhorar isso depois.
*/

#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>

void escrever(std::string s, int n, std::string original);

void letra_aleatoria(std::string& frase, int posicao);

void selecao(std::stack<std::string> *pilha, std::string original);

int main(){
    std::srand(std::time(nullptr));

    int taxa_de_mutacao = 10; //em porcentagem
    std::string original = "quanto mais voltava para tras, mais vida havia. havia igualmente mais bondade na existencia e mais vida propriamente, tambem.";
    //std::string original = "isabella";
    int tamanho = original.length();

    std::stack<std::string> geracao_atual; //stack<tipo_de_dado>
    std::stack<std::string> descendentes;

    int linha=0;
    int concluido=0;

    //gera 8 strings aleatorias
    for(int j=0; j<8; j++){
        std::string novo(tamanho, ' ');
        for(int i=0; i<tamanho; i++){
            letra_aleatoria(novo, i);
        }
        geracao_atual.push(novo);

        if(novo == original){
            concluido=1; break;
        }
    }

    if(!concluido) do{

        selecao(&geracao_atual, original);//pega somente os 2 melhores desta geração

        std::string pai_1 = geracao_atual.top(); geracao_atual.pop(); escrever(pai_1, linha++, original);
        if(pai_1 == original){
            concluido = 1; break;
        }
        //getchar();
        std::string pai_2 = geracao_atual.top(); geracao_atual.pop(); escrever(pai_2, linha++, original);
        if(pai_2 == original){
            concluido = 1; break;
        }
        //getchar();

        //Geração dos descendentes
        for(int i=0; i<8; i++){
            std::string novo;

            //CRUZAMENTO
            int cross = std::rand() % tamanho;
            if(std::rand()%2){//50% da string inicial ser do pai_1, 50% de ser do pai_2
                novo.append(pai_1.substr(0, cross));
                novo += pai_2.substr(cross);
            }
            else{
                novo.append(pai_2.substr(0, cross));
                novo += pai_1.substr(cross);
            }

            //MUTAÇÕES
            int x;
            while((x = std::rand()%100) < taxa_de_mutacao){
                int letra = std::rand() % tamanho;
                letra_aleatoria(novo, letra);
            }

            descendentes.push(novo);
        }
        descendentes.swap(geracao_atual);
        //getchar();
    }while(1);



    return 0;
}

void selecao(std::stack<std::string> *pilha, std::string original){
    std::string melhor1;
    std::string melhor2;

    int maior1 = -1, maior2 = -1;
    do{
        int contagem=0;
        std::string teste = pilha->top();
        for(int i=0; i<teste.length(); i++){
            if(teste[i] == original[i]) contagem++;
        }

        if(contagem > maior1){
            maior1 = contagem;
            melhor1 = teste;
        }
        else if(contagem > maior2){
            maior2 = contagem;
            melhor2 = teste;
        }

        pilha->pop();

    }while(!pilha->empty());

    pilha->push(melhor2); pilha->push(melhor1);
}

void letra_aleatoria(std::string& frase, int posicao){
    int n = std::rand() % 30;
    switch(n){
        case 26: frase[posicao] = ' '; break;
        case 27: frase[posicao] = '.'; break;
        case 28: frase[posicao] = ','; break;
        case 29: frase[posicao] = '-'; break;
        default: frase[posicao] = n + 'a';
    }
}

void escrever(std::string s, int n, std::string original){
    int contagem=0;
    for(int i=0; i<s.length(); i++){
        if(s[i] == original[i]) contagem++;
    }

    std::cout << "Tentativa " << n << ": " << s << " (" << contagem << ")" << std::endl;
}
