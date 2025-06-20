#ifndef SERVO_H
#define SERVO_H
#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
#include "../config.h"

/* Function Declarations */
void Servo_init(void);
void TaskServo(void);

#ifdef __cplusplus
}
#endif
#endif  //SERVO_H