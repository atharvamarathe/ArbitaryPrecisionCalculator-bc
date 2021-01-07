
#include<stdio.h>
#include<stdlib.h>
#include "stack.h"
#include "operations.h"
#include "mini.h"

/*
 * //////////////////////////////////////////////////////////////////////////////////////////////////////
 *
 *      Infix Evaluator using Two stacks
 *      Take one token at a time and put it in respective stack
 *      Then it evaluates it appropriately.
 *      
 *  //////////////////////////////////////////////////////////////////////////////////////////////////////    
*/ 

int precedence(char c) {
    switch(c){
        case '+':
        case '-':
            return 1;
            break;
        case '*':
        case '/':
        case '%':
            return 2;
            break;
        case '^':
            return 3;
            break;
        case '@':
            return 4;
            break;
        default:
            return 0;
    }
}

/* This function will perform respective operation on top two elements of stack.
    Return type : Returns number of type bignum
*/
bignum perform_operation(big_stack *st_num, stack * st_op){
    bignum first , second;
    bignum ret_num;
    second = pop_stack_big(st_num);
    first = pop_stack_big(st_num);
    char op = pop(st_op);
    switch(op){
        case '@':
            push_stack_big(st_num, first);
            second.sign = NEGATIVE;
            ret_num =  second; 
            break;
        case '+':
            ret_num =  add_bignum(first, second);
            delete_bignum(first);
            delete_bignum(second);
            break;
        case '-':
            ret_num =  subtract_bignum(first, second);
            delete_bignum(first);
            delete_bignum(second);
            break;
        case '*':
            ret_num =  multiply_bignum(first, second);
            delete_bignum(first);
            delete_bignum(second);
            break;
        case '/':
            if (is_bignum_zero(second)){
                delete_bignum(first);
                delete_bignum(second);
                destroy_stack_big(st_num);
                destroy(st_op);
                bignum res;
		init(&res);
		res.len = -1;
		return res;
            }
	    ret_num =  divide_bignum(first, second,SCALE);
            delete_bignum(first);
            delete_bignum(second);
            break;
    }return ret_num;
}

bignum infix_eval(char *expr) {
    big_stack st_num;
    bignum num;
    stack st_op;
    init_stack(&st_op);
    init_stack_big(&st_num);
    token t;
    while(1){

        t = get_token(expr);

        switch (t.type){
            case OPERAND:
                push_stack_big(&st_num, t.data.num);
                break;
            case OPERATOR :
                if(isEmpty(st_op)){
                    push(&st_op, t.data.op);
                }else if(t.data.op == '('){
                    push(&st_op, t.data.op);
                }
                //Closed brace, evaluate the entire brace
                else if(t.data.op ==')') {
                    while(peek(st_op) != '('){
                        num = perform_operation(&st_num , &st_op);
                        //push it back to stack
                        push_stack_big(&st_num, num);
                    }
                    pop(&st_op);
                }
     
                else{
                    while(!isEmpty(st_op) && precedence(t.data.op) <= precedence(peek(st_op))){
                        
                        num = perform_operation(&st_num , &st_op);
                        //push it back to stack
                        push_stack_big(&st_num, num);
                    }
                    //Now push the current operator to stack
                    push(&st_op, t.data.op);
                }
                break;
            case UNARY_OPERATOR :
                push(&st_op, t.data.op);
                break;
            case END :
                while(!isEmpty(st_op)){
                    num = perform_operation(&st_num , &st_op);
                    //push it back to stack
                    push_stack_big(&st_num, num);
                }
                return pop_stack_big(&st_num);
                break;
            case ERR :
                destroy_stack_big(&st_num);
                destroy(&st_op);
		bignum res;
		init(&res);
		res.len = -1;
                return res;
                break;
        }
    }
}
                
