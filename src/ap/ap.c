#include "ap.h"

void apInit(void) {
  hwInit();
  uartOpen(0, 115200);
}

void apMain(void) {
  while (1) {
  }
}
