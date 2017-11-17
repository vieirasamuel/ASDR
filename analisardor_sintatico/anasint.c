#include <stdio.h>
#include <stdlib.h>
#include "anasint.h"
#include "analex.h"
#define unspecifiedError 0
#define idExpected 1
#define pontoVirgulaExpected 2
#define opRel 3
#define fechaParenteseExpected 4
#define TYPE_EXPECTED 5

#define TRUE 1
#define FALSE 0

top_symbols_table = 0;

char erros[][50] = {
                "Unspecified error.",
                "Identifier Expected.",
                "; Expected.",
                "OpRel Expected",
                ") Expected",
                "Type Expected"
                };

void prog(){
    call_analyzer();
    while(strcmp(tk.type, "EOF")){
        //call_analyzer();
        if(tipo() || !strcmp(tk.type, "PR") && !strcmp(tk.content, "semretorno")){
            int sem_retorno = FALSE;
            if(!strcmp(tk.content, "semretorno")){
                sem_retorno = TRUE;
            }
            puts("TIPO OU SEM RETORNO");
            call_analyzer();
            if(!strcmp(tk.type, "ID")){
                puts("IDENTIFICADOR");
                call_analyzer();
                //printf("tk.type [%s]\ttk.content [%s]\tstr tk.type [%d]\tstr tk.content [%d]\n", tk.type, tk.content, !strcmp(tk.type, "SN"), !strcmp(tk.content, "("));
                if(!strcmp(tk.type, "SN") && !strcmp(tk.content, "(")){
                    puts("ABRE PARENTESE");
                    call_analyzer();
                    tipos_param();
                    if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ")")){
                        puts("FECHA PARENTESE");
                        call_analyzer();
                        if(!strcmp(tk.type, "SN") && !strcmp(tk.content, "{")){
                            puts("ABRE CHAVE");
                            call_analyzer();
                            if(tipo()){
                                puts("TIPO");
                                call_analyzer();
                                if(!strcmp(tk.type, "ID")){
                                    puts("IDENTIFICADOR");
                                    call_analyzer();
                                    while(/*strcmp(tk.type, "SN") && strcmp(tk.content, ";")*/tk.content != ";"){
                                        if(!strcmp(tk.type, "EOF")){
                                            erro(pontoVirgulaExpected);
                                        }
                                        if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ",")){
                                            puts("SINAL VIRGULA");
                                            call_analyzer();
                                            if(!strcmp(tk.type, "ID")){
                                                puts("IDENTIFICADOR");
                                                call_analyzer();
                                            } else {
                                                erro(unspecifiedError);
                                            }
                                        } else if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ";")){
                                            puts("PONTO E VIRGULA");
                                            call_analyzer();
                                            break;
                                        } else {
                                            erro(pontoVirgulaExpected);
                                        }
                                    }
                                } else {
                                    erro(idExpected);
                                }
                            } else {
                                cmd();
                            }
                            if(!strcmp(tk.type, "SN") && !strcmp(tk.content, "}")){
                                puts("FECHA CHAVE");
                                call_analyzer();
                            } else {
                                erro(0);
                            }
                        }
                    } else {
                        erro(fechaParenteseExpected);
                    }
                } else {
                    if(!sem_retorno){
                        while(/*strcmp(tk.type, "SN") && strcmp(tk.content, ";")*/tk.content != ";"){
                            if(!strcmp(tk.type, "EOF")){
                                erro(pontoVirgulaExpected);
                            }
                            if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ",")){
                                puts("SINAL VIRGULA");
                                call_analyzer();
                                if(!strcmp(tk.type, "ID")){
                                    puts("IDENTIFICADOR");
                                    call_analyzer();
                                } else {
                                    erro(unspecifiedError);
                                }
                            } else if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ";")){
                                puts("PONTO E VIRGULA");
                                call_analyzer();
                                break;
                            } else {
                                erro(pontoVirgulaExpected);
                            }
                        }
                    } else {
                        erro(0);
                    }
                }
            } else {
                erro(idExpected);
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
                                while(strcmp(tk.content, ";")){
                                    if(!strcmp(tk.type, "EOF")){
                                        erro(pontoVirgulaExpected);
                                    }
                                    if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ",")){
                                        puts("VIRGULA");
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
                                                } else {
                                                    erro(fechaParenteseExpected);
                                                }
                                            } else {
                                                erro(0);
                                            }
                                        } else {
                                            erro(idExpected);
                                        }
                                    } else if(!strcmp(tk.type, "SN") && !strcmp(tk.content,";")){
                                        puts("PONTO E VIRGULA");
                                    } else {
                                        erro(pontoVirgulaExpected);
                                    }
                                }
                            } else {
                                erro(fechaParenteseExpected);
                            }
                        } else {
                            erro(0);
                        }
                    } else {
                        erro(idExpected);
                    }
                } else {
                    erro(0);
                }
        } else if(!strcmp(tk.type, "EOF")){
        } /*else{
            erro(unspecifiedError);
        }*/
    }
}

