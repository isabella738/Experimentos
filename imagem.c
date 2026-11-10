/*
    Imprime uma imagem PPM P3 como texto colorido no terminal.
    A imagem precisa obrigatoriamente ser PPM P3. Dica: use ImageMagick.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    int r, g, b;
}Pixel;

int main(){
    int altura_ideal = 40;
    int largura_ideal = 70;

    FILE *imagem = fopen("imagem.ppm", "r");
    if(imagem == NULL){
        printf("Arquivo não aberto.\n");
        return 0;
    }

    char formato[3]; fscanf(imagem, "%s", formato);
    if(strcmp(formato, "P3") != 0){
        printf("A imagem deve estar em formato PPM P3 para executar.\n");
        return 0;
    }

    int altura, largura, valor_maximo;
    fscanf(imagem, "%d %d %d", &largura, &altura, &valor_maximo);

    int razao, razao1;

    do{
        razao = altura/altura_ideal;
        razao1 = largura/largura_ideal;
        if(razao1 > razao) razao = razao1;

        for(int i=0; i<altura/razao; i++)printf("-\n");
        for(int i=0; i<largura/razao; i++)printf("- ");
        printf("\nA imagem foi reduzida em %d vezes para melhor se adequar ao terminal.\n", razao);
        printf("As linhas anteriores servem como guia das dimensões da imagem final. Atualmente: %dx%d.\n", largura/razao, altura/razao);
        printf("As dimensões máximas atuais são %dx%d. Insira outra configuração, ou 0 0 para imprimir.\n", largura_ideal, altura_ideal);

        int a, b;
        if(scanf("%d %d", &a, &b)){
            if(a == 0 && b == 0) break;
            largura_ideal = a;
            altura_ideal = b;
        }
        system("clear");
    }while(1);
    system("clear");

    Pixel pixel[altura][largura];

    for(int i=0; i<altura; i++){
        int r=0, g=0, b=0, contador=0;

        for(int j=0; j<largura; j++){

            int sr, sg, sb;
            fscanf(imagem, "%d %d %d", &sr, &sg, &sb);
            r += sr;
            g += sg;
            b += sb;
            contador++;

            if(contador >= razao || j+1 == largura){
                r/=contador;
                g/=contador;
                b/=contador;
                pixel[i][j/razao] = (Pixel){r, g, b};
                
                contador = 0; r=0; g=0; b=0;
            }
            
        }
    }

    for(int j=0; j<largura/razao; j++){
        int r=0, g=0, b=0, contador=0;

        for(int i=0; i<altura; i++){

            r += pixel[i][j].r;
            g += pixel[i][j].g;
            b += pixel[i][j].b;
            contador++;

            if(contador >= razao || i+1 == largura){
                r/=contador;
                g/=contador;
                b/=contador;
                pixel[i/razao][j] = (Pixel){r, g, b};
                
                contador = 0; r=0; g=0; b=0;
            }
            
        }
    }

    for(int y=0; y<altura/razao; y++){
        for(int x=0; x<largura/razao; x++){
            printf("\033[48;2;%d;%d;%dm  \033[0m", pixel[y][x].r, pixel[y][x].g, pixel[y][x].b);
        }
        printf("\n");
    }

    fclose(imagem);
}