#include "stm32f10x.h"                  // Device header
#include "signals.h"
#include "fft.h"

#define N 64
#define LOOP_Cycle (wavesignal_size/N)

extern const int32_t lowpassfilter[lpsize];
extern const float inputSignal_f32_1kHz_15kHz[wavesignal_size];
void fftconv(const real* signal , uint32_t signalsize , const int32_t *filter ,float* output);

static float FFTcurrent_value_v = 0;
static float FFTcurrent_value_v1 = 0;
static float IFFTcurrent_value_v = 0;
static float IFFTcurrent_value_v1 = 0;
static float current_value_v = 0;
static float current_value_v1 = 0;
static float excution_flag = 0;

int main()
{

			int i,k;
			complex v[N], v1[N], scratch[N];
			
			/* Fill v[] with a function of known FFT: */
/*		for(k=0; k<N; k++) {
			
      v[k].Re = 125*cos(2*PI*k/(double)N);
      v[k].Im = -125*sin(2*PI*k/(double)N);
      v1[k].Re =  300*cos(2*PI*k/(double)N);
      v1[k].Im = -300*sin(2*PI*k/(double)N);
			}*/
	
			/** @brief fill signal with the values of square signal*/

				for(k=0; k< N; k++) {
					v[k].Re = 0;
					v[k].Im = 0;
					
					if((k < (N/2 - N/4)) )
					{
						v[k].Re = 1 ;
					}				
				}

				
				/**@brief this loop display the v.Re on logic analyzer */
				for(k = 0 ; k < N ; k++)
				{
					current_value_v = v[k].Re;
				}
				current_value_v = 0;
				
				/**@brief this perofm an FFT or DFT */	
				excution_flag = 1;
				fft( v, N, scratch ); 
				excution_flag = 0;
				excution_flag = 1;
				dft( v ); 
				excution_flag = 0;
				
				/**@brief this loop display the fft of v on logic analyzer*/			
				for(k = 0 ; k < N ; k++)
				{
					FFTcurrent_value_v = v[k].Re;
				}
				FFTcurrent_value_v = 0;


				/**@brief this perofm an Ifft */						
				ifft( v, N, scratch ); 
				
				/**@brief this loop display the ifft of v on logic analyzer*/							
				for(k = 0 ; k < N ; k++)
				{
					IFFTcurrent_value_v = v[k].Re;
				}
				IFFTcurrent_value_v = 0;		

				
			/**@brief this big loop perform fft and ifft on long signals*/

			for( i = 0 ; i < LOOP_Cycle ; i++) 
			{
				
				/**@brief this loop copy the inputSignal_f32_1kHz_15kHz into the real part of v struct*/
				
				for(k=0; k<N; k++) {	
					//filling signal with a sin wave

					v[k].Re = inputSignal_f32_1kHz_15kHz[(i*N) + k];
					v[k].Im = 0;
					scratch[k].Re = 0;
					scratch[k].Im = 0;
				}
				
				/**@brief this loop display the v.Re on logic analyzer */
				for(k = 0 ; k < N ; k++)
				{
					current_value_v = v[k].Re;
				}
				current_value_v = 0;
				
				/**@brief this perofm an fft */			
				fft( v, N, scratch ); 
				
				/**@brief this loop display the fft of v on logic analyzer*/			
				for(k = 0 ; k < N ; k++)
				{
					FFTcurrent_value_v = v[k].Re;
				}
				FFTcurrent_value_v = 0;


				/**@brief this perofm an Ifft */						
				ifft( v, N, scratch ); 
				
				/**@brief this loop display the ifft of v on logic analyzer*/							
				for(k = 0 ; k < N ; k++)
				{
					IFFTcurrent_value_v = v[k].Re;
				}
				IFFTcurrent_value_v = 0;		

				
				/** @brief this loop reset the v and scratch */
				for(k = 0 ; k<N ; k++)
				{
					v[k].Re = 0;
					scratch[k].Re = 0;
					v[k].Im = 0;
					scratch[k].Im = 0;					
				}
		}
			

//			for(k = 0 ; k < N ; k++)
//			{
//				current_value_v1 = v1[k].Re;
//			}
//			current_value_v1 = 0;
			
			
		

			
//      /* FFT, iFFT of v1[]: */
//      fft( v1, N, scratch );
//			for(k = 0 ; k < N ; k++){FFTcurrent_value_v1 = v1[k].Re;}			
//			FFTcurrent_value_v1 = 0;
//      ifft( v1, N, scratch );
//			for(k = 0 ; k < N ; k++){IFFTcurrent_value_v1 = v1[k].Re;}
//			IFFTcurrent_value_v1 = 0;


	while(1)
	{		
	}	
	return 0;
}
/*

void fftconv( const real* signal , uint32_t signalsize ,const int32_t *filter ,float* output)
{
	int i;
	complex sig[signalsize];
	complex filt[signalsize];
	complex temp[signalsize];
	
	for(i = 0 ; i < signalsize ; i++)
	{
		sig[i].Re = signal[i];
		filt[i].Re = filter[i];
	}
	
	fft(sig,signalsize,temp);
	fft(filt,signalsize,temp);
	for(i = 0 ; i < signalsize ; i++)
	{
		temp[i].Re = sig[i].Re * filt[i].Re;
		temp[i].Im = sig[i].Im * filt[i].Im;
	}
	ifft(temp,signalsize,sig);
	for(i = 0 ; i < signalsize ; i++)
	{
		output[i] = sqrt(temp[i].Re * temp[i].Re + temp[i].Im * temp[i].Im);
	}
	
		
}*/