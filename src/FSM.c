#include "FSM.h"

void buttonAndLed(TaskState *ts)
{
  switch(ts->state)
  {
    case RELEASED:
      if(getButton(ts->whichButton) == IS_PRESSED)
      {
        turnLED(ts->whichLED, LED_ON);
        ts->recordedTime = getTime();
        ts->state = PRESSED_ON;
      }
      break;
    case PRESSED_ON:
      printf("what?");
      if(getButton(ts->whichButton) == IS_PRESSED)
      {
        do
        {
          ts->interval = getTime() - ts->recordedTime;
        }while(ts->interval < 0.25);
        ts->recordedTime = getTime();
        turnLED(ts->whichLED, LED_OFF);
        ts->state = PRESSED_OFF;
      }
      else // IS_RELEASED
      {
        ts->state = RELEASED_ON;
      }
      break; 
    case PRESSED_OFF:
      if(getButton(ts->whichButton) == IS_PRESSED)
      {
        do
        {
          ts->interval = getTime() - ts->recordedTime;
        }while(ts->interval < 0.25);
        ts->recordedTime = getTime();
        turnLED(ts->whichLED, LED_ON);
        ts->state = PRESSED_ON;
      }
      else // IS_RELEASED
      {
        ts->state = RELEASED_OFF;
      }
      break;
    case RELEASED_ON:
      if(getButton(ts->whichButton) == IS_RELEASED)
      {
        do
        {
          ts->interval = getTime() - ts->recordedTime;
        }while(ts->interval < 0.25);
        ts->recordedTime = getTime();
        turnLED(ts->whichLED, LED_OFF);
        ts->state = RELEASED_OFF;
      }
      else // IS_PRESSED
      {
        ts->state = TURNING_OFF;
      }
      break; 
    case RELEASED_OFF:
      if(getButton(ts->whichButton) == IS_RELEASED)
      {
        do
        {
          ts->interval = getTime() - ts->recordedTime;
        }while(ts->interval < 0.25);
        ts->recordedTime = getTime();
        turnLED(ts->whichLED, LED_ON);
        ts->state = RELEASED_ON;
      }
      else // IS_PRESSED
      {
        ts->state = TURNING_OFF;
      }
      break;
    case TURNING_OFF:
      if(getButton(ts->whichButton) == IS_RELEASED)
        ts->state = RELEASED;
      break;
    default:
      printf("Throw Error");
        
  }
}
