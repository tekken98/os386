#ifndef M_H
#define M_H
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif
ulong get_free_page(void);
void new_mem_page(uint);
#ifdef __cplusplus
}
#endif
#endif

