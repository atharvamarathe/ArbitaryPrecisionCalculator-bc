#include <stdio.h>
#include <stdlib.h>
#include "bignum.h"
#include "operations.h"

#define SCALE 20
#define POSITIVE '0'
#define NEGATIVE '1'



/*
 * //////////////////////////////////////////////////////////////////////////////////////////////////////
 *
 * This file contains basic arithmatic functions for the bignum data structure :
 *  1) divide_bignum(num1 , num2) --> Division of two bignums
 *
 *  2) multiply_bignum(num1, num2) --> Multiplication of the two bignums.
 *
 *  3) subtract_bignum(num1, num2) -->  Subtraction of the two bignums
 *
 *  	i)  subtract_num(num1, num2) --> absolute subtraction of the integer linked list.
 *  	ii) subtract_fnum(num1, num2) --> absolute subtraction of the fractional part linked list.
 *
 *  4) add_bignum(num1, num2) --> addition of the two bignums
 *  	i) add_num(num1, num2) --> Absolute addition of the integer part of the bignum
 *  	ii) add_fnum(num1, num2) -> Absolute subtraction of the fractional part of the bignum
 *
 * //////////////////////////////////////////////////////////////////////////////////////////////////////
 */



/*
 * Function :- leftshift(bignum num, int n)
 * Description :- left shifts integer part of the bignum data structure.
 * i.e. adds zeros to the right by a specified number of times given by the second argument to the 
 * function
 *return type -> bignum
 */

bignum leftshift(bignum num, int n) {
	for(int i =0; i < n; i++) {
		num.a = add_digit('0',num.a);
		num.len +=1;
	}
	return num;
}





