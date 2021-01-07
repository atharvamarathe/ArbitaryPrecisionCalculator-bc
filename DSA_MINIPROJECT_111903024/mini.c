#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "mini.h"

/*
 * ///////////////////////////////////////////////////////////////////////////////////////////////////////////
 * 
 * This is the Driver code for the binary calculator(bc)
 * It accepts input repeatedly until it given exit condition
 * It accpet a string until '\n' i.e. enter key is pressed.
 * The string is tokenized using the get_token function.
 * It is then evaluated in the expression_evaluate.c file
 * It prints the appropriate answer or error messge if any 
 *
 * //////////////////////////////////////////////////////////////////////////////////////////////////////////
 *
 */





enum states{START, NUMBER, OP, UNARY, FINISH, ERROR, TRIGN};
int scale = 0;


int main() {
    int x = 0;
    char *m;
    printf("////////////////////////////////////////////////////////////////////////////////////\n");
    printf("---------------------------- Binary Calculator -------------------------------------\n");
    printf("////////////////////////////////////////////////////////////////////////////////////\n");
    printf("To set Scale type S = scale\n");
    printf("Press q to quit \n");
    printf("\n");
    
    while(1) {
       m = inputString(stdin, 10);
    	if(!m){
	    	printf("INVALID\n");
	    	exit(0);
    	}

        if(m[0] == 'q')
            exit(0);
        if(m[0] == 'S' && m[1] == '=') {
            x = 2;
            if(scale != 0)
                scale = 0;
            while(m[x] != '\0') {
            scale = scale * 10 + (m[x] - '0');
            x +=1;
            }
        }
        else {
    	bignum answer;
    	answer = infix_eval(m);
    	if(answer.a == NULL && answer.len == -1){
	    	printf("INVALID EXPRESSION\n");
	    
    	}
    	print_num(answer,scale);
        }
    }
     return 0;
    
}

/*
 * getbig_num() --> returns bignum data type from the string of input
 */

bignum getbig_num(char *str, int start, int end, char sign){
    bignum num;
    init(&num);
    if(sign == NEGATIVE)
   	 num.sign = NEGATIVE;
    int j=0, k = 1,i;
    for(j = start; j < end; j++){
        if(str[j] == '.')
            break;
        else
            continue;
    }
   
    for(i = start ;i < j ;i++) {
	    num.a = add_digit(str[i],num.a);
	    num.len+=1;
    }
    if( j != end) {
	    
	    num.f_enable = '1';
    	for(i=j+1;i<end;i++) {
	
		num.b = add_fdigit(str[i],num.b);
		num.flen +=1;
	}
	
    }	
	return num;
}



int check_parenthesis(char *expr) {
	int count = 0;
	for(int i = 0; i < strlen(expr) ; i++){
		if(expr[i] == '('){
			count++;
		}else if(expr[i] == ')'){
			count--;
		}
	}if(count == 0){
		return 1;
	}return 0;
}



