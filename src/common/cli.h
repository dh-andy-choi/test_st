#ifndef CLI_H_
#define CLI_H_

#include "def.h"

#define CLI_MAX_CMD_STR    16
#define CLI_MAX_ARGS       8

typedef struct {
  char   cmd_str[CLI_MAX_CMD_STR];
  void (*cmd_func)(uint8_t argc, char **argv);
} cli_cmd_t;

void cliInit(void);
bool cliOpen(uint8_t ch, uint32_t baud);
bool cliMain(void);
void cliPrintf(const char *fmt, ...);
bool cliAdd(const char *cmd_str, void (*p_func)(uint8_t argc, char **argv));

#endif /* CLI_H_ */