bignum divide_bignum(bignum num1, bignum num2,int scale) {
	while(num1.a -> next != NULL && num1.a -> whole == '0') {
		num1.a = delete_firstnode(num1.a);	
		num1.len -=1;
	}
	while(num2.a -> next != NULL && num2.a -> whole == '0') {
	       num2.a = delete_firstnode(num2.a);	
		num2.len -=1;
	}
  	bignum res,temp,temp2;
  	init(&res);
  	init(&temp);
  	num *p, *q;
  	p = num1.a;
  	q = num2.a;
  	int quotient = 0;
	int i,num2_len;
	num2_len = num2.flen;

	/*
	 * division for floating point type bignums i.e. having fractional part 
	 */

	if(num1.f_enable == '1' || num2.f_enable == '1') {
		if(num1.f_enable == '0') {
			num1.f_enable = '1';
			for( i=0;i<num2.flen;i++) {
				num1.b = add_fdigit('0',num1.b);
			}
			num1.flen = num2.flen;
		}
		else if(num2.f_enable == '0') {
			num2.f_enable = '1';
			for( i=0;i<num1.flen;i++) {
				num2.b = add_fdigit('0',num2.b);
			}
			num2.flen = num1.flen;
		}
		if(num1.f_enable == '1' && num2.f_enable == '1') {
			if(comparator(num1,num2) == 1) {
				if(num1.a -> whole != '0' && (num2.a -> whole == '0' && num2.len == 1)) {
					fnum * n2_b;
					n2_b = num2.b;
					while(n2_b -> next != NULL) {
						n2_b = n2_b -> next;
					}
					while(n2_b -> frac == '0') {
						n2_b = n2_b -> prev;
						num2.flen -=1;
					}
				
					bignum f_n2,p_ten, buffer;
					init(&buffer);
					init(&p_ten);
					n2_b = num2.b;
			       		init(&f_n2);
					f_n2.len = num2_len;
					for(i =0;i<f_n2.len;i++) {
						f_n2.a = add_digit(n2_b -> frac, f_n2.a);
						n2_b = n2_b -> next;
					}

					p_ten.a = add_digit('1',p_ten.a);
					p_ten.len +=1;
					for(i = 0;i<f_n2.len;i++) {
						p_ten.a = add_digit('0',p_ten.a);
						p_ten.len+=1;
					}
					
					buffer = multiply_bignum(num1,p_ten);
					
					res = divide_bignum(buffer,f_n2,SCALE);
					return res;
				}
					
				int t_len,n1_flen,n2_flen;
				num *temp_int;
				n1_flen = num1.flen;
				n2_flen = num2.flen;
				num1 = concatenate(num1);
				num2 = concatenate(num2);
				num1.f_enable = '0';
				num2.f_enable = '0';
				temp = divide_bignum(num1,num2,num1.len + num2.len);
				
				t_len = temp.len;
				temp = concatenate(temp);
				if(n1_flen >= n2_flen) 
					t_len = t_len + (n1_flen - n2_flen);
				else if(n1_flen < n2_flen)
					t_len = t_len + (n2_flen - n1_flen);
				temp_int = temp.a;
				for(i=0;i<t_len;i++) {
					res.a = add_digit(temp_int -> whole,res.a);
					temp_int = temp_int -> next;
					res.len +=1;
				}
				res.f_enable = '1';
				while(temp_int != NULL) {
					res.b = add_fdigit(temp_int -> whole,res.b);
					res.flen +=1;
					temp_int = temp_int -> next;
				}
				return res;
				

			}
			else if(comparator(num1,num2) == -1) {
				bignum temp2;
				int k = 0, u;
				num *final;
				init(&temp2);
				temp = divide_bignum(num2, num1,SCALE);
				temp = concatenate(temp);
				temp2.a = add_digit('1',temp2.a);
				temp2.len +=1;
				for(i = 0;i<SCALE;i++) {
					temp2.a= add_digit('0',temp2.a);
					temp2.len +=1;
				}
				while(comparator(temp2,temp) != 1) {
					temp2.a = add_digit('0',temp2.a);
					temp2.len +=1;
					k+=1;
				}
				temp = divide_bignum(temp2,temp,SCALE);
			
				k = k -1;
				res.a = add_digit('0',res.a);
				res.len =1;
				while(k>0) {
					res.b = add_fdigit('0',res.b);
					res.flen +=1;
					k -=1;
				}
				temp = concatenate(temp);
				final = temp.a;
				for(i=0;i<SCALE;i++) {
					res.f_enable = '1';
					res.b = add_fdigit(final -> whole,res.b);
					res.flen+=1;
					final = final -> next;
				}
				return res;
			}
		}


	}



	/*
	 * Division of integer type bignums 
	 *
	 */


  	if(comparator(num1,num2) == 1) {
		int i;
		for(i = 0; i < scale; i++) {
			num1.a = add_digit('0',num1.a);
			num1.len +=1;
		}
  		temp.len = num2.len;
  		for(i = 0 ;i < temp.len; i++) {
  			temp.a = add_digit(p -> whole,temp.a);
  			p = p -> next;
  		}
  		while(comparator(temp,num2) == 1 ||comparator(temp,num2) == 0) {
 			temp = subtract_bignum(temp,num2);
  			quotient +=1;
  		}
		res.a = add_digit(quotient + '0',res.a);	
		res.len +=1;
		quotient = 0;
		if(p != NULL) {
  			temp.a = add_digit(p -> whole,temp.a);
			temp.len +=1;
		}
		else if( p == NULL)
			return res;
		
  		while( p != NULL) {
  			while(comparator(temp,num2) == 1 ||comparator(temp,num2) == 0) {
				
				temp = subtract_bignum(temp,num2);
				
  				quotient +=1;

  			}
 			res.a = add_digit(quotient + '0',res.a);
			res.len +=1;
  			quotient = 0;
			p = p -> next;
			if( p!= NULL) {
  				temp.a = add_digit(p -> whole,temp.a);
				temp.len +=1;
			}
		}
		res.f_enable = '1';
		res = split_bignum(res,scale,res.len);
		while(res.a -> next != NULL && res.a -> whole == '0') {
			res.a = delete_firstnode(res.a);	
			res.len -=1;
		}
	}
	else if(comparator(num1,num2) == -1) {
		bignum temp2;
		int k = 0, u;
		num *final;
		init(&temp2);
		temp = divide_bignum(num2,num1,SCALE);
		temp = concatenate(temp);
		temp2.a = add_digit('1',temp2.a);
		temp2.len +=1;
		for(i = 0;i<SCALE;i++) {
			temp2.a= add_digit('0',temp2.a);
			temp2.len +=1;
		}
		while(comparator(temp2,temp) != 1) {
			temp2.a = add_digit('0',temp2.a);
			temp2.len +=1;
			k+=1;
		}
		temp = divide_bignum(temp2,temp,SCALE);
	
		k = k -1;
		res.a = add_digit('0',res.a);
		res.len =1;
		while(k>0) {
			res.b = add_fdigit('0',res.b);
			res.flen +=1;
			k -=1;
		}
		temp = concatenate(temp);
		final = temp.a;
		for(i=0;i<SCALE;i++) {
			res.f_enable = '1';
			res.b = add_fdigit(final -> whole,res.b);
			res.flen+=1;
			final = final -> next;
		}
	}
	else if(comparator(num1,num2) == 0) {
		res.a = add_digit('1',res.a);
		res.len = 1;
		res.f_enable = '1';
		for(i = 0;i<SCALE;i++) {
			res.b = add_fdigit('0',res.b);
			res.flen +=1;
		}
	}
  	return res;
}


