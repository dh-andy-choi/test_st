#include "qbuffer.h"

void qbufferInit(void) {
}

bool qbufferCreate(qbuffer_t *p_node, uint8_t *p_buf, uint32_t len) {
  p_node->in = 0;
  p_node->out = 0;
  p_node->len = len;
  p_node->p_buf = p_buf;
  return true;
}

bool qbufferWrite(qbuffer_t *p_node, uint8_t *p_buf, uint32_t len) {
  bool ret = true;
  uint32_t next_in;

  for (uint32_t i=0; i<len; i++) {
    next_in = (p_node->in + 1) % p_node->len;
    if (next_in != p_node->out) {
      p_node->p_buf[p_node->in] = p_buf[i];
      p_node->in = next_in;
    } else {
      ret = false;
      break;
    }
  }
  return ret;
}

bool qbufferRead(qbuffer_t *p_node, uint8_t *p_buf, uint32_t len) {
  bool ret = true;

  for (uint32_t i=0; i<len; i++) {
    if (p_node->p_buf != NULL && p_node->in != p_node->out) {
      p_buf[i] = p_node->p_buf[p_node->out];
      p_node->out = (p_node->out + 1) % p_node->len;
    } else {
      ret = false;
      break;
    }
  }
  return ret;
}

uint32_t qbufferAvailable(qbuffer_t *p_node) {
  return (p_node->in - p_node->out + p_node->len) % p_node->len;
}

void qbufferFlush(qbuffer_t *p_node) {
  p_node->in = 0;
  p_node->out = 0;
}
