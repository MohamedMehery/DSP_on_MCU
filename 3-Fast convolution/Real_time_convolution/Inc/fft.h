#ifndef __FFT_H 
#define __FFT_H
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


#ifndef PI
# define PI	3.141592653589793
#endif
typedef float real;
typedef struct{real Re; real Im;} complex;

 void print_vector(
	     const char *title,
	     complex *x,
	     int n);
 void fft( complex *v, int n, complex *tmp );
 void ifft( complex *v, int n, complex *tmp );
 void dft(complex *x );
int check(int n) ;   //checking if the number of element is a power of 2
int log_2(int n)   ; /*function to calculate the log2(.) of int numbers*/

#endif 