bignum multiply_bignum(bignum num1, bignum num2) {

	bignum sum,tmp;
	int i,j,k;
	init(&sum);
	init(&tmp);
	num *p, *q, *r, *s;
	p = num1.a;
	q = num2.a;
	for(i = 0; i<(num1.len + num2.len); i++ ) {
		sum.a = add_digit('0',sum.a);
	}
	sum.len = num1.len + num2.len;
	for(k = 0; k<= num1.len; k++) {
		tmp.a = add_digit('0',tmp.a);
	}
	tmp.len = num1.len + 1;
	r = sum.a;
	s = tmp.a;
	while(p -> next != NULL)
		p = p-> next;
	while( q -> next != NULL)
		q = q-> next;
	while( r -> next != NULL)
		r = r-> next;
	while( s-> next != NULL)
		s = s-> next;
	bignum num1_1,num2_1;
	init(&num1_1);
	init(&num2_1);
	if(num1.f_enable == '1' &&  num2.f_enable == '1') {
		num1_1 = concatenate(num1);
		num2_1 = concatenate(num2);
		bignum res;
		int float_pt;
		init(&res);
		float_pt = num1.flen + num2.flen;
		res = multiply_bignum(num1_1,num2_1);
		res = split_bignum(res,float_pt,res.len);
		if((num1.sign == NEGATIVE && num2.sign == POSITIVE) || (num2.sign == NEGATIVE && num1.sign == POSITIVE))
			res.sign = NEGATIVE;
		return res;
	}
	else if(num1.f_enable == '1') {
		num1_1 = concatenate(num1);
		bignum res;
		int float_pt;
		init(&res);
		float_pt = num1.flen;
		res = multiply_bignum(num1_1,num2);
	
		return split_bignum(res,float_pt,res.len);

	}
	else if(num2.f_enable == '1') {
		num2_1 = concatenate(num2);
		bignum res;
		int float_pt;
		init(&res);
		float_pt = num2.flen;
		res = multiply_bignum(num1,num2_1);
		return split_bignum(res,float_pt,res.len);

	}
	else {	

		int a;

		for( i=0; i< num2.len; i++) {
				a = q -> whole - '0';	
				for(j = 0; j < a; j++) {
					tmp = add_bignum(num1,tmp);
				}
				sum = add_bignum(sum,leftshift(tmp,i));
		
				if(q != NULL)
					q = q -> prev;
			while((tmp.a -> next != NULL)) {
				tmp.a -> whole = '0';
				tmp.a = tmp.a -> next;
			}
			tmp.a -> whole = '0';
			
		}
		
		return sum;
	}
}





