#ifndef UART_H_
#define UART_H_

#include "hw_def.h"

#define UART_MAX_CH     _HW_DEF_UART_CH_MAX

bool     uartInit(void);
bool     uartOpen(uint8_t ch, uint32_t baud);
uint32_t uartAvailable(uint8_t ch);
uint8_t  uartRead(uint8_t ch);
uint32_t uartWrite(uint8_t ch, uint8_t *p_data, uint32_t len);
uint32_t uartPrintf(uint8_t ch, char *fmt, ...);

#endif /* UART_H_ */