token get_token(char *expr) {
    bignum num;
    token t;
    init(&t.data.num);
	static int start_index = 0;
	static char sign;
    static int i = 0;
    static enum states currstate = START;
    char currchar;
    enum states nextstate;
    while(1){
        currchar = expr[i];
        switch (currstate){
            case START :
                switch(currchar){
                    case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':case '.':
						start_index = i;
						sign = POSITIVE;
						nextstate = NUMBER;
						i++;
						break;
					case '-' :
						nextstate = UNARY;
						i++;
						break;
					case '(' :
						nextstate = OP;
						i++;
						break;
					case '\0':
						nextstate = FINISH;
						break;

					case 's': case 'c': case 't':
						nextstate = TRIGN;
						i++;
						//trig = currchar;
						break;
					default:                            // anything else
						nextstate = ERROR;
						break;
				}
				currstate = nextstate;
				break;
			case NUMBER :
                switch(currchar){
                    case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':case '.':
						nextstate = NUMBER; 
						i++;
						break;
                    case '+': case '-': case '*': case '/': case '%': case '(': case ')': case '>': case '<': case '^':

						nextstate = OP;
						t.type = OPERAND;
                       				 num = getbig_num(expr, start_index, i, sign);
					
						t.data.num = num;
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						nextstate = FINISH;
						t.type = OPERAND;
						num = getbig_num(expr, start_index, i, sign);
				
			                        t.data.num = num;
						currstate = nextstate;
						return t;
						break;
			
					default: // anything else
						nextstate = ERROR;
						break;                                                                                     
				}
                currstate = nextstate;
			    break;
            case OP :
                switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':case '.':
                        start_index = i;
						sign = POSITIVE;    // CHANGED HERE
						nextstate = NUMBER;

						t.type = OPERATOR;
						t.data.op = expr[i - 1];
						currstate = nextstate;
                        i++;
						return t;
						break;
					case '+': case '-': case '*': case '/': case '%': case '(': case ')': case '>': case '<': case '^':
						if(expr[i-1] == ')'){
							if(currchar == '('){
								nextstate = ERROR;
								currstate = nextstate;
								break;	
							}nextstate = OP;
							t.type = OPERATOR;
							t.data.op = expr[i - 1];
							currstate = nextstate;
							i++;
							return t;
							break;
						}else if(currchar == '-'){
							nextstate = UNARY;
							t.type = OPERATOR;
							t.data.op = expr[i - 1];
							currstate = nextstate;
							i++;
							return t;
							break;
						}
						else if(currchar != '(') {
							nextstate = ERROR;
							currstate = nextstate;
							break;
						}
						nextstate = OP;
						t.type = OPERATOR;
						t.data.op = expr[i - 1];
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						if(expr[i - 1] != ')') {
							nextstate = ERROR;
							currstate = nextstate;
							break;
						}
                        nextstate = FINISH;
						t.type = OPERATOR;
						t.data.op = expr[i - 1];
						currstate = nextstate;
						return t;
						break;
		
					case 's': case 'c' : case 't':
						nextstate = TRIGN;
						t.type = OPERATOR;
						t.data.op = expr[i - 1];
						currstate = nextstate;
						i++;
						//trig = currchar;
						return t;
						break;
					default: // anything else
						nextstate = ERROR;
					 	break;
				}
				break;
            case FINISH :
                t.type = END;
                currstate = START;
                start_index = 0;
                i = 0;
				return t;
				break;
            case ERROR :
				t.type = ERR;
                currstate = START;
                start_index = 0;
                i = 0;
				return t;
				break;
            
			case UNARY :
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':case '.':
                        start_index = i;
						sign = NEGATIVE;   //CHANGED HERE
 						nextstate = NUMBER;
						currstate = nextstate;
                        i++;
						break;
					case '+': case '-': case '*': case '/': case '%': case '(': case ')': case '>': case '<': case '^':
						if(currchar != '(') {
							nextstate = ERROR;
							currstate = nextstate;
							break;
						}
						nextstate = OP;
						t.type = UNARY_OPERATOR;

						//Replaced unary minus symbol with '@'
						
						t.data.op = '@';
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						nextstate = ERROR;
						currstate = nextstate;
						break;
	
					case 's': case 'c' : case 't':
						nextstate = TRIGN;
						t.type = UNARY_OPERATOR;
						//Replaced unary minus symbol with '@'
						t.data.op = '@';
						currstate = nextstate;
						i++;
						//trig = currchar;
						return t;
						break;
					default: // anything else
						nextstate = ERROR;
					 	break;
				}
				break;
            case TRIGN :
				break;	
        }
    }

}




/*
 * inputString function() --> For taking input from the user 
 */

char *inputString(FILE *fp, size_t size){

    char *str;
    char ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(char)*size);
    if(!str)return str;
    while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
        if(ch!=32)
            str[len++]=ch;
        if(len==size){
            str = realloc(str, sizeof(char)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(char)*len);
}

