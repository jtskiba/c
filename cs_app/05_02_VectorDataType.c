#include <stdio.h>
#include <stdlib.h>

/* for additions */
// #define IDENT 0
// #define OP +

/* for multiplications */

#define IDENT 1
#define OP *


/* Allow for different data type declarations */
typedef double data_t;

/* Create abstract data type for vector */
typedef struct {
	long len;
	data_t *data;
} vec_rec, *vec_ptr;
// /* Alternative version of the struct above */
// struct vector {
	// long len;
	// data_t *data;
// };
// typedef struct vector  vec_rec;
// typedef struct vector* vec_ptr;


/* Create vector of specified length */
vec_ptr new_vec(long len){
	
	/* Allocate header structure */
	vec_ptr result = (vec_ptr) malloc(sizeof(vec_rec));
	data_t *data = NULL;
	
	if (result == NULL) // or if (!result)
		return NULL; /* Could not allocate storage */
	result->len = len;
	
	/* Allocate array */
	if (len > 0){
		data = (data_t *)calloc(len, sizeof(data_t));
		if (!data){
			free((void *) result);
			return NULL; /* Could not allocate storage */
		}
	}
	
	/* Data will either be NULL or allocated array */
	result->data = data;
	return result;
}

/* Retrieve vector element
 * and store it at dest
 * Return 0 (out of bounds) or 1 (successful)
 */
int get_vec_element(vec_ptr v, long index, data_t *dest){
	if (index < 0 || index > v->len)
		return 0;
	*dest = v->data[index];
	return 1;
}

/* Return length of vector */
long vec_length(vec_ptr v){
	return v->len;
}

data_t *get_vec_start(vec_ptr v){
	return v->data;
}

/* Implementation with maximum use of data abstraction */
void combine1(vec_ptr v, data_t *dest){
	long i;
	*dest = IDENT;
	for (i=0; i<vec_length(v); i++){
		data_t val;
		get_vec_element(v, i, &val);
		*dest = *dest OP val;
	}
}

/* Moving function call in for loop's condition check*/  
void combine2(vec_ptr v, data_t *dest){
	long i;
	long length = vec_length(v);
	
	*dest = IDENT;
	for (i=0; i<length; i++){
		data_t val;
		get_vec_element(v, i, &val);
		*dest = *dest OP val;
	}
}

/* Direct access to vector data */
void combine3(vec_ptr v, data_t *dest){
	long i;
	long length = vec_length(v);
	data_t *data = get_vec_start(v); 
	
	*dest = IDENT;
	for (i=0; i<length; i++){
		*dest = *dest OP data[i];
	}
}


/* Accumulate result in temporary */
void combine4(vec_ptr v, data_t *dest){
	long i;
	long length = vec_length(v);
	data_t *data = get_vec_start(v); 
	data_t acc = IDENT; /* temporary acc variable introduced */
	
	for (i=0; i<length; i++){
		acc = acc OP data[i];
	}
	*dest = acc;
}


/* 2x1 loop unrolling */
void combine5(vec_ptr v, data_t *dest){
	long i;
	long length = vec_length(v);
	long limit = length - 1;
	data_t *data = get_vec_start(v); 
	data_t acc = IDENT; /* temporary acc variable introduced */
	
	/* Combine 2 elements in 1 iteration */
	for (i=0; i<limit; i+=2){
		acc = (acc OP data[i]) OP data[i+1];
	}
	
	/* Finish any remaining elements */
	for (; i<length; i++)
		acc = acc OP data[i];
	*dest = acc;
}

/* 5x1 loop unrolling, i.e. k=5 */
/* Problem 5.7 on p.560 of edition 3 */
void combine5b(vec_ptr v, data_t *dest){
	long i, j;
	long k = 5;
	long length = vec_length(v);
	long limit = length - k + 1;
	data_t *data = get_vec_start(v); 
	data_t acc = IDENT; /* temporary acc variable introduced */
	
	/* Combine 5 elements in 1 iteration */
	for (i=0; i<limit; i+=k){
		acc = acc OP data[i] OP data[i+1];
		acc = acc OP data[i+2] OP data[i+3];
		acc = acc OP data[i+4];
	}
	
	/* Finish any remaining elements */
	for (; i<length; i++)
		acc = acc OP data[i];
	*dest = acc;
}

/* 2x2 loop unrolling */
void combine6(vec_ptr v, data_t *dest){
	long i;
	long length = vec_length(v);
	long limit = length - 1;
	data_t *data = get_vec_start(v); 
	data_t acc0 = IDENT; /* temporary acc variable introduced */
	data_t acc1 = IDENT; /* temporary acc variable introduced */
	
	/* Combine 2 elements in 1 iteration */
	for (i=0; i<limit; i+=2){
		acc0 = acc OP data[i];   // even
		acc1 = acc OP data[i+1]; //odd
	}
	
	/* Finish any remaining elements */
	for (; i<length; i++)
		acc0 = acc0 OP data[i];
	
	*dest = acc0 OP acc1;
}

/* 2x1 loop unrolling */
/* or Reassociation Transformation - like combine5, just brackets in one of the lines changed! */
void combine5(vec_ptr v, data_t *dest){
	long i;
	long length = vec_length(v);
	long limit = length - 1;
	data_t *data = get_vec_start(v); 
	data_t acc = IDENT; /* temporary acc variable introduced */
	
	/* Combine 2 elements in 1 iteration */
	for (i=0; i<limit; i+=2){
		acc = acc OP (data[i] OP data[i+1]);
	}
	
	/* Finish any remaining elements */
	for (; i<length; i++)
		acc = acc OP data[i];
	*dest = acc;
}



int main(void){
	
	
	
}


