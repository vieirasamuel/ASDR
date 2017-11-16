#include <stdio.h>
#include <stdlib.h>
#include "anasint.h"
#include "analex.h"
#define unspecifiedError 0
#define idExpected 1
#define pontoVirgulaExpected 2

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
            if(!strcmp(tk.type, "ID")){
                puts("IDENTIFICADOR");
                while(strcmp(tk.type, "SN") && strcmp(tk.content, ";")){
                    call_analyzer();
                    if(!strcmp(tk.type, "EOF")){
                        erro(pontoVirgulaExpected);
                    }
                    if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ",")){
                        puts("SINAL VIRGULA");
                        call_analyzer();
                        if(!strcmp(tk.type, "ID")){
                            puts("IDENTIFICADOR");
                        } else {
                            erro(unspecifiedError);
                        }
                    } else if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ";")){
                        puts("PONTO E VIRGULA");
                        break;
                    } else {
                        erro(pontoVirgulaExpected);
                    }
                }
            } else {
                erro(1);
            }
        } else if(!strcmp(tk.type, "PR") && !strcmp(tk.content, "prototipo")){
                puts("PROTOTIPO");
                call_analyzer();
                if(tipo() || !strcmp(tk.type, "PR") && !strcmp(tk.content, "semretorno")){
                    puts("TIPO OU SEMRETORNO");
                    call_analyzer();
                    if(!strcmp(tk.type, "ID")){
                        puts("IDENTIFICADOR");
                        call_analyzer();
                        if(!strcmp(tk.type, "SN") && !strcmp(tk.content, "(")){
                            puts("ABRE PARENTESE");
                            call_analyzer();
                            tipos_p_opc();
                            if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ")")){
                                puts("FECHA PARENTESE");
                                call_analyzer();
                                if(!strcmp(tk.type, "SN") && !strcmp(tk.content,";")){
                                    puts("PONTO E VIRGULA");
                                    call_analyzer();
                                } else {
                                    erro(pontoVirgulaExpected);
                                }
                            } else {
                                erro(0);
                            }
                        } else {
                            erro(0);
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
        puts("SEMPARAM");
        call_analyzer();
    } else if(tipo()){
        puts("TIPO");
        call_analyzer();
        if(!strcmp(tk.type, "ID")){
            puts("IDENTIFICADOR");
            call_analyzer();
        } else {
            erro(0);
        }
        while(strcmp(tk.content, ")")){
            if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ",")){
                puts("SINAL VIRGULA");
                call_analyzer();
                if(tipo()){
                    puts("TIPO");
                    call_analyzer();
                    if(!strcmp(tk.type, "ID")){
                        puts("IDENTIFICADOR");
                        call_analyzer();
                    } else {
                        erro(0);
                    }
                } else {
                    erro(0);
                }
            }
        }
    } else {
        erro(unspecifiedError);
    }
}

void tipos_p_opc(){
    if(!strcmp(tk.type, "PR") && !strcmp(tk.content, "semparam")){
        puts("SEMPARAM");
        call_analyzer();
    } else if(tipo()){
        puts("TIPO");
        call_analyzer();
        if(!strcmp(tk.type, "ID")){
            puts("IDENTIFICADOR");
            call_analyzer();
        }
        while(strcmp(tk.content, ")")){
            if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ",")){
                puts("SINAL VIRGULA");
                call_analyzer();
                if(tipo()){
                    puts("TIPO");
                    call_analyzer();
                    if(!strcmp(tk.type, "ID")){
                        puts("IDENTIFICADOR");
                        call_analyzer();
                    }
                } else {
                    erro(0);
                }
            }
        }
    } else {
        erro(unspecifiedError);
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
    call_analyzer();
    if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ",")){
    }
}

int erro(int e){
    printf("ERRO! %s", erros[e]);
    exit(e);
}

void call_analyzer(){
    do{
        lexical_analyzer();
    } while(state != 0);
}
