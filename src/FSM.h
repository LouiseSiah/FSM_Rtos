#ifndef FSM_H
#define FSM_H

#include "GetSignal.h"

typedef enum
{
  RELEASED,
  PRESSED_ON,
  PRESSED_OFF,
  // RELEASED_ON,
  // RELEASED_OFF,
  TURNING_OFF,
}FsmState;

typedef struct
{
  FsmState state;
  unsigned int recordedTime;
  int interval;
  WhichLED whichLED;
  WhichButton whichButton;
  int buttonHasReleased;
}TaskState;

void button(TaskState *ts);
#endif // FSM_H
