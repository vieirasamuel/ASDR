#include <stdio.h>
#include <stdlib.h>
#include "anasint.h"
#include "analex.h"

#define TRUE 1
#define FALSE 0

top_symbols_table = 0;

void prog(){
    while(strcmp(tk.type, "EOF")){
        call_analyzer();
        if(tipo()){
            puts("TIPO");
            call_analyzer();
            printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
            if(!strcmp(tk.type, "ID")){
                puts("IDENTIFICADOR");
                while(strcmp(tk.type, "SN") && strcmp(tk.content, ";")){
                    call_analyzer();
                    if(!strcmp(tk.type, "EOF")){
                        erro();
                    }
                    printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                    if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ",")){
                        puts("SINAL VIRGULA");
                        call_analyzer();
                        if(!strcmp(tk.type, "ID")){
                            printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                            puts("IDENTIFICADOR");
                        } else {
                            erro();
                        }
                    } else if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ";")){
                        printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                        puts("PONTO E VIRGULA");
                        break;
                    }
                }
            } else {
                erro();
            }
        } else if(!strcmp(tk.type, "PR") && !strcmp(tk.content, "prototipo")){
                printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                puts("PROTOTIPO");
                call_analyzer();
                if(tipo() || !strcmp(tk.type, "PR") && !strcmp(tk.content, "semretorno")){
                    printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                    puts("TIPO OU SEMRETORNO");
                    call_analyzer();
                    if(!strcmp(tk.type, "ID")){
                        printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                        puts("IDENTIFICADOR");
                        call_analyzer();
                        if(!strcmp(tk.type, "SN") && !strcmp(tk.content, "(")){
                            printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                            puts("ABRE PARENTESE");
                            call_analyzer();
                            tipos_p_opc();
                            call_analyzer();
                            if(!strcmp(tk.type, "SN") && !strcmp(tk.content,";")){
                                printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                                puts("PONTO E VIRGULA");
                            } else {
                                printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                                erro();
                            }
                        }
                    } else {
                        erro();
                    }
                } else {
                    erro();
                }
        } else if(!strcmp(tk.type, "EOF")){
        } else{
            erro();
        }
    }
}

int tipo(){
    printf("tk.type %s tk.content %s\n", tk.type, tk.content);
    if((!strcmp(tk.type, "PR") && !strcmp(tk.content, "caracter"))
       || (!strcmp(tk.type, "PR") && !strcmp(tk.content, "inteiro"))
       || (!strcmp(tk.type, "PR") && !strcmp(tk.content, "real"))
       || (!strcmp(tk.type, "PR") && !strcmp(tk.content, "booleano"))){
        return(TRUE);
       } else {
            return(FALSE);
       }
}

void tipos_param(){

}

void tipos_p_opc(){
    if(!strcmp(tk.type, "PR") && !strcmp(tk.content, "semparam")){
        printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
        puts("SEMPARAM");
    } else if(tipo()){
        printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
        puts("TIPO");
        while(strcmp(tk.type, "SN") && strcmp(tk.content, ")")){

            call_analyzer();
            if(!strcmp(tk.type, "ID")){
                printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                puts("IDENTIFICADOR");
            }
            if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ",")){
                printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                puts("SINAL VIRGULA");
                call_analyzer();
                if(tipo()){
                    puts("TIPO");
                    call_analyzer();
                    if(!strcmp(tk.type, "ID")){
                        printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                        puts("IDENTIFICADOR");
                        call_analyzer();
                    }
                } else {
                    erro();
                }
            } else if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ")")){
                printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                puts("FECHA PARETESE");
                break;
            } else {

            }
        }
    } else {
        printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
        erro();
    }
}

void cmd(){

}

void atrib(){

}

void expr(){

}

void expr_simp(){

}

void termo(){

}

void fator(){

}

void op_rel(){

}

int erro(){
    puts("erro!");
    exit(1);
}

void call_analyzer(){
    do{
        lexical_analyzer();
    } while(state != 0);
}