int subtract_num(num *p, num *q, num *r,int borrow) {
	int buf;
	int p1, q1;	
	while(q != NULL) {
		p1 = p -> whole - '0';
		q1 = q -> whole - '0';
	
			if(borrow == 1) {
				q1 = q1 + 1 ;
				borrow = 0;
			}
			if( p1 >= q1 ) {
				r -> whole = (p1 - q1) + '0';
				borrow = 0;
			}
			else if(q1 > p1) {
				r -> whole = ( 10 + p1 - q1) + '0';
				borrow = 1;
			}


			p = p -> prev;
			q = q -> prev;
			r = r -> prev;
		}
		if(borrow != 0) {
			while(p != NULL) {
				if( p -> whole == '0') {
					if( borrow == 1) {
						buf = 10;
						r -> whole = (buf - 1) + '0';
						borrow = 1;
					}
					else { 
						r -> whole = p -> whole;
						borrow = 0;
					}
				}
				else {
					if( borrow == 1) {
						r -> whole = ((p -> whole - '0') - 1) + '0';
						borrow = 0;
					}
					else {
						r -> whole = p -> whole;
						borrow = 0;
					}
				}
				p = p -> prev;
				r = r -> prev;
			}

		}
		else {
			while(p!=NULL) {
				r -> whole = p -> whole;
				p = p -> prev;
				r = r -> prev;
			}
		}
	return borrow;
}

int subtract_fnum(fnum *p, fnum *q, fnum *r, int borrow) {
	int  buf,q1,p1;	
	while(q != NULL) {
			if(p != NULL && q != NULL) {
				p1 = p -> frac - '0';
				q1 = q -> frac - '0';
			}
	
			if(borrow == 1) {
				q1 = q1 + 1 ;
				borrow = 0;
			}
			if( p1 >= q1 ) {
				r -> frac = (p1 - q1) + '0';
				borrow = 0;
			}
			else if(q1 > p1) {
				r -> frac = ( 10 + p1 - q1) + '0';
				borrow = 1;
			}


			p = p -> prev;
			q = q -> prev;
			r = r -> prev;	
		}
		if(borrow != 0) {
			while(p != NULL) {
				if( p -> frac == '0') {
					if( borrow == 1) {
						buf = 10;
						r -> frac = (buf - 1) + '0';
						borrow = 1;
					}
					else { 
						r -> frac = p -> frac;
						borrow = 0;
					}
				}
				else {
					if( borrow == 1) {
						r -> frac = ((p -> frac - '0') - 1) + '0';
						borrow = 0;
					}
					else {
						r -> frac = p -> frac;
						borrow = 0;
					}
				}
				p = p -> prev;
				r = r -> prev;
			}

		}
		else {
			while(p!=NULL) {
				r -> frac = p -> frac;
				p = p -> prev;
				r = r -> prev;
			}
		}
	return borrow;
}


