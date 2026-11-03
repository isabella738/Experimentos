// trata um arquivo de texto. Tira pontuações e números, pode tirar letras maiusculas e acentos se
// necessario

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char substituir_acento(unsigned char segundo_byte){

    switch(segundo_byte){

        // A maiúsculo
        case 0x84: case 0x85: case 0x81:
        case 0x82: case 0x80: case 0x83:
            return 'A';

        // a minúsculo
        case 0xA4: case 0xA1: case 0xA2:
        case 0xA0: case 0xA3:
            return 'a';

        // E maiúsculo
        case 0x89: case 0x8A: case 0x8B: case 0x88:
            return 'E';

        // e minúsculo
        case 0xA9: case 0xAA: case 0xAB: case 0xA8:
            return 'e';

        // I maiúsculo
        case 0x8D: case 0x8E: case 0x8F: case 0x8C:
            return 'I';

        // i minúsculo
        case 0xAD: case 0xAE: case 0xAF: case 0xAC:
            return 'i';

        // O maiúsculo
        case 0x96: case 0x93: case 0x94:
        case 0x92: case 0x95:
            return 'O';

        // o minúsculo
        case 0xB6: case 0xB3: case 0xB4:
        case 0xB2: case 0xB5:
            return 'o';

        // U maiúsculo
        case 0x9C: case 0x9A: case 0x9B:
            return 'U';

        // u minúsculo
        case 0xBC: case 0xBA: case 0xBB: case 0xB9:
            return 'u';

        // C e c
        case 0x87: return 'C';
        case 0xA7: return 'c';

        default:
            return '\0';
    }
}

int main(){

    int desabilitar_maiusculas = 1;
    int desabilitar_acentos = 1;

    FILE *origem = fopen("temp.txt", "r");
    if(origem == NULL){
        printf("Erro ao abrir origem\n");
        return 1;
    }
    FILE *destino = fopen("banco_de_texto.txt", "w");
    if(destino == NULL){
        printf("Erro ao abrir origem\n");
        return 1;
    }

    char linha[500];
    while(fgets(linha, 500, origem) != NULL){
        char copia[500];
        int c = 0;
        if(linha[0] == '\n') continue;

        int tamanho = strlen(linha);

        for(int i = 0; i < tamanho; i++){
            unsigned char atual = (unsigned char)linha[i];

            // Caracteres ASCII
            if(atual < 128){

                if(atual >= 'A' && atual <= 'Z'){
                    if(desabilitar_maiusculas)
                        copia[c++] = atual + ('a' - 'A');
                    else
                        copia[c++] = atual;
                }
                else if((atual >= 'a' && atual <= 'z') ||
                        atual == '\n' || atual == ' '){

                    copia[c++] = atual;
                }
                else if(atual == '-' || atual == '_' || atual == '(' || atual == ')'){
                    copia[c++] = ' ';
                }
            }

            // Caracteres UTF-8 de dois bytes
            else if((atual & 0xE0) == 0xC0 && i + 1 < tamanho){

                unsigned char segundo = (unsigned char)linha[i+1];

                if(desabilitar_acentos && atual == 0xC3){

                    char substituto = substituir_acento(segundo);

                    if(substituto != '\0'){

                        if(desabilitar_maiusculas &&
                        substituto >= 'A' && substituto <= 'Z'){

                            substituto += ('a' - 'A');
                        }

                        copia[c++] = substituto;
                    }
                }
                else if(!desabilitar_acentos){

                    copia[c++] = linha[i];
                    copia[c++] = linha[i+1];
                }

                i++; // Avança o segundo byte
            }
        }

        copia[c] = '\0';
        fprintf(destino, "%s", copia);
    }
    printf("Concluido!\n");
    fclose(origem);
    fclose(destino);

    return 0;
}