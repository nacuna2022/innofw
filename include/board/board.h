#ifndef __INCLUDE_BOARD_BOARD_H__
#define __INCLUDE_BOARD_BOARD__H__
#include <compiler.h>

unsigned long board_cpu_hz(void);
void early_board_initialize(void);
void initialize_board(void);

#endif /* __INCLUDE_BOARD_BOARD_H__ */

