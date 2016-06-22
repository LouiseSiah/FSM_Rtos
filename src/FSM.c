#include "FSM.h"

void buttonAndLed(TaskState *ts)
{
  int currentTime;
  // int buttonHasReleased;
  
  switch(ts->state)
  {
    case RELEASED:
      if(getButton(ts->whichButton) == IS_PRESSED)
      {
        turnLED(ts->whichLED, LED_ON);
        ts->recordedTime = getTime();
        ts->state = PRESSED_ON;
        ts->buttonHasReleased = 0;
      }
      break;
    case PRESSED_ON:
      if(getButton(ts->whichButton) == IS_PRESSED)
      {
        if(ts->buttonHasReleased)
        {
          ts->state = TURNING_OFF;
          turnLED(ts->whichLED, LED_OFF);
          break;
        }
      }
      else // released button
      {
        ts->state = PRESSED_ON;
        ts->buttonHasReleased = 1;
      }
        
      currentTime = getTime();
      if(currentTime - (ts->recordedTime) < ts->interval)
        break;

      ts->recordedTime = getTime();
      turnLED(ts->whichLED, LED_OFF);
      ts->state = PRESSED_OFF;
      break;
    
    case PRESSED_OFF:
      if(getButton(ts->whichButton) == IS_PRESSED)
      {
        if(ts->buttonHasReleased)
        {
          ts->state = TURNING_OFF;
          turnLED(ts->whichLED, LED_OFF);
          break;
        }
      }
      else // released button
      {
        ts->state = PRESSED_OFF;
        ts->buttonHasReleased = 1;
      }
      
      currentTime = getTime();
      if(currentTime - (ts->recordedTime) < ts->interval)
        break;
      
      ts->recordedTime = getTime();
      turnLED(ts->whichLED, LED_ON);
      ts->state = PRESSED_ON;
      break;
    
    case TURNING_OFF:
      if(getButton(ts->whichButton) == IS_RELEASED)
        ts->state = RELEASED;
      break;
      
    default:
      turnLED(ts->whichLED, LED_OFF);
      ts->state = RELEASED;
      break;
        
  }
}
