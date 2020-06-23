#ifndef _MOVING_AVG_H_
#define _MOVING_AVG_H_
#include "signal.h"
#include "stm32f10x.h"

void moving_avg_filter(const float * signal , uint32_t length , uint32_t npts , float *result);
void recursiong_moving_avg(const float * signal , uint32_t length , uint32_t npts , float *result);



#endif
