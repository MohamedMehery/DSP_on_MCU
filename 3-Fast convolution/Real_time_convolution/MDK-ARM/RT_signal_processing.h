#ifndef RT_SIGNAL_PROCESSING
#define RT_SIGNAL_PROCESSING

#include "main.h"
#include <math.h>


extern DMA_HandleTypeDef hdma_memtomem_dma1_channel1;

extern float current_value ;
extern float buffer_current_value;

void fill_signal_buffer(float * signal_sample);
void fill_filter_buffer(float * filter_sample);
void Fast_convolution(float * signal_sample,float * filter_arr , complex * output);
void slow_convolution(const	float * signal_arr,const  int32_t * impulse_response_arr , float * result 
						, unsigned int signal_size , unsigned int impulse_size );
int Decimation(int num , int size);
#endif
