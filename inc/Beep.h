#ifndef BEEP_H
#define BEEP_H
#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
#include "../config.h"

/* Function Declarations */
void Beep_init(void);
void TaskBeep(void);

#ifdef __cplusplus
}
#endif
#endif  //BEEP_H