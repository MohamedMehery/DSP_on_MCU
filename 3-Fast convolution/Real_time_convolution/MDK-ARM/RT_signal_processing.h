#ifndef RT_SIGNAL_PROCESSING
#define RT_SIGNAL_PROCESSING

#include "main.h"
extern float   signal32_64_buffer[64];
extern int32_t filter32_64_buffer[64];
extern DMA_HandleTypeDef hdma_memtomem_dma1_channel1;

/**
* @brief this function fill the signal32_64buffer and badding 32 zeros in array.
*	@param pointer to first word in signal array.
*	@retval None.
*/
void fill_signal_buffer(float * signal_sample);
void fill_filter_buffer(uint32_t * filter_sample);

#endif