bignum subtract_bignum(bignum num1, bignum num2) {
	bignum res;
	int i;
	int op1, op2, borrow = 0, sum;
	init(&res);	
	res.len = maxlen(num1,num2,'1')+1;
	res.flen =maxlen(num1,num2,'0');
	num *p, *q, *r;
	fnum *p1, *q1, *r1;
	for( i =0;i < res.len ; i++)  
		res.a = add_digit('0',res.a);
	if(res.flen != 0) {
		res.f_enable = '1';
		for(i = 0; i< res.flen; i++) 
			res.b = add_fdigit('0',res.b);
	}
	while(num1.a -> next != NULL && num1.a -> whole == '0') {
		num1.a = delete_firstnode(num1.a);	
		num1.len -=1;
	}
	while(num2.a -> next != NULL && num2.a -> whole == '0') {
	       num2.a = delete_firstnode(num2.a);	
		num2.len -=1;
	}
	p = num1.a;
	q = num2.a;
	r = res.a;
	p1 = num1.b;
	q1 = num2.b;
	r1 = res.b;
	while(p -> next != NULL)
		p = p-> next;
	while( q -> next != NULL)
		q = q-> next;
	while( r-> next != NULL)
		r = r-> next;

	if(r1!= NULL) {
		while(r1 -> next != NULL)
			r1 = r1 -> next;
	}
	if(num1.sign == POSITIVE && num2.sign == POSITIVE) {
		if(res.f_enable == '1') {
				if(num1.flen >= num2.flen) {
					int i = num1.flen - num2.flen;
					while(i> 0) {
						num2.b = add_fdigit('0',num2.b);
						i--; 
					}
					num2.flen = num1.flen;
					p1 = num1.b;
					q1 = num2.b;
					while(q1 -> next != NULL)
						q1 = q1 -> next;
					while(p1 -> next != NULL)
						p1 = p1 -> next;
					borrow = subtract_fnum(p1,q1,r1,0);
				}
				else {
					num1.f_enable = '1';
					int i = num2.flen - num1.flen;
					while(i> 0) {
						num1.b = add_fdigit('0',num1.b);
						i-- ;
					}
					num1.flen = num2.flen;
					p1 = num1.b;
					q1 = num2.b;
					while(p1 -> next != NULL) {
						p1 = p1 -> next;
					}
					while(q1 -> next != NULL) {
						q1 = q1 -> next;
					}
					borrow = subtract_fnum(p1,q1,r1,0);
				}
			}
		if(num1.len > num2.len) {
			borrow = subtract_num(p,q,r,borrow);
		}
	
		else if ( num2.len > num1.len) {
			res.sign = NEGATIVE;
			borrow = subtract_num(q,p,r,borrow);	
		}
		else {
			int cmp;
			cmp = comparator(num1,num2);
			if(cmp == 0) {
				return res;
			}
			else if(cmp == 1) {
				borrow = subtract_num(p,q,r,borrow);
			}
			else if( cmp == -1) {
				res.sign = NEGATIVE;
				borrow = subtract_num(q,p,r,borrow);

			}
		}

	}
	else if(num1.sign == NEGATIVE  && num2.sign == POSITIVE) {
		num1.sign = POSITIVE;
		res = add_bignum(num1,num2);
		res.sign = NEGATIVE;
	}
	else if(num1.sign == POSITIVE && num2.sign == NEGATIVE) {
		num2.sign = POSITIVE;
		res = add_bignum(num1,num2);
	}
	else if(num1.sign == NEGATIVE && num2.sign == NEGATIVE) {
		num2.sign = POSITIVE;
		num1.sign = POSITIVE;
		res = subtract_bignum(num2,num1);
	}

	return res;


}
int add_num(num *p, num *q, num *r,int carry) {
	int op1,op2,sum;
	int u,l;
		while(q!= NULL && p != NULL) {
				op1 = p -> whole-'0';
				op2 = q -> whole-'0';		
				sum = op1 + op2 + carry;
				r -> whole =(sum % 10) + '0';
				carry = sum /10;
				if( p != NULL)
					p = p -> prev;
				if(q != NULL)
					q = q -> prev;
				r = r -> prev;
			}
			if(carry != 0) {
				if(p == NULL) {
					r -> whole = carry +'0';
				}
				else {
					while(p!= NULL) {
						sum = carry + (p -> whole - '0');
						r -> whole = (sum %10) + '0';
						carry = sum /10;
						p = p -> prev;
						r = r -> prev;
					}
					if(carry!=0) {
						r -> whole = carry +'0';
					}
				}
			}
			else {
				if( p != NULL) {

					while(p !=NULL) {
						if( r != NULL && p != NULL)
							r -> whole = p -> whole;
						p = p -> prev;
						if( r != NULL)
							r = r -> prev;
					}
				}
			}

	return carry;


}

