#ifndef ANALEX_H
#define ANALEX_H

#define FILE_NAME_SIZE 256

char file_name[FILE_NAME_SIZE];

/*
*
*/
char reserved_words[][11];

/*
*
*/
char sinals[][3];

/*
*
*/
typedef struct Token{
    char type[4];
    char content[256];
    struct Token *next;
}Token;

/*
*
*/
Token *root_token;
Token *node;

extern Token tk;
extern FILE *imput;
extern int state;
int line;

void open_file(char file_name[]);

void save_token();

Token lexical_analyzer();

#endif // ANALEX
