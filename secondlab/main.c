#include "stm32f10x.h"                  // Device header
#include "signals.h"
#include "fft.h"

#define N 64

extern const int32_t lowpassfilter[wavesignal_size];
extern const float inputSignal_f32_1kHz_15kHz[wavesignal_size];
void fftconv(const real* signal , uint32_t signalsize , const int32_t *filter ,float* output);

static float FFTcurrent_value_v = 0;
static float FFTcurrent_value_v1 = 0;
static float IFFTcurrent_value_v = 0;
static float IFFTcurrent_value_v1 = 0;
static float current_value_v = 0;
static float current_value_v1 = 0;

int main()
{

    int k;complex v[N], v1[N], scratch[N];

    /* Fill v[] with a function of known FFT: */
    for(k=1; k<=N; k++) {
      v[k].Re = 125*cos(2*PI*k/(double)N);
      v[k].Im = -125*sin(2*PI*k/(double)N);
      v1[k].Re =  300*cos(2*PI*k/(double)N);
      v1[k].Im = -300*sin(2*PI*k/(double)N);
    }
			for(k = 1 ; k <= N ; k++)
			{
				current_value_v = v[k].Re;
			}
			current_value_v = 0;
			for(k = 1 ; k <= N ; k++)
			{
				current_value_v1 = v1[k].Re;
			}
			current_value_v1 = 0;
			
      /* FFT, iFFT of v[]: */
      fft( v, N, scratch ); 
			for(k = 1 ; k <= N ; k++){FFTcurrent_value_v = v[k].Re;}
			FFTcurrent_value_v = 0;
      ifft( v, N, scratch );
			for(k = 1 ; k <= N ; k++){IFFTcurrent_value_v = v[k].Re;}
			FFTcurrent_value_v1 = 0;
			
      /* FFT, iFFT of v1[]: */
      fft( v1, N, scratch );
			for(k = 1 ; k <= N ; k++){IFFTcurrent_value_v1 = v1[k].Re;}			
			IFFTcurrent_value_v = 0;
      ifft( v1, N, scratch );
			for(k = 1 ; k <= N ; k++){IFFTcurrent_value_v1 = v1[k].Re;}
			IFFTcurrent_value_v1 = 0;


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