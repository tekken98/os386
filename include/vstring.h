#ifndef VSTRING_H
#define VSTRING_H
#include "types.h"
#define max(a,b) ((a) > (b) ? (a): (b));
#ifdef __cplusplus
extern "C" {
#endif
void printk(const char * fmt , ...);
void mmemcpy( void * dst, void * src ,uint len);
#ifdef __cplusplus
}
#endif
#endif

