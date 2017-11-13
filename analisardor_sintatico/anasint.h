#ifndef ANASINT_H
#define ANASINT_H

#define MAX_SYMBOL_NAME_SIZE 256
#define MAX_SYMBOLS_TABLE_SIZE 1000

/*
*
*/
typedef struct symbol{
    char name[MAX_SYMBOL_NAME_SIZE];
    int type;       // 1 = inteiro 2 = caracter 3 = real
    int category;   // 1 = variável 2 = função
    int scope;      // 1 = local 2 = global
}symbol;

char erros[][50];

/*
*
*/
extern symbol symbols_table[MAX_SYMBOLS_TABLE_SIZE];

/*
*
*/
extern int top_symbols_table;

#endif // ANASINT_H