int tipo(){
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
                    erro(TYPE_EXPECTED);
                }
            } else if(!strcmp(tk.type, "EOF") || strcmp(tk.content, ")")){
                erro(fechaParenteseExpected);
            }
        }
    } else {
        erro(TYPE_EXPECTED);
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
                    erro(TYPE_EXPECTED);
                }
            } else if(!strcmp(tk.type, "EOF") || strcmp(tk.content, ")")){
                erro(fechaParenteseExpected);
            }
        }
    } else {
        erro(TYPE_EXPECTED);
    }
}

void cmd(){
    if(!strcmp(tk.type, "PR") && !strcmp(tk.content, "se")){
        puts("SE");
        call_analyzer();
        if(!strcmp(tk.type, "SN") && !strcmp(tk.content, "(")){
            puts("ABRE PARENTESE");
            call_analyzer();
            expr();
            if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ")")){
                puts("FECHA PARENTESE");
                call_analyzer();
                cmd();
                if(!strcmp(tk.type, "PR") && !strcmp(tk.content, "senao")){
                    puts("SENAO");
                    call_analyzer();
                    cmd();
                }
            } else {
                erro(fechaParenteseExpected);
            }
        } else {
            erro(0);
        }
    } else if(!strcmp(tk.type, "PR") && !strcmp(tk.content, "enquanto")){
        puts("ENQUANTO");
        call_analyzer();
        if(!strcmp(tk.type, "SN") && !strcmp(tk.content, "(")){
            puts("ABRE PARENTESE");
            call_analyzer();
            expr();
            if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ")")){
                puts("FECHA PARENTESE");
                call_analyzer();
                cmd();
            } else {
                erro(fechaParenteseExpected);
            }
        } else {
            erro(0);
        }
    } else if(!strcmp(tk.type, "PR") && !strcmp(tk.content, "para")){
        puts("PARA");
        call_analyzer();
        if(!strcmp(tk.type, "SN") && !strcmp(tk.content, "(")){
            puts("ABRE PARENTESE");
            call_analyzer();
            atrib();
            if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ";")){
                puts("PONTO E VIRGULA");
                call_analyzer();
                expr();
                if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ";")){
                    puts("PONTO E VIRGULA");
                    call_analyzer();
                    atrib();
                    if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ")")){
                        puts("FECHA PARENTESE");
                        call_analyzer();
                        cmd();
                    } else {
                        erro(fechaParenteseExpected);
                    }
                } else {
                    erro(pontoVirgulaExpected);
                }
            } else {
                erro(pontoVirgulaExpected);
            }
        }
    } else if (!strcmp(tk.type, "PR") && !strcmp(tk.content, "retorne")){
        puts("RETORNE");
        call_analyzer();
        expr();
        if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ";")){
            puts("PONTO E VIRGULA");
            call_analyzer();
        } else {
            erro(pontoVirgulaExpected);
        }
    } else if(!strcmp(tk.type, "ID")){
        puts("IDENTIFICADOR");
        call_analyzer();
        if(!strcmp(tk.type, "SN") && !strcmp(tk.content, "(")){
            puts("ABRE PARENTESE");
            call_analyzer();
            expr();
            while(strcmp(tk.content, ")")){
                if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ",")){
                    puts("SINAL VIRGULA");
                    call_analyzer();
                    expr();
                } else {
                    erro(0);
                }
            }
            if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ")")){
                puts("FECHA PARENTESE");
                call_analyzer();
                if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ";")){
                    puts("PONTO E VIRGULA");
                    call_analyzer();
                } else {
                    erro(pontoVirgulaExpected);
                }
            } else {
                erro(fechaParenteseExpected);
            }
        }
    } else if(!strcmp(tk.type, "SN") && !strcmp(tk.content, "{")){
        puts("ABRE CHAVE");
        call_analyzer();
        cmd();
        if(!strcmp(tk.type, "SN") && !strcmp(tk.content, "}")){
            puts("FECHA CHAVE");
            call_analyzer();
        } else {
            erro(0);
        }
    } else if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ";")){
        puts("PONTO E VIRGULA");
        call_analyzer();
    } else {
        atrib();
        if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ";")){
            puts("PONTO E VIRGULA");
            call_analyzer();
        } else {
            erro(pontoVirgulaExpected);
        }
    }
}

