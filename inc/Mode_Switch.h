#ifndef MODE_SWITCH_H
#define MODE_SWITCH_H
#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
#include "../config.h"

/* Function Declarations */
void Mode_Switch_init(void);
void TaskDayNight(void);
void TaskAccidentCheck(void);

#ifdef __cplusplus
}
#endif
#endif  //MODE_SWITCH_H