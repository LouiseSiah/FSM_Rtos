#include "unity.h"
#include "FSM.h"
#include "mock_GetSignal.h"
#include <malloc.h>

void setUp(void){}

void tearDown(void){}

void test_buttonAndLed_given_RELEASED_state_without_pressing_button_should_stay_at_RELEASED(void)
{
  TaskState *ts = malloc(sizeof(TaskState));
  ts->state = RELEASED;
  
  getButton_ExpectAndReturn(ts->whichButton, IS_RELEASED);
  
  buttonAndLed(ts);
  TEST_ASSERT_EQUAL(RELEASED, ts->state);
}

void test_buttonAndLed_given_RELEASED_state_then_press_button_should_change_to_PRESSED_ON(void)
{
  TaskState *ts = malloc(sizeof(TaskState));
  ts->state = RELEASED;
  
  getButton_ExpectAndReturn(ts->whichButton, IS_PRESSED);
  turnLED_Expect(ts->whichLED, LED_ON);
  getTime_ExpectAndReturn(0);
  
  buttonAndLed(ts);
  TEST_ASSERT_EQUAL(PRESSED_ON, ts->state);
}

void test_buttonAndLed_given_PRESSED_ON_state_with_pressing_button_and_timer_not_expired_should_stay_in_PRESSED_ON(void)
{
  TaskState *ts = malloc(sizeof(TaskState));
  ts->state = PRESSED_ON;
  ts->recordedTime = 0;
  ts->interval = 250;
  ts->buttonHasReleased = 0;
  
  getButton_ExpectAndReturn(ts->whichButton, IS_PRESSED);
  getTime_ExpectAndReturn(0);  // for timer not expired yet
  
  buttonAndLed(ts);
  TEST_ASSERT_EQUAL(PRESSED_ON, ts->state);
  TEST_ASSERT_EQUAL(0, ts->buttonHasReleased);
}

void test_buttonAndLed_given_PRESSED_ON_state_with_pressing_button_and_timer_expired_should_change_to_PRESSED_OFF(void)
{
  TaskState *ts = malloc(sizeof(TaskState));
  ts->state = PRESSED_ON;
  ts->recordedTime = 0;
  ts->interval = 250;
  ts->buttonHasReleased = 0;
  
  getButton_ExpectAndReturn(ts->whichButton, IS_PRESSED);
  getTime_ExpectAndReturn(250);
  getTime_ExpectAndReturn(0); // for restat timer , recordedTime = 0
  turnLED_Expect(ts->whichLED, LED_OFF);
  
  buttonAndLed(ts);
  TEST_ASSERT_EQUAL(PRESSED_OFF, ts->state);
  TEST_ASSERT_EQUAL(0, ts->buttonHasReleased);
}

void test_buttonAndLed_given_PRESSED_ON_state_with_released_button_should_stay_in_PRESSED_ON(void)
{
  TaskState *ts = malloc(sizeof(TaskState));
  ts->state = PRESSED_ON;
  ts->recordedTime = 0;
  ts->interval = 250;
  ts->buttonHasReleased = 0;
  
  getButton_ExpectAndReturn(ts->whichButton, IS_RELEASED);
  getTime_ExpectAndReturn(0);  // for timer not expired yet
  
  buttonAndLed(ts);
  TEST_ASSERT_EQUAL(PRESSED_ON, ts->state);
  TEST_ASSERT_EQUAL(1, ts->buttonHasReleased);
}

void test_buttonAndLed_given_PRESSED_ON_state_with_press_button_again_should_change_to_TURNING_OFF(void)
{
  TaskState *ts = malloc(sizeof(TaskState));
  ts->state = PRESSED_ON;
  ts->recordedTime = 0;
  ts->interval = 250;
  ts->buttonHasReleased = 1;
  
  getButton_ExpectAndReturn(ts->whichButton, IS_PRESSED);
  turnLED_Expect(ts->whichLED, LED_OFF);
  
  buttonAndLed(ts);
  TEST_ASSERT_EQUAL(TURNING_OFF, ts->state);
}

/************************ PRESSED_OFF ****************************************/
void test_buttonAndLed_given_PRESSED_OFF_state_with_pressing_button_and_timer_not_expired_should_stay_in_PRESSED_OFF(void)
{
  TaskState *ts = malloc(sizeof(TaskState));
  ts->state = PRESSED_OFF;
  ts->recordedTime = 0;
  ts->interval = 250;
  ts->buttonHasReleased = 0;
  
  getButton_ExpectAndReturn(ts->whichButton, IS_PRESSED);
  getTime_ExpectAndReturn(0);  // for timer not expired yet
  
  buttonAndLed(ts);
  TEST_ASSERT_EQUAL(PRESSED_OFF, ts->state);
  TEST_ASSERT_EQUAL(0, ts->buttonHasReleased);
}

void test_buttonAndLed_given_PRESSED_OFF_state_with_pressing_button_and_timer_expired_should_change_to_PRESSED_ON(void)
{
  TaskState *ts = malloc(sizeof(TaskState));
  ts->state = PRESSED_OFF;
  ts->recordedTime = 0;
  ts->interval = 250;
  ts->buttonHasReleased = 0;
  
  getButton_ExpectAndReturn(ts->whichButton, IS_PRESSED);
  getTime_ExpectAndReturn(250);
  getTime_ExpectAndReturn(0); // for restat timer , recordedTime = 0
  turnLED_Expect(ts->whichLED, LED_ON);
  
  buttonAndLed(ts);
  TEST_ASSERT_EQUAL(PRESSED_ON, ts->state);
  TEST_ASSERT_EQUAL(0, ts->buttonHasReleased);
}

void test_buttonAndLed_given_PRESSED_OFF_state_with_released_button_should_stay_in_PRESSED_OFF(void)
{
  TaskState *ts = malloc(sizeof(TaskState));
  ts->state = PRESSED_OFF;
  ts->recordedTime = 0;
  ts->interval = 250;
  ts->buttonHasReleased = 0;
  
  getButton_ExpectAndReturn(ts->whichButton, IS_RELEASED);
  getTime_ExpectAndReturn(0);  // for timer not expired yet
  
  buttonAndLed(ts);
  TEST_ASSERT_EQUAL(PRESSED_OFF, ts->state);
  TEST_ASSERT_EQUAL(1, ts->buttonHasReleased);
}

void test_buttonAndLed_given_PRESSED_OFF_state_with_press_button_again_should_change_to_TURNING_OFF(void)
{
  TaskState *ts = malloc(sizeof(TaskState));
  ts->state = PRESSED_OFF;
  ts->recordedTime = 0;
  ts->interval = 250;
  ts->buttonHasReleased = 1;
  
  getButton_ExpectAndReturn(ts->whichButton, IS_PRESSED);
  turnLED_Expect(ts->whichLED, LED_OFF);
  
  buttonAndLed(ts);
  TEST_ASSERT_EQUAL(TURNING_OFF, ts->state);
}
/*********************** check default state **********************************/
void test_buttonAndLed_given_UNKNOWN_state_should_change_to_RELEASED(void)
{
  TaskState *ts = malloc(sizeof(TaskState));

  turnLED_Expect(ts->whichLED, LED_OFF);
  buttonAndLed(ts);

  TEST_ASSERT_EQUAL(RELEASED, ts->state);
}
