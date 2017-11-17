#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analex.h"

//char file_name[] = {"imput.cmm"};

Token tk;
FILE *imput;
state = 0, line = 1;
char reserved_words[][11] = {
                             "se",
                             "entao",
                             "senao",
                             "enquanto",
                             "para",
                             "faca",
                             "retorne",
                             "semretorno",
                             "inteiro",
                             "real",
                             "caracter",
                             "booleano",
                             "semparam",
                             "prototipo",
                             };

char sinals[][3] = {
                    ";", ",", "<", "<=", ">",
                    ">=", "=", "!=", "==", "(",
                    ")", "[", "]", "{", "}", "\n",
                    "*", "/", "+", "-", "&&", "||",
                    "!"
                    };

Token lexical_analyzer() {
    //printf("arquivo: %p\n", imput);
    char atom, string[256] = {"\0"}, str_atom[2] = {"\0"};
    if(imput != NULL){
            int i;
            atom = getc(imput);
            //printf("atom: %c", atom);
            if(atom == '\n'){
                line++;
            }
            if(state == 0){
                strcpy(tk.content, "");
                strcpy(tk.type, "");
            }
            //printf("line: %d\tstate: %d\tchar: [%c]\n", line, state, atom);
            switch(state){
                case 0:
                    if(atom == EOF){
                        state = 0;
                        strcat(tk.content, "EOF");
                        strcat(tk.type, "EOF");
                    } else
                    if(atom == '\n' || atom == ' ' || atom == '\t'){
                        state = 0;
                        lexical_analyzer();
                    } else if(isalpha(atom)){
                        state = 1;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                        //printf("alpha: [%c]\n", atom);
                    } else if(isdigit(atom)){
                        state = 3;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                        //printf("number: [%c]", atom);
                    } else if(atom == '\''){
                        state = 8;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                        //printf("sinal: %c", atom);
                    } else if(atom == '"'){
                        state = 14;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                        //printf("sinal: %c", atom);
                    } else if(atom == '&'){
                        state = 17;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                        //printf("sinal: %c", atom);
                    } else if(atom == '|'){
                        state = 19;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                        //printf("sinal: %c", atom);
                    } else if(atom == '/'){
                        state = 21;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                        //printf("token: %s, %c\n", tk.content, atom);
                        //printf("sinal: %c", atom);
                    } else if(atom == '*' || atom == '+' || atom == '-' || atom == '{' || atom == '}' || atom == ','
                              || atom == ';' || atom == '(' || atom == ')'){
                        state = 0;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                        strcpy(tk.type, "SN");
                        //printf("token: %s, %c\n", tk.content, atom);
                        //save_token(&tk);
                        //strcpy(tk.content, "");
                        //strcpy(tk.type, "");
                        //printf("sinal: %c", atom);
                    } else if(atom == '!'){
                        state = 29;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                        //printf("sinal: %c", atom);
                    }else if(atom == '<'){
                        state = 32;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                        //printf("sinal: %c", atom);
                    } else if(atom == '>'){
                        state = 35;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                        //printf("sinal: %c", atom);
                    } else if(atom == '='){
                        state = 38;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                    } else {
                        printf("Caractere invalido! <%c>", atom);
                        exit(1);
                    }
                    break;
                case 1:
                    if(isalpha(atom) || isdigit(atom) || atom == '_'){
                        str_atom[0] = atom;
                        //printf("alpha: [%c]\n", atom);
                        strcat(tk.content, str_atom);
                        //printf("tk.content: [%s]\n", tk.content);
                    } else {
                        state = 0;
                        for(i = 0; i < 14; i++){
                            if(!strcmp(reserved_words[i], tk.content)){
                                strcpy(tk.type, "PR");
                                break;
                            }else if(i == 12){
                                strcpy(tk.type, "ID");
                            }
                        }
                        //printf("token: %s, %c\n", tk.content, atom);
                        //save_token(&tk);
                        //strcpy(tk.content, "");
                        //strcpy(tk.type, "");
                        ungetc(atom, imput);
                    }
                    break;
                case 3:
                    if(isdigit(atom)){
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                    } else if(atom == '.'){
                        state = 5;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                    } else {
                        state = 0;
                        strcpy(tk.type, "CTI");
                        //save_token(&tk);
                        //strcpy(tk.content, "");
                        //strcpy(tk.type, "");
                        ungetc(atom, imput);
                    }
                    break;
                case 5:
                    if(isdigit(atom)){
                        state = 6;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                    } else {
                        printf("Erro na linha %d. [%c]\n", line, atom);
                        exit(1);
                    }
                    break;
                case 6:
                    if(isdigit(atom)){
                        state = 6;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                    } else {
                        state = 0;
                        strcpy(tk.type, "CTR");
                        //save_token(&tk);
                        //strcpy(tk.content, "");
                        //strcpy(tk.type, "");
                        ungetc(atom, imput);
                    }
                    break;
                case 8:
                    if(isprint(atom) && atom != '\'' && atom != '\\'){
                        state = 9;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                    } else if(atom == '\\'){
                        state = 11;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                    } else {
                        printf("Erro na linha %d. [%c]\n", line, atom);
                        exit(1);
                    }
                    break;
                case 9:
                    if(atom == '\''){
                        state = 0;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                        strcpy(tk.type, "CTC");
                        //save_token(&tk);
                        //strcpy(tk.content, "");
                        //strcpy(tk.type, "");
                    } else {
                        printf("Erro na linha %d. [%c]\n", line, atom);
                        exit(1);
                    }
                    break;
                case 11:
                    if(atom == 'n' || atom == '0'){
                        state = 12;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                    } else {
                        printf("Erro na linha %d. [%c]\n", line, atom);
                        exit(1);
                    }
                    break;
                case 12:
                    if(atom == '\''){
                        state = 0;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                        strcpy(tk.type, "CTC");
                        //save_token(&tk);
                        //strcpy(tk.content, "");
                        //strcpy(tk.type, "");
                    } else {
                        printf("Erro na linha %d. [%c]\n", line, atom);
                        exit(1);
                    }
                    break;
                case 14:
                    if(isprint(atom) && atom != '"' && atom != '\n'){
                        state = 15;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                    } else {
                        printf("Erro na linha %d. [%c]\n", line, atom);
                        exit(1);
                    }
                    break;
                case 15:
                    if(isprint(atom) && atom != '"' && atom != '\n'){
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                    } else if(atom == '"'){
                        state = 0;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                        strcpy(tk.type, "CTL");
                        //save_token(&tk);
                        //strcpy(tk.content, "");
                        //strcpy(tk.type, "");
                    } else {
                        printf("Erro na linha %d. [%c]\n", line, atom);
                        exit(1);
                    }
                    break;
                case 17:
                    if(atom == '&'){
                        state = 0;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                        strcpy(tk.type, "SN");
                        //save_token(&tk);
                        //strcpy(tk.content, "");
                        //strcpy(tk.type, "");
                    } else {
                        printf("Erro na linha %d. [%c]\n", line, atom);
                        exit(1);
                    }
                    break;
                case 19:
                    if(atom == '|'){
                        state = 0;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                        strcpy(tk.type, "SN");
                        //save_token(&tk);
                        //strcpy(tk.content, "");
                        //strcpy(tk.type, "");
                    } else {
                        printf("Erro na linha %d. [%c]\n", line, atom);
                        exit(1);
                    }
                    break;
                case 21:
                    if(atom == '*'){
                        state = 23;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                    } else {
                        state = 0;
                        strcpy(tk.type, "SN");
                        //save_token(&tk);
                        //strcpy(tk.content, "");
                        //strcpy(tk.type, "");
                    }
                    break;
                case 23:
                    if(isprint(atom) || atom == '\n' || atom == '\t'){
                        state = 24;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                    } else {
                        printf("Erro na linha %d. [%c]\n", line, atom);
                        exit(1);
                    }
                    break;
                case 24:
                    if(isprint(atom) && atom != '*' || atom == '\n'){
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                    } else if(atom == '*'){
                        state = 25;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                    } else {
                        printf("Erro na linha %d. [%c]\n", line, atom);
                        exit(1);
                    }
                    break;
                case 25:
                    if(atom == '/'){
                        state = 0;
                        str_atom[0] = atom;
                        strcpy(tk.content, "Comentario");
                        strcpy(tk.type, "CMT");
                        lexical_analyzer();
                        //save_token(&tk);
                        //strcpy(tk.content, "");
                        //strcpy(tk.type, "");
                    }
                    break;
                case 29:
                    if(atom == '='){
                        state = 0;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                        strcpy(tk.type, "SN");
                        //save_token(&tk);
                        //strcpy(tk.content, "");
                        //strcpy(tk.type, "");
                    } else {
                        state = 0;
                        strcpy(tk.type, "SN");
                        //save_token(&tk);
                        //strcpy(tk.content, "");
                        //strcpy(tk.type, "");
                        ungetc(atom, imput);
                    }
                    break;
                case 32:
                    if(atom == '='){
                        state = 0;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                        strcpy(tk.type, "SN");
                        //save_token(&tk);
                        //strcpy(tk.content, "");
                        //strcpy(tk.type, "");
                    } else {
                        state = 0;
                        strcpy(tk.type, "SN");
                        //save_token(&tk);
                        //strcpy(tk.content, "");
                        //strcpy(tk.type, "");
                        ungetc(atom, imput);
                    }
                    break;
                case 35:
                    if(atom == '='){
                        state = 0;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                        strcpy(tk.type, "SN");
                        //save_token(&tk);
                        //strcpy(tk.content, "");
                        //strcpy(tk.type, "");
                    } else {
                        state = 0;
                        strcpy(tk.type, "SN");
                        //save_token(&tk);
                        //strcpy(tk.content, "");
                        //strcpy(tk.type, "");
                        ungetc(atom, imput);
                    }
                    break;
                case 38:
                    if(atom == '='){
                        state = 0;
                        str_atom[0] = atom;
                        strcat(tk.content, str_atom);
                        strcpy(tk.type, "SN");
                        //save_token(&tk);
                        //strcpy(tk.content, "");
                        //strcpy(tk.type, "");
                    } else {
                        state = 0;
                        strcpy(tk.type, "SN");
                        //save_token(&tk);
                        //strcpy(tk.content, "");
                        //strcpy(tk.type, "");
                        ungetc(atom, imput);
                    }
                    break;
            }
    } else {
        puts("Eh um arquivo invalido!");
        exit(1);
    }

}

void open_file(char file_name[]){
    //printf("arquivo: %s\n", file_name);
    imput = fopen(file_name, "r");
}

void save_token(Token *tk){
    if(root_token == NULL){
        root_token = (Token *) malloc(sizeof(Token));
        node = root_token;
    } else {
        node->next = (Token *) malloc(sizeof(Token));
        node = node->next;
    }
    strcpy(node->content, tk->content);
    strcpy(node->type, tk->type);
    printf("Token_list: <%s, %s>\n", node->type, node->content);
}
