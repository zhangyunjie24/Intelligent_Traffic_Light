#ifndef __SEG_7_H__
#define __SEG_7_H__
#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
#include <stdint.h>
#include "../config.h"

/* Function Declarations */
void Seg7_init(const uint8_t* pins);
void Seg7_show(uint8_t num);
void TaskSeg(void);

#ifdef __cplusplus
}
#endif
#endif  /* #ifndef __SEG_7_H__ */