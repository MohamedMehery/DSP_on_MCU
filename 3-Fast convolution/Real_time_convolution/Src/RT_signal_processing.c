#include "RT_signal_processing.h"


/**
* @brief this function fill the signal32_64buffer and badding 32 zeros in array.
*	@param pointer to first word in signal array.
*	@retval None.
*/
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

/**
* @brief this function fill the filter32_64buffer and badding 32 zeros in array.
*	@param pointer to first word in filter array.
*	@retval None.
*/
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


/**
* @brief this function perfom fast convoluation between signal and filter
*	@param pointer to first word in signal,filter and output array.
*	@retval None.
*/
void Fast_convolution(float * signal_sample,uint32_t * filter_arr , complex * output)
{
	int i;
	complex filter_sample[64],scratch[64] , original_signal[64];
	fill_signal_buffer(signal_sample);
	fill_filter_buffer(filter_arr);
	for(i = 0 ; i < 64 ; i++)
	{
		original_signal[i].Re = signal32_64_buffer[i];
		filter_sample[i].Re = filter32_64_buffer[i];
	}
	fft(original_signal,64,scratch);
	fft(filter_sample,64,scratch);
	
	for(i = 0 ; i < 64 ; i++)
	{
		
		output[i].Re = original_signal[i].Re * filter_sample[i].Re;
		output[i].Im = original_signal[i].Im * filter_sample[i].Im;
		
	}
}

void slow_convolution(const	float * signal_arr,const  int32_t * impulse_response_arr , float * result 
						, unsigned int signal_size , unsigned int impulse_size )
{
	/* notice -> there is no overlap add or save, so it cannot be applied to large signals */
	/* the overlab method produce the output same size of input */
	int i , j ;

	for( i = 0 ;i < signal_size ; i++)
	{
		for( j = 0 ;j < impulse_size ; j++)
		{
			result[i+j] = result[i+j] + signal_arr[i]*impulse_response_arr[impulse_size - j - 1];
		}
	}
}
