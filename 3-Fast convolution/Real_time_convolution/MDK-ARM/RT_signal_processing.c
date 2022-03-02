#include "RT_signal_processing.h"

 float signal32_64_buffer[64];
 float filter32_64_buffer[64];
 
/**
* @brief this function fill the signal32_64buffer and badding 32 zeros in array.
*	@param pointer to first word in signal array.
*	@retval None.
*/
void fill_signal_buffer(float * signal_sample)
{
	int i ;
	/* transfer signal 32 point sample to buffer */
//	HAL_DMA_Start(&hdma_memtomem_dma1_channel1 , (uint32_t)&signal_sample[0] ,  (uint32_t)&signal32_64_buffer[0] , 32);
//	while(!( DMA1->ISR & (1<<DMA_ISR_GIF1)));  
////	HAL_DMA_PollForTransfer(&hdma_memtomem_dma1_channel1 , HAL_DMA_FULL_TRANSFER , HAL_MAX_DELAY);
//	HAL_DMA_Abort(&hdma_memtomem_dma1_channel1);
	for(i = 0 ; i < 32 ; i++)
	{
		signal32_64_buffer[i] = signal_sample[i];
//		current_value = signal32_64_buffer[i];		
	}
	
	/* perform zero padding*/
	for( i = 32 ; i < 64 ; i++)
	{
		signal32_64_buffer[i] = 0;	
//		current_value = signal32_64_buffer[i];		
	}	
	
}

/**
* @brief this function fill the filter32_64buffer and badding 32 zeros in array.
*	@param pointer to first word in filter array.
*	@retval None.
*/
void fill_filter_buffer(float * filter_sample)
{
	int i ;
	/* transfer signal 32 point sample to buffer */
//	HAL_DMA_Start(&hdma_memtomem_dma1_channel1 , (uint32_t)&filter_sample[0] ,  (uint32_t)&filter32_64_buffer[0] , 32);
//	while(!( DMA1->ISR & (1<<DMA_ISR_GIF1)));
////	HAL_DMA_PollForTransfer(&hdma_memtomem_dma1_channel1 , HAL_DMA_FULL_TRANSFER , HAL_MAX_DELAY);
//	HAL_DMA_Abort(&hdma_memtomem_dma1_channel1);
//	
	for(i = 0 ; i < 32 ; i++)
	{
		filter32_64_buffer[i] = filter_sample[i];
	//	current_value = filter32_64_buffer[i];		
		
	}
	/* perform zero padding*/
	for( i = 32 ; i < 64 ; i++)
	{
		filter32_64_buffer[i] = 0;	
	//	current_value = filter32_64_buffer[i];		

	}

}


/**
* @brief this function perfom fast convoluation between signal and filter
*	@param pointer to first word in signal,filter and output array.
*	@retval None.
*/
void Fast_convolution(float * signal_sample,float * filter_arr , complex * output)
{
	int i,j;double Real_buff , Imag_buff;
	
	complex filter_sample[64],scratch[64] , original_signal[64];
	
	fill_signal_buffer(signal_sample);
	fill_filter_buffer(filter_arr);
	for(i = 0 ; i < 64 ; i++)
	{
		original_signal[i].Re = signal32_64_buffer[i];
		current_value = filter32_64_buffer[i]; 
		filter_sample[i].Re = filter32_64_buffer[i];
		
	}
	current_value = 0;
	fft(original_signal,64,scratch);
	fft(filter_sample,64,scratch);
	
	for( i = 0 ; i < 64 ; i++)
	{
		Real_buff = filter_sample[i].Re * filter_sample[i].Re;
		Imag_buff = filter_sample[i].Im * filter_sample[i].Im;
		
		current_value = (float)sqrt(Real_buff + Imag_buff);				
		
	}	
	current_value = 0;
	
//	for(i = 0 ; i < 64 ; i++)
//	{
//		j = Decimation(i , 64);							// perform anti decimation in time
//		output[j].Re = original_signal[i].Re * filter_sample[i].Re;
//		output[j].Im = original_signal[i].Im * filter_sample[i].Im;
//	}
	ifft(output,64,scratch);
	
	//show the output on the logic analyzer
	for(i = 0 ; i < 64 ; i++)
	{
		buffer_current_value = output[i].Re;
	}	
	
//	for( i = 0 ; i < 64 ; i++)
//	{
//		Real_buff = output[i].Re * output[i].Re;
//		Imag_buff = output[i].Im * output[i].Im;
//		current_value = (float)sqrt(Real_buff + Imag_buff);		
//	}		
}
/**
* @brief this function return the number of most significant '1' 
* @retval this fun return int in range of (0 - 31) represent the most 2's power in input number
*/

int towpownum(int input)
{
    int num = 0;
    for(int i = 0 ; i < 32 ; i++)
    {
        if( (input & (1<<i)))
        {
            num = i;
        }
    }
    return num;
}
/**
* @brief this function perfom a decimation in int number e.g. '000011' it return '110000' 
* @retval this fun return int in range of (0 - siz-1) represent decimation in binary bits
*/
int Decimation( int num , int siz)
{
    int temp = 0;
    int pow2 = towpownum(siz);
    for(int i = 0 ; i < pow2 ; i++)
    {
        if( num & (1<<i))
        {
            temp = temp | (1<<(pow2 - i - 1));
        }
    }
    return temp;
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
		//show the output on the logic analyzer
	for(i = 0 ; i < 64 ; i++)
	{
		buffer_current_value = result[i];
	}	
}
