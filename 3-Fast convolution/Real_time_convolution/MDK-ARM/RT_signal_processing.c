#include "RT_signal_processing.h"

void fill_signal_buffer(float * signal_sample)
{
	int i ;
	/* transfer signal 32 point sample to buffer */
	HAL_DMA_Start(&hdma_memtomem_dma1_channel1 , (uint32_t)&signal_sample[0] ,  (uint32_t)&signal32_64_buffer[0] , 32);
	/* perform zero padding*/
	for( i = 32 ; i < 64 ; i++)
	{
		signal32_64_buffer[i] = 0;	
	}
	
}
void fill_filter_buffer(uint32_t * filter_sample)
{
	int i ;
	/* transfer signal 32 point sample to buffer */
	HAL_DMA_Start(&hdma_memtomem_dma1_channel1 , (uint32_t)&filter_sample[0] ,  (uint32_t)&filter32_64_buffer[0] , 32);
	/* perform zero padding*/
	for( i = 32 ; i < 64 ; i++)
	{
		filter32_64_buffer[i] = 0;	
	}
	
}
