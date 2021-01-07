#include <stdio.h>
#include "bignum.h"
#include <stdlib.h>
#define POSITIVE '0'
#define NEGATIVE '1'


/*
 * //////////////////////////////////////////////////////////////////////////////////////////
 *
 * This file contains the basic functions of the ADT Bignum
 * BASIC STRCUTURE OF BIGNUM :-
 * COMPONENTS :-
 * 1) char sign --> Contains the sign of the bignum
 * 2) int len  ---> Contains the length of the integer part
 * 3) int flen ----> Contains the length of the fractional part
 * 4) char f_enable --> Flag which states whether a number is floating point or not
 * 5) num *a  --> Doubly linked list which contains integer part of the bignum
 * 6) fnum *b --> Doubly linked list which contains fractional part of the bignum
 *
 * //////////////////////////////////////////////////////////////////////////////////////////////
 *
 */


num * add_digit(char digit, num *head) {
	num *q, *p;
	p = head;
	q = (num *)malloc(sizeof(num));

		q -> whole = digit;

	q -> next = NULL;
	q -> prev = NULL;
	if( head == NULL) {
		return(q);
	}
	else {
		while(p -> next != NULL) {
			p = p-> next;
		}
		q ->prev = p;
		p -> next = q;
		return(head);


	}
	
}


fnum * add_fdigit(char digit, fnum *head) {
	fnum *q, *p;
	p = head;
	q = (fnum *)malloc(sizeof(fnum));

		q -> frac = digit;

	q -> next = NULL;
	q -> prev = NULL;
	if( head == NULL) {
		return(q);
	}
	else {
		while(p -> next != NULL) {
			p = p-> next;
		}
		q ->prev = p;
		p -> next = q;
		return(head);


	}
	
}


void print_num(bignum p, int scale) {
        num *q;
        q = p.a;
        fnum *r;
        r = p.b;
        int count = 0;
        if(p.sign == NEGATIVE)
        	printf("-");
        while(q -> whole == '0' && q -> next != NULL)
        	q = q -> next ;
        while(q!= NULL) {
        	printf("%c",q -> whole);
                q = q -> next;
	}
                if(scale !=0) {
                	printf(".");
                        while(r!= NULL && count < scale) {
                        	printf("%c",r -> frac);
                                count +=1;
                                r = r -> next;
			}
                        if(count < scale) {
                        	while(count < scale) {
                                	printf("0");
                                        count +=1;
				}
			}
		}
		printf("\n");
}



num * delete_firstnode(num *head) {
	num *p;
	p = head;
	if(head != NULL)
		head = head -> next;
	if(head != NULL) {
		head -> prev = NULL;	
		free(p);
	}
	return head;
}

	

		


int maxlen(bignum num1, bignum num2, char a) {
	if(a == '1') {
		if(num1.len>=num2.len)
	
			return num1.len;
		return num2.len;
	}
	else if(a == '0') {
	       if(num1.flen >= num2.flen)
		       return num1.flen;
	       return num2.flen;
	}

}

/*
 * returns 1 if num1 > num2
 * returns 0 if both equal
 * returns -1 if num2 > num1
 *
 */
