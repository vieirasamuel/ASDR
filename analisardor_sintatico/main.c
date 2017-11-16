#include <stdio.h>
#include <stdlib.h>
#include "analex.h"
#include "anasint.h"

int main(int argc, char *argv[]){
    puts("Digite o nome do arquivo:");
    scanf("%s", &file_name);
    open_file(&file_name);
    prog();
    /*while(!feof(imput)){
        do{
            lexical_analyzer();
        } while(state != 0);
        printf("Token type: %s, content: %s\n", tk.type, tk.content);
    }*/
    return 0;
}