int add_fnum(fnum *p, fnum *q, fnum *r,int carry) {
	int op1,op2,sum;
		while(q!= NULL) {
				op1 = p -> frac-'0';
				op2 = q -> frac-'0';		
				sum = op1 + op2 + carry;
				r -> frac =(sum % 10) + '0';
				carry = sum /10;
				p = p -> prev;
				q = q -> prev;
				r = r -> prev;
			}
			if(carry != 0) {
				if(p == NULL) {
					if( r != NULL)
						r -> frac = carry +'0';
					else
						return carry;
				}
				else {
					while(p!= NULL) {
						sum = carry + (p -> frac - '0');
						r -> frac = (sum %10) + '0';
						carry = sum /10;
						p = p -> prev;
						r = r -> prev;
					}
					if(carry!=0) {
						if(r != NULL)
							r -> frac = carry +'0';
						else 
							return carry;
					}
				}
			}

			else {
				if( p != NULL) {
					while(p !=NULL) {
						r -> frac = p -> frac;
						p = p -> prev;
						r = r -> prev;
					}
				}
			}

	return carry;


}



bignum add_bignum(bignum num1, bignum num2) {
	bignum res;
	int i;
	int op1, op2, carry = 0, sum;
	init(&res);
	res.len = maxlen(num1,num2,'1')+1;
	res.flen =maxlen(num1,num2,'0');
	num *p, *q, *r;
	fnum *p1, *q1, *r1;
	for( i =0;i < res.len ; i++)  
		res.a = add_digit('0',res.a);
	if(res.flen != 0) {
		res.f_enable = '1';
		for(i = 0; i< res.flen; i++) 
			res.b = add_fdigit('0',res.b);
	}
	p = num1.a;
	q = num2.a;
	r = res.a;
	p1 = num1.b;
	q1 = num2.b;
	r1 = res.b;
	if( p != NULL) {
		while(p -> next != NULL)
			p = p-> next;
	}
	if(q != NULL) {	
		while( q -> next != NULL)
			q = q-> next;
	}
	if(r != NULL) {
		while( r-> next != NULL)
			r = r-> next;
	}
	if(p1!=NULL) {
		while(p1 -> next != NULL)
			p1 = p1 -> next;
	}
	if(q1!=NULL) {
		while(q1 -> next != NULL)
			q1 = q1 -> next;
	}
	if(r1!= NULL) {
		while(r1 -> next != NULL)
			r1 = r1 -> next;

	}
	if(num1.sign == POSITIVE && num2.sign == POSITIVE) {
		if(res.f_enable == '1') {
			if(num1.flen >= num2.flen) {
				int i = num1.flen - num2.flen;
				while(i> 0) {
					q1 = add_fdigit('0',q1);
					i--; 
				}
				num2.flen = num1.flen;
				while(q1 -> next != NULL)
					q1 = q1 -> next;
				carry = add_fnum(p1,q1,r1,0);
			}
			else {
				int i = num2.flen - num1.flen;
				while(i> 0) {
					p1 = add_fdigit('0',p1);
					i-- ;
				}
				num1.flen = num2.flen;
				while(p1 -> next != NULL)
					p1 = p1 -> next;
				carry = add_fnum(q1,p1,r1,0);
			}
		}
		if(num1.len >= num2.len) {
			carry = add_num(p,q,r,carry);
		
		}
		else {
			carry = add_num(q,p,r,carry);

		}
	}
	else if ( num1.sign == NEGATIVE && num1.sign == NEGATIVE) {
		res.sign = NEGATIVE;
		if(res.f_enable == '1') {
			if(num1.flen >= num2.flen) {
				int i = num1.flen - num2.flen;
				while(i> 0) {
					q1 = add_fdigit('0',q1);
					i--; 
				}
				num2.flen = num1.flen;
				while(q1 -> next != NULL)
					q1 = q1 -> next;
				carry = add_fnum(p1,q1,r1,0);
			}
			else {
				int i = num2.flen - num1.flen;
				while(i> 0) {
					p1 = add_fdigit('0',p1);
					i-- ;
				}
				num1.flen = num2.flen;
				while(p1 -> next != NULL)
					p1 = p1 -> next;
				carry = add_fnum(q1,p1,r1,0);
			}
		}
		if(num1.len >= num2.len) {
			carry = add_num(p,q,r,carry);
		
		}
		else {
			carry = add_num(q,p,r,carry);

		}
	}
	else if(num1.sign == NEGATIVE || num2.sign == NEGATIVE) {
		res = subtract_bignum(num1,num2);
	}	
	return res;

}



