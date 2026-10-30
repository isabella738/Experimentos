#include <stdio.h>
#include <string.h>

//DECODIFICADOR DE MORSE
//
//Observações:
//1. Separar letras com espaços
//2. Separar palavras com barra (/), sem espaços entre os caracteres
//3. São aceitos apenas numeros e letras minusculas

char decodificacao(char codigo[]){
    char letra;
    int n=0;

    if(codigo[n]=='.'){
        n++;
        if(codigo[n]=='\0')letra='e';
        else if(codigo[n]=='.'){
            n++;
            if(codigo[n]=='\0')letra='i';
            else if(codigo[n]=='.'){
                n++;
                if(codigo[n]=='\0')letra='s';
                else if(codigo[n]=='.')letra='h';
                else letra='v';
            }
            else{//traço 3
                n++;
                if(codigo[n]=='\0')letra='u';
                else if(codigo[n]=='.')letra='f';
                //else letra='?';
            }
        }
        else{//traço 2
            n++;
            if(codigo[n]=='\0')letra='a';
            else if(codigo[n]=='.'){
                n++;
                if(codigo[n]=='\0')letra='r';
                else if(codigo[n]=='.')letra='l';
                //else letra='?';
            }
            else{//traço 3
                n++;
                if(codigo[n]=='\0')letra='w';
                else if(codigo[n]=='.')letra='p';
                else letra='j';
            }
        }
    }
    else if(codigo[n]=='-'){//traço 1
        n++;
        if(codigo[n]=='\0')letra='t';
        else if(codigo[n]=='.'){
            n++;
            if(codigo[n]=='\0')letra='n';
            else if(codigo[n]=='.'){
                n++;
                if(codigo[n]=='\0')letra='d';
                else if(codigo[n]=='.')letra='b';
                else letra='x';
            }
            else{
                n++;
                if(codigo[n]=='\0')letra='k';
                else if(codigo[n]=='.')letra='c';
                else letra='y';
            }
        }
        else{//traço 2
            n++;
            if(codigo[n]=='\0')letra='m';
            else if(codigo[n]=='.'){
                n++;
                if(codigo[n]=='\0')letra='g';
                else if(codigo[n]=='.')letra='z';
                else letra='q';
            }
            else{
                n++;
                if(codigo[n]=='\0')letra='o';
                //else if(codigo[n]=='.')letra='?';
                //else letra='?';
            }
        }
    }

    /*
    if(strcmp(codigo, ".-")==0)letra='a';
    else if(strcmp(codigo, "-...")==0)letra='b';
    else if(strcmp(codigo, "-.-.")==0)letra='c';
    else if(strcmp(codigo, "-..")==0)letra='d';
    else if(strcmp(codigo, ".")==0)letra='e';
    else if(strcmp(codigo, "..-.")==0)letra='f';
    else if(strcmp(codigo, "--.")==0)letra='g';
    else if(strcmp(codigo, "....")==0)letra='h';
    else if(strcmp(codigo, "..")==0)letra='i';
    else if(strcmp(codigo, ".---")==0)letra='j';
    else if(strcmp(codigo, "-.-")==0)letra='k';
    else if(strcmp(codigo, ".-..")==0)letra='l';
    else if(strcmp(codigo, "--")==0)letra='m';
    else if(strcmp(codigo, "-.")==0)letra='n';
    else if(strcmp(codigo, "---")==0)letra='o';
    else if(strcmp(codigo, ".--.")==0)letra='p';
    else if(strcmp(codigo, "--.-")==0)letra='q';
    else if(strcmp(codigo, ".-.")==0)letra='r';
    else if(strcmp(codigo, "...")==0)letra='s';
    else if(strcmp(codigo, "-")==0)letra='t';
    else if(strcmp(codigo, "..-")==0)letra='u';
    else if(strcmp(codigo, "...-")==0)letra='v';
    else if(strcmp(codigo, ".--")==0)letra='w';
    else if(strcmp(codigo, "-..-")==0)letra='x';
    else if(strcmp(codigo, "-.--")==0)letra='y';
    else if(strcmp(codigo, "--..")==0)letra='z';*/

    else if(strcmp(codigo, "-----")==0)letra='0';
    else if(strcmp(codigo, ".----")==0)letra='1';
    else if(strcmp(codigo, "..---")==0)letra='2';
    else if(strcmp(codigo, "...--")==0)letra='3';
    else if(strcmp(codigo, "....-")==0)letra='4';
    else if(strcmp(codigo, ".....")==0)letra='5';
    else if(strcmp(codigo, "-....")==0)letra='6';
    else if(strcmp(codigo, "--...")==0)letra='7';
    else if(strcmp(codigo, "---..")==0)letra='8';
    else if(strcmp(codigo, "----.")==0)letra='9';
    else letra='?';

    return letra;
};

