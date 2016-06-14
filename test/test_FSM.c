#include "unity.h"
#include "FSM.h"
#include "mock_GetSignal.h"
#include <malloc.h>
void setUp(void)
{
}

void tearDown(void)
{
}

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
