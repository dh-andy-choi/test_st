#ifndef BSP_H_
#define BSP_H_

#include "def.h"

void bspInit(void);
void bspDeInit(void);

void delay(uint32_t ms);
uint32_t millis(void);

#endif /* BSP_H_ */
