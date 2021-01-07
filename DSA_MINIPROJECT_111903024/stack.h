#ifndef STACK_H
#define STACK_H
#include "bignum.h"
typedef struct node2{
    	bignum num;
    	struct node2 *next;
}node2;

typedef node2* big_stack;
//
typedef struct stack_node{
    	char data;
    	struct stack_node *next;
}stack_node;
typedef stack_node* stack;



void init_stack(stack *s);

void push(stack *s,char data);

int isEmpty(stack s);

char peek(stack s);

char pop(stack *s);

void display(stack s);

void destroy(stack *s);




void init_stack_big(big_stack *s);

void push_stack_big(big_stack *s,bignum data);

int isEmpty_stack_big(big_stack s);

bignum peek_stack_big(big_stack s);

bignum pop_stack_big(big_stack *s);

void display_stack_big(big_stack s);

//void display(big_stack s);

void destroy_stack_big(big_stack *s);
#endif


