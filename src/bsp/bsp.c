#include "bsp.h"

void bspInit(void) {
  // HAL already initialized in main.c
}

void bspDeInit(void) {
}

void delay(uint32_t ms) {
  HAL_Delay(ms);
}

uint32_t millis(void) {
  return HAL_GetTick();
}