int comparator(bignum p, bignum q) {
	int plen,qlen;
	num *p1, *q1;
	p1 = p.a;
	q1 = q.a;
	plen = p.len;
	qlen = q.len;
	int res = 0;
	if(p.sign == NEGATIVE && q.sign == POSITIVE) {
		return -1;
	}
	else if(p.sign == POSITIVE && q.sign == NEGATIVE) {
		return 1;
	}
	else {
		while(p1 -> whole == '0' && p1 -> next != NULL) {
			plen = plen - 1;
			p1 = p1 -> next ;
		}
		while(q1 -> whole == '0' && q1 -> next != NULL) {
			qlen = qlen - 1;
			q1 = q1 -> next ;
		}
		if(plen > qlen) {
			return 1;
		}
		else if(plen < qlen) {
			return -1;
		}
		else {
			while(p1!=NULL) {
				if(p1 -> whole > q1 -> whole) {
					return 1;
				}
			
				else if( q1 -> whole > p1 -> whole) {
					return -1;
				}
				p1 = p1 -> next;
				q1 = q1 -> next;
			}
		}
		if(p.f_enable == '1' || q.f_enable == '1') {
			if(q.f_enable == '0') {
				fnum *p2;
				p2 = p.b;
				while(p2 != NULL) {
					if(p2 -> frac != '0')
						return 1;
					p2 = p2 -> next;
				}
				return 0;
			}
			else if(p.f_enable == '0') {
				fnum *q2;
				q2 = q.b;
				while(q2 != NULL) {
					if(q2 -> frac != '0')
						return -1;
					q2 = q2 -> next;
				}
				return 0;
			}
			else {
				fnum *p2, *q2;
				p2 = p.b;
				q2 = q.b;
				if(p.flen >= q.flen) {
					while(q2!= NULL) {
						if(p2 -> frac > q2 -> frac) 
							return 1;
						else if( q2 -> frac > p2 -> frac)
							return -1;
						p2 = p2 -> next;
						q2 = q2 -> next;
					}
					if(p2 != NULL) {
						while(p2 != NULL) {
							if( p2 -> frac != '0')
								return 1;
							p2 = p2 -> next;
						}
					}
				}
				else if(q.flen > p.flen) {
					while(p2 != NULL) {
						if(p2 -> frac > q2 -> frac)
							return 1;
						else if(q2 -> frac > p2 -> frac)
							return -1;
						p2 = p2 -> next;
						q2 = q2 -> next;
					}
					if(q2 != NULL) {
						while(q2 != NULL) {
							if(q2 -> frac != '0')
								return -1;
							q2 = q2 -> next;
						}
					}
				}
			}
		}



	}
	return 0;
}


bignum concatenate(bignum num1) {
	bignum res;
	num *p, *r;
	fnum *q;
	p = num1.a;
	q = num1.b;
	init(&res);
	res.len = num1.len + num1.flen;
	r = res.a;
	int i = 0;
	while(p != NULL) {
		res.a = add_digit(p -> whole,res.a);
		p = p -> next;
	}
	while(q != NULL) {
		res.a = add_digit( q -> frac,res.a);
		q = q -> next;
	}
	return res;
}


void init(bignum *n1) {

	n1 -> sign = POSITIVE;
	n1 -> f_enable = '0';
	n1 -> a = NULL;
	n1 -> len = 0;
	n1 -> b = NULL;
	n1 -> flen = 0;
}

bignum split_bignum(bignum n1, int a, int total) {
	bignum res;
	init(&res);
	res.sign = n1.sign;
	res.f_enable = '1';
	num *p, *q;
	fnum *r;
	p = n1.a;
	r = res.b;
	int i =  0;
	if(total > a) {
		while(i < (total - a)) {
			res.a = add_digit(p -> whole,res.a);
			p = p -> next;
			i +=1 ;
		}
		while( p != NULL) {
			res.b = add_fdigit( p -> whole, res.b);
			p = p -> next;
		}
		res.len = total - a;
		res.flen = a;
		res.f_enable = '1';
		return  res;
	}
	else if(total == a) {
	
		res.a = add_digit('0',res.a);
		while( p != NULL) {
			res.b = add_fdigit( p -> whole, res.b);
			p = p -> next;
		}
		res.f_enable = '1';
		res.flen = a;
		return res;
	}
	else {
		res.a = add_digit('0',res.a);
		while(i < (a - total)) {
			res.b = add_fdigit('0',res.b);
			i +=1 ;
		}
		while( p != NULL) {
			res.b = add_fdigit(p -> whole,res.b);
			p = p -> next;
		}
		res.f_enable = '1';
		res.flen = a;
		return res;
	}

}



void delete_bignum(bignum n) {
	num *current, *next;
	fnum *fcurrent, *fnext;
	current  = n.a;
	fcurrent = n.b;
	while(current != NULL) {
		next = current -> next;
		free(current);
		current = next;
	}
	n.a = NULL;
	while(fcurrent != NULL) {
		fnext = fcurrent -> next;
		free(fcurrent);
		fcurrent = fnext;
	}
	n.b = NULL;
	n.len = -1;
	n.flen = -1;
	return;
}

int is_bignum_zero(bignum n1) {

	num *q;
	fnum *w;
	q = n1.a;
	w = n1.b;
	while(q != NULL) {
		if(q -> whole != '0')
			return 0;
		q = q -> next;
	}
	while( w != NULL) {
		if( w -> frac != '0')
			return 0;
		w = w -> next;
	}
	return 1;
}