char* codificacao(char letra){
    char* c;
    if(letra==' ')c="/"; 
    else if(letra=='a')c=".- "; 
    else if(letra=='b')c="-... "; 
    else if(letra=='c')c="-.-. "; 
    else if(letra=='d')c="-.. "; 
    else if(letra=='e')c=". "; 
    else if(letra=='f')c="..-. "; 
    else if(letra=='g')c="--. "; 
    else if(letra=='h')c=".... "; 
    else if(letra=='i')c=".. "; 
    else if(letra=='j')c=".--- "; 
    else if(letra=='k')c="-.- "; 
    else if(letra=='l')c=".-.. "; 
    else if(letra=='m')c="-- "; 
    else if(letra=='n')c="-. "; 
    else if(letra=='o')c="--- "; 
    else if(letra=='p')c=".--. "; 
    else if(letra=='q')c="--.- "; 
    else if(letra=='r')c=".-. "; 
    else if(letra=='s')c="... "; 
    else if(letra=='t')c="- "; 
    else if(letra=='u')c="..- "; 
    else if(letra=='v')c="...- "; 
    else if(letra=='w')c=".-- "; 
    else if(letra=='x')c="-..- "; 
    else if(letra=='y')c="-.-- "; 
    else if(letra=='z')c="--.. "; 
    else if(letra=='0')c="----- "; 
    else if(letra=='1')c=".---- "; 
    else if(letra=='2')c="..--- "; 
    else if(letra=='3')c="...-- "; 
    else if(letra=='4')c="....- "; 
    else if(letra=='5')c="..... "; 
    else if(letra=='6')c="-.... "; 
    else if(letra=='7')c="--... "; 
    else if(letra=='8')c="---.. "; 
    else if(letra=='9')c="----. ";
    else c="?";

    return c;
};

int main(){
    int n;
    printf("1. Codificar\n2. Decodificar\n");
    scanf("%d ", &n);

    char frase[1000]; int f=0;
    fgets(frase, sizeof(frase), stdin);

    if(n==1){//codificar
        char codf[1000]; int cd=0;
        char *cadeia;
        while(frase[f] != '\0' && frase[f]!='\n'){
            cadeia = codificacao(frase[f]);

            for(int i=0; cadeia[i]!='\0'; i++){
                codf[cd] = cadeia[i];
                cd++;
            }

            f++;
        }

        codf[cd]='\0';
        printf("%s\n", codf);
    }
    else if(n==2){//decodificar
        char dec[1000]; int d=0;

        while(frase[f] != '\0'){
            char cod[10]; int c=0;
            while(frase[f]=='.' || frase[f]=='-'){
                cod[c] = frase[f];
                f++; c++;
            }
            
            cod[c]='\0';
            dec[d]= decodificacao(cod);
            d++;

            if(frase[f]=='/'){
                dec[d]=' ';
                d++;
            }
            f++;
        }
        dec[d]='\0';
        printf("%s\n", dec);
    }

    return 0;
}