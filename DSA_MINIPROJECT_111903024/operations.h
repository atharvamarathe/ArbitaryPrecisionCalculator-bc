#ifndef OPERATIONS_H
#define OPERATIONS_H

/*
 * Corresponding header file for the arithmatic operations on bignum data type
 *
 *
 */


bignum leftshift(bignum num, int n);

bignum multiply_bignum(bignum num1, bignum num2);

int subtract_num(num *p, num *q, num *r,int borrow);

int subtract_fnum(fnum *p, fnum *q, fnum *r, int borrow);

bignum subtract_bignum(bignum num1, bignum num2);

int add_num(num *p, num *q, num *r,int carry);

int add_fnum(fnum *p, fnum *q, fnum *r,int carry);

bignum add_bignum(bignum num1, bignum num2);

bignum divide_bignum(bignum num1, bignum num2,int scale);

#endif

