#ifndef GetSignal_H
#define GetSignal_H
#include <stdint.h>
#include <stdio.h>

typedef enum
{
  IS_PRESSED,
  IS_RELEASED,
}ButtonStatus;

typedef enum
{
  LED_ON,
  LED_OFF,
}OnOffLED;

typedef enum
{
  LED_A,
  LED_B,
}WhichLED;

typedef enum
{
  BUTTON_A,
  BUTTON_B,
}WhichButton;

int getButton(WhichButton whichButton);
int getTime();
void turnLED(WhichLED whichLED, OnOffLED onOff);
#endif // GetSignal_H
