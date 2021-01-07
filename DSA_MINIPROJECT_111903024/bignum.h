#ifndef BIGNUM_H
#define BIGNUM_H
typedef struct num {
	char whole;
	struct num *next;
	struct num *prev;
}num;

typedef struct fnum {
	char frac;
	struct fnum *next;
	struct fnum *prev;
}fnum;

typedef struct bignum {
	num *a;
	fnum *b;
	char sign;
	char f_enable;
	int len;
	int flen;
}bignum;


num * add_digit(char digit, num *head);

fnum * add_fdigit(char digit, fnum *head);

void print_num(bignum num, int scale);

int maxlen(bignum num1, bignum num2, char a);

int comparator(bignum p, bignum q);

bignum concatenate(bignum num1);

void init(bignum *n1);

bignum split_bignum(bignum n1, int a, int total);

num * delete_firstnode(num *head);

void delete_bignum(bignum n);

int is_bignum_zero(bignum n1);

#endif
