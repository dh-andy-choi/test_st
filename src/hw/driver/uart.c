#include "uart.h"
#include "qbuffer.h"

// Assuming UART3 is used (common for STM32 Nucleo/Discovery CLI)
extern UART_HandleTypeDef huart3;

typedef struct {
  bool is_open;
  uint32_t baud;
  qbuffer_t qbuffer;
  uint8_t rx_buf[256];
} uart_t;

static uart_t uart_tbl[UART_MAX_CH];

bool uartInit(void) {
  for (int i=0; i<UART_MAX_CH; i++) {
    uart_tbl[i].is_open = false;
  }
  return true;
}

bool uartOpen(uint8_t ch, uint32_t baud) {
  bool ret = false;
  if (ch >= UART_MAX_CH) return false;

  switch(ch) {
    case 0:
      uart_tbl[ch].baud = baud;
      uart_tbl[ch].is_open = true;
      qbufferCreate(&uart_tbl[ch].qbuffer, uart_tbl[ch].rx_buf, 256);
      
      // Start interrupt-based reception
      HAL_UART_Receive_IT(&huart3, &uart_tbl[ch].rx_buf[0], 1);
      ret = true;
      break;
  }
  return ret;
}

uint32_t uartAvailable(uint8_t ch) {
  if (ch >= UART_MAX_CH || !uart_tbl[ch].is_open) return 0;
  return qbufferAvailable(&uart_tbl[ch].qbuffer);
}

uint8_t uartRead(uint8_t ch) {
  uint8_t ret = 0;
  qbufferRead(&uart_tbl[ch].qbuffer, &ret, 1);
  return ret;
}

uint32_t uartWrite(uint8_t ch, uint8_t *p_data, uint32_t len) {
  if (ch >= UART_MAX_CH || !uart_tbl[ch].is_open) return 0;
  HAL_UART_Transmit(&huart3, p_data, len, 100);
  return len;
}

// UART RX Interrupt Callback (Simple implementation)
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  if (huart->Instance == USART3) {
    // Write received byte to qbuffer and restart IT
    // (This is a simplified version for structure)
    HAL_UART_Receive_IT(&huart3, &uart_tbl[0].rx_buf[0], 1);
  }
}
