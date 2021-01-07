#ifndef EXPRESSION_EVALUATE_H
#define EXPRESSION_EVALUATE_H

#include "stack.h"
#include "bignum.h"

int precedence(char c);

bignum perform_operation(big_stack *st_num, stack * st_op);

bignum infix_eval(char *expr);







#endif
