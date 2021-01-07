#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "stack.h"
#define SCALE 5


void init_stack_big(big_stack *s){
	*s = NULL;
    return;
}
void push_stack_big(big_stack *s,bignum num) {
    node2* p;
    p = (node2*)malloc(sizeof(node2));
    if(!p){
        return;
    }
    p->num = num;
    p->next = *s;
    *s = p;
}
int isEmpty_stack_big(big_stack s) {
    return s == NULL;
}


bignum peek_stack_big(big_stack s){
    if(!isEmpty_stack_big(s)) {
        return s->num;
    }
    else {
	    bignum res;
	    init(&res);
	    res.len = -1;
	    return res;
    }
}



bignum pop_stack_big(big_stack *s) { 
    if(isEmpty_stack_big(*s)) {
        bignum res;
	init(&res);
	res.len = -1;
	return res;
    }

    bignum ele = (*s)->num;
    node2 * p = *s;
    *s = (*s)->next;
    p->next = NULL;
    free(p);
    return ele;
}


void display_stack_big(big_stack s){
    node2 * p;
    if(s == NULL){
        return;
    }
    else {
        p = s;
        while(p){
            print_num(p->num,SCALE);
            p = p-> next;
        }
    }
}

void destroy_stack_big(big_stack *s) {
    big_stack current = *s; 
    big_stack next; 
  
   while (current != NULL){ 
       next = current->next; 
       free(current); 
       current = next; 
   }
   *s = NULL;

}



void init_stack(stack *s){
	*s = NULL;
    return;
}
void push(stack *s,char data){
    stack_node* p;
    p = (stack_node*)malloc(sizeof(stack_node));
    if(!p){
        return;
    }
    p->data =data;
    p->next = *s;
    *s = p;
}
int isEmpty(stack s){
    if(s == NULL)
        return 1;
    else
        return 0;
}
char peek(stack s){
    if(!isEmpty(s)){
        return s->data;
    }else
        return '#';
}
char pop(stack *s){
    if(isEmpty(*s)){
        return '#' ;
    }
    char ele=(*s)->data;
    stack_node * p = *s;
    *s = (*s)->next;
    p->next = NULL;
    free(p);
    return ele;

}
void display(stack s){
    stack_node * p;
    if(s == NULL){
        return;
    }
    else{
        p = s;
        while(p){
            printf("%c\n", p->data);
            p = p->next;
        }
    }
}
void destroy(stack *s){
    stack current = *s; 
    stack next; 
  
   while (current != NULL){ 
       next = current->next; 
       free(current); 
       current = next; 
   }*s = NULL; 
}













