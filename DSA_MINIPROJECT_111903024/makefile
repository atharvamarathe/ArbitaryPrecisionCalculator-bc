all : miniproject



miniproject : mini.o stack.o expression_evaluate.o operations.o bignum.o
	gcc -o miniproject mini.o stack.o expression_evaluate.o operations.o bignum.o

mini.o : mini.c mini.h
	gcc -c   mini.c
stack.o : stack.c stack.h
	gcc -c   stack.c
operations.o : operations.c operations.h
	gcc -c   operations.c
bignum.o : bignum.c bignum.h
	gcc -c   bignum.c
expression_evaluate.o : expression_evaluate.c expression_evaluate.h
	gcc -c  expression_evaluate.c
		
