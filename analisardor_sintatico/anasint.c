#include <stdio.h>
#include <stdlib.h>
#include "anasint.h"
#include "analex.h"

#define TRUE 1
#define FALSE 0

top_symbols_table = 0;

char erros[][50] = {
                "Unspecified error.",
                "Identifier Expected.",
                "; Expected."
                };

void prog(){
    while(strcmp(tk.type, "EOF")){
        call_analyzer();
        if(tipo()){
            puts("TIPO");
            call_analyzer();
            //printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
            if(!strcmp(tk.type, "ID")){
                puts("IDENTIFICADOR");
                while(strcmp(tk.type, "SN") && strcmp(tk.content, ";")){
                    call_analyzer();
                    if(!strcmp(tk.type, "EOF")){
                        erro(2);
                    }
                    //printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                    if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ",")){
                        puts("SINAL VIRGULA");
                        call_analyzer();
                        if(!strcmp(tk.type, "ID")){
                            //printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                            puts("IDENTIFICADOR");
                        } else {
                            erro(0);
                        }
                    } else if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ";")){
                        //printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                        puts("PONTO E VIRGULA");
                        break;
                    } else {
                        erro(2);
                    }
                }
            } else {
                erro(1);
            }
        } else if(!strcmp(tk.type, "PR") && !strcmp(tk.content, "prototipo")){
                //printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                puts("PROTOTIPO");
                call_analyzer();
                if(tipo() || !strcmp(tk.type, "PR") && !strcmp(tk.content, "semretorno")){
                    //printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                    puts("TIPO OU SEMRETORNO");
                    call_analyzer();
                    if(!strcmp(tk.type, "ID")){
                        //printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                        puts("IDENTIFICADOR");
                        call_analyzer();
                        if(!strcmp(tk.type, "SN") && !strcmp(tk.content, "(")){
                            //printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                            puts("ABRE PARENTESE");
                            call_analyzer();
                            tipos_p_opc();
                            call_analyzer();
                            if(!strcmp(tk.type, "SN") && !strcmp(tk.content,";")){
                                //printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                                puts("PONTO E VIRGULA");
                            } else {
                                //printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                                erro(2);
                            }
                        }
                    } else {
                        erro(0);
                    }
                } else {
                    erro(0);
                }
        } else if(!strcmp(tk.type, "EOF")){
        } else{
            erro(0);
        }
    }
}

int tipo(){
    //printf("tk.type %s tk.content %s\n", tk.type, tk.content);
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
    if(!strcmp(tk.type, "PR") && !strcmp(tk.content, "semparam")){
        //printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
        puts("SEMPARAM");
        call_analyzer();
    } else if(tipo()){
        //printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
        puts("TIPO");
        while(strcmp(tk.type, "SN") && strcmp(tk.content, ")")){

            call_analyzer();
            if(!strcmp(tk.type, "ID")){
                //printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                puts("IDENTIFICADOR");
                call_analyzer();
            }
            else {
                erro(0);
            }
            if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ",")){
                //printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                puts("SINAL VIRGULA");
                call_analyzer();
                if(tipo()){
                    puts("TIPO");
                    call_analyzer();
                    if(!strcmp(tk.type, "ID")){
                        //printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                        puts("IDENTIFICADOR");
                        call_analyzer();
                    }
                    else{
                        erro(0);
                    }
                } else {
                    erro(0);
                }
            } else if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ")")){
                //printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                puts("FECHA PARETESE");
                break;
            } else {

            }
        }
    } else {
        //printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
        erro(0);
    }
}

void tipos_p_opc(){
    if(!strcmp(tk.type, "PR") && !strcmp(tk.content, "semparam")){
        //printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
        puts("SEMPARAM");
        call_analyzer();
    } else if(tipo()){
        //printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
        puts("TIPO");
        while(strcmp(tk.type, "SN") && strcmp(tk.content, ")")){
            call_analyzer();
            if(!strcmp(tk.type, "ID")){
                //printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                puts("IDENTIFICADOR");
                call_analyzer();
            }
            if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ",")){
                //printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                puts("SINAL VIRGULA");
                call_analyzer();
                if(tipo()){
                    puts("TIPO");
                    call_analyzer();
                    if(!strcmp(tk.type, "ID")){
                        //printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                        puts("IDENTIFICADOR");
                        call_analyzer();
                    }
                } else {
                    erro(0);
                }
            } else if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ")")){
                //printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
                puts("FECHA PARETESE");
                break;
            } else {

            }
        }
    } else {
        //printf("tk.type: %s tk.content: %s\n",tk.type, tk.content);
        erro(0);
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

int erro(int e){
    printf("ERRO! %s in line %d", erros[e], line);
    exit(e);
}

void call_analyzer(){
    do{
        lexical_analyzer();
    } while(state != 0);
}
