#include "FSM.h"

void buttonAndLed(TaskState *ts)
{
  int currentTime;
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
      if(getButton(ts->whichButton) == IS_PRESSED)
      {
        do
        {
          currentTime = getTime();
        }while(currentTime - (ts->recordedTime) < ts->interval);
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
          currentTime = getTime();
        }while(currentTime - (ts->recordedTime) < ts->interval);
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
          currentTime = getTime();
        }while(currentTime - (ts->recordedTime) < ts->interval);
        ts->recordedTime = getTime();
        ts->state = RELEASED_OFF;
      }
      else // IS_PRESSED
      {
        ts->state = TURNING_OFF;
      }
      turnLED(ts->whichLED, LED_OFF);
      break; 
    case RELEASED_OFF:
      if(getButton(ts->whichButton) == IS_RELEASED)
      {
        do
        {
          currentTime = getTime();
        }while(currentTime - (ts->recordedTime) < ts->interval);
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
      ts->state = RELEASED;
        
  }
}
