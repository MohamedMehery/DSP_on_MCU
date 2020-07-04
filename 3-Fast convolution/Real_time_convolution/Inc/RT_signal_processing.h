#ifndef RT_SIGNAL_PROCESSING
#define RT_SIGNAL_PROCESSING

#include "main.h"
extern float   signal32_64_buffer[64];
extern int32_t filter32_64_buffer[64];
extern DMA_HandleTypeDef hdma_memtomem_dma1_channel1;


void fill_signal_buffer(float * signal_sample);
void fill_filter_buffer(uint32_t * filter_sample);
void Fast_convolution(float * signal_sample,uint32_t * filter_arr , complex * output);
void slow_convolution(const	float * signal_arr,const  int32_t * impulse_response_arr , float * result 
						, unsigned int signal_size , unsigned int impulse_size );
#endif
