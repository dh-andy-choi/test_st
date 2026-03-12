#include "hw.h"

void hwInit(void) {
  bspInit();
  
  qbufferInit();
  uartInit();
}
