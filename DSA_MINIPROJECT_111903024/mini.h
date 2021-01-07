#ifndef MINI_H
#define MINI_H
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "bignum.h"
#include "expression_evaluate.h"


#define OPERAND  100
#define OPERATOR 200
#define END      300
#define ERR      400
#define UNARY_OPERATOR 500
#define POSITIVE '0'
#define NEGATIVE '1'
#define SCALE     5

//
// A token datatype that will store type of token and token itself
//      (Operator or Operand or End or Error)
//
typedef struct token{
    int type;         //OPERATOR , OPERAND, END  , ERR

    //Used union as we have to store one of two tokens.
    
    union data{
        bignum num;
        char op;
    }data;
}token;





token get_token(char *expr);
char *inputString(FILE *fp, size_t size);
bignum getbig_num(char *str, int start, int end, char sign);
int check_parenthesis(char *expr);


#endif
