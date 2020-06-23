#ifndef __FFT_H 
#define __FFT_H
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


#ifndef PI
# define PI	3.14159265358979323846264338327950288
#endif
typedef float real;
typedef struct{real Re; real Im;} complex;

 void print_vector(
	     const char *title,
	     complex *x,
	     int n);
 void fft( complex *v, int n, complex *tmp );
 void ifft( complex *v, int n, complex *tmp );

#endif 
