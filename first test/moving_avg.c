#include "moving_avg.h"
/*
Blackman window :
	w[i] = 0.42 - 0.5 * cos(2 * pi * i / M) + 0.08 * cos(4 * pi * i / M);
	Hamming window :
	w[i] = 0.54 - 0.46 * cos(2 * pi * i / M)
*/

void moving_avg_filter(const float * signal , uint32_t length , uint32_t npts , float *result)
{
	int i , j;
	for(i = 0 ; i < length - npts - 1 ; i++)
	{
		for(j = 0 ; j < npts ; j++)
		{
			result[i] += signal[i+j];
		}
		result[i] = result[i]/npts;
	}
	for(i = length - npts - 1 ; i < length ; i++)
	{
		for(j = 0 ; j < npts ; j++)
		{
			result[i] += signal[i+j];
		}
		result[i] = result[i]/(npts);
		npts--;
		if(npts == 1)return;
	}
}

void recursiong_moving_avg(const float * signal , uint32_t length , uint32_t npts , float *result)
{
	int i , j ;
	for( j = 0 ; j < npts ; j++)
	{
		result[0] += signal[j];
	}
	for(i = 1 ; i < length ; i++)
	{
			result[i] = result[i - 1] + signal[i+ npts - 1] - signal[i - 1] ;
	}
}