void atrib(){
    if(!strcmp(tk.type, "ID")){
        puts("IDENTIFICADOR");
        call_analyzer();
        if(!strcmp(tk.type, "SN") && !strcmp(tk.content, "=")){
            puts("SINAL IGUAL");
            expr();
        } else {
            erro(0);
        }
    }
}

void expr(){
    expr_simp();
    call_analyzer();
    if((!strcmp(tk.type, "SN") && !strcmp(tk.content, "==")) ||
       (!strcmp(tk.type, "SN") && !strcmp(tk.content, "!=")) ||
       (!strcmp(tk.type, "SN") && !strcmp(tk.content, "<=")) ||
       (!strcmp(tk.type, "SN") && !strcmp(tk.content, "<")) ||
       (!strcmp(tk.type, "SN") && !strcmp(tk.content, ">=")) ||
       (!strcmp(tk.type, "SN") && !strcmp(tk.content, ">"))){
           op_rel();
           expr_simp();
    }
}

void expr_simp(){
    call_analyzer();
    if(!strcmp(tk.type, "SN") && !strcmp(tk.content, "+") || !strcmp(tk.content, "-")){
        puts("SINAL MAIS OU SINAL MENOS");
        //call_analyzer();      "termo" já chama o próprio analyzer
    }
    termo();
    while((!strcmp(tk.type, "SN") && !strcmp(tk.content, "+")) || (!strcmp(tk.type, "SN") && !strcmp(tk.content, "-")) || (!strcmp(tk.type, "SN") && !strcmp(tk.content, "||"))){
        termo();
    }

}

void termo(){
    fator();
    call_analyzer();
    while((!strcmp(tk.type, "SN") && !strcmp(tk.content, "*")) || (!strcmp(tk.type, "SN") && !strcmp(tk.content, "/")) || (!strcmp(tk.type, "SN") && !strcmp(tk.content, "&&"))){
        puts("SINAL MULTIPLICACAO OU SINAL DIVISAO OU SINAL AND");
        fator();
        call_analyzer();
    }
}

void fator(){
    call_analyzer();
    if(!strcmp(tk.type, "ID")){
        puts("IDENTIFICADOR");
        if(!strcmp(tk.type, "SN") && !strcmp(tk.content, "(")){
            puts("ABRE PARENTESE");
            call_analyzer();
            expr();
            while(!strcmp(tk.type, "SN") && !strcmp(tk.content, ",")){
                puts("VIRGULA");
                call_analyzer();
                expr();
            }
            if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ")")){
                puts("FECHA PARENTESE");
            } else{
                erro(fechaParenteseExpected);
            }
        }
    } else if(!strcmp(tk.type, "CTI")){
        puts("CONSTANTE INTEIRA");
    } else if(!strcmp(tk.type, "CTR")){
        puts("CONSTANTE REAL");
    } else if(!strcmp(tk.type, "CTC")){
        puts("CONSTANTE CARACTERE");
    } else if(!strcmp(tk.type, "CTL")){
        puts("CONSTANTE LITERAL");
    } else if(!strcmp(tk.type, "SN") && !strcmp(tk.content, "!")){
        puts("EXCLAMACAO");
        fator();
    } else if(!strcmp(tk.type, "SN") && !strcmp(tk.content, "(")){
        puts("ABRE PARENTESE");
        call_analyzer();
        expr();
        if(!strcmp(tk.type, "SN") && !strcmp(tk.content, ")")){
            puts("FECHA PARENTESE");
        } else{
            erro(fechaParenteseExpected);
        }
    } else{
        erro(0);
    }
}

void op_rel(){
    if((!strcmp(tk.type, "SN") && !strcmp(tk.content, "==")) ||
       (!strcmp(tk.type, "SN") && !strcmp(tk.content, "!=")) ||
       (!strcmp(tk.type, "SN") && !strcmp(tk.content, "<=")) ||
       (!strcmp(tk.type, "SN") && !strcmp(tk.content, "<")) ||
       (!strcmp(tk.type, "SN") && !strcmp(tk.content, ">=")) ||
       (!strcmp(tk.type, "SN") && !strcmp(tk.content, ">"))){
           puts("OPERADOR DE RELACAO");
    } else{
        erro(opRel);
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
