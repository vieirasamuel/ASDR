#ifndef ANASINT_H
#define ANASINT_H

#define MAXIMUM_SYMBOLS_SIZE 1000

/*
*
*/
typedef struct symbol{
    char name[];
    int type;       // 1 = inteiro 2 = caracter 3 = real
    int category;   // 1 = vari�vel 2 = fun��o
    int scope;      // 1 = local 2 = global
}symbol;

/*
*
*/
extern symbol symbols_table[MAXIMUM_SYMBOLS_SIZE];

/*
*
*/
extern int top_symbols_table = 0;

#endif // ANASINT_H
