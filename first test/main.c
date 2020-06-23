#include "stm32f10x.h"                  // Device header
#include "signals.h"
#include "moving_avg.h"

extern const float inputSignal_f32_1kHz_15kHz[wavesignal_size];
extern const int32_t lowpassfilter[lpsize];


/* this is not real time filter */
void convolution(const	float * signal_arr,const  int32_t * impulse_response_arr , float * result 
						, unsigned int signal_size , unsigned int impulse_size );

int main()
{
		static float current_value = 0 ;	/* this variable must be static to get view on logic analyzer */
		static float lpresult_value = 0 ;
		static float moving_avg_result_value = 0 ;
		static float recursion_mov_avg_value = 0 ;
		static int32_t filter_value = 0 ;
	int i = 0;
	
	float lowpass_result[wavesignal_size + lpsize - 1]={0}; 	/* sram is not enough */
//	float moving_avg_result[wavesignal_size]={0};	
//	float recursion_mov_avg_result[wavesignal_size]={0};	
	
	convolution(inputSignal_f32_1kHz_15kHz , lowpassfilter , lowpass_result , wavesignal_size, lpsize);
	
//	moving_avg_filter(inputSignal_f32_1kHz_15kHz, 320 , 15 , moving_avg_result);
//	recursiong_moving_avg(inputSignal_f32_1kHz_15kHz, 320 , 15, recursion_mov_avg_result);	
	while(1)
	{
		/* display original wave and output of moving average filter */
		for( i = 0 ; i < wavesignal_size ; i++)
		{
		current_value = inputSignal_f32_1kHz_15kHz[i];
//		moving_avg_result_value = moving_avg_result[i];
//		recursion_mov_avg_value = 	recursion_mov_avg_result[i];
		}
		
		 /*plot the output of lowpass filter */
		for( i = 0 ; i < wavesignal_size + lpsize - 1 ; i++)
		lpresult_value = lowpass_result[i];	
		/* display the lowpass filter impulse response */
	  for(i = 0 ; i < lpsize ; i++)
		filter_value = lowpassfilter[i];
	}
}


void convolution(const	float * signal_arr,const  int32_t * impulse_response_arr , float * result 
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
