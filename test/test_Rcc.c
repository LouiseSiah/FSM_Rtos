#include "unity.h"
#include "Register.h"
#include "Rcc.h"
#include "Gpio.h"
#include "Host.h"
#include "malloc.h"

void setUp(void){
  HostRcc   = malloc(sizeof(RCC_t));
  HostGpioA = malloc(0x400 * 11);
  HostGpioB = HostGpioA + 0x400;
  HostGpioC = HostGpioB + 0x400;
  HostGpioD = HostGpioC + 0x400;
  HostGpioE = HostGpioD + 0x400;
  HostGpioF = HostGpioE + 0x400;
  HostGpioG = HostGpioF + 0x400;
  HostGpioH = HostGpioG + 0x400;
  HostGpioI = HostGpioH + 0x400;
  HostGpioJ = HostGpioI + 0x400;
  HostGpioK = HostGpioJ + 0x400;
}

void tearDown(void){
  free(HostRcc);
  free(HostGpioG);
  HostRcc = NULL;
  HostGpioA = NULL;
  HostGpioB = NULL;
  HostGpioC = NULL;
  HostGpioD = NULL;
  HostGpioE = NULL;
  HostGpioF = NULL;
  HostGpioG = NULL;
  HostGpioH = NULL;
  HostGpioI = NULL;
  HostGpioJ = NULL;
  HostGpioK = NULL;
}

void test_Rcc_not_reset_and_clock_GpioG(void){
  RCC_reg->RCC_AHB1ENR  = 0;
  RCC_reg->RCC_AHB1RSTR = 0xFFFFFFFF;
  gpioUnresetEnableClock(PORTG);
  
  TEST_ASSERT_EQUAL(1, RCC_reg->RCC_AHB1ENR & 1);
  TEST_ASSERT_EQUAL(0, RCC_reg->RCC_AHB1RSTR & 1);
  
  TEST_ASSERT_EQUAL_HEX32(RCC_reg, HostRcc);
  TEST_ASSERT_EQUAL_HEX32(PORTG, HostGpioG);
}

void test_GPIOG(){
  TEST_ASSERT_EQUAL_HEX32(PORTG, HostGpioG);
  gpioUnresetEnableClock(PORTG);
  
  configureOutput(GPIO_SPEED_V_HIGH, PIN_4, PORTG);

  TEST_ASSERT_EQUAL_HEX32(1 << 8, PORTG->MODER);
  TEST_ASSERT_EQUAL_HEX32(0, PORTG->OTYPER);
  TEST_ASSERT_EQUAL_HEX32(3 << 8, PORTG->OSPEED);
  
  PORTG->BSRR = 0;
  writeOne(PIN_6, PORTG);
  TEST_ASSERT_EQUAL(1 << 6, PORTG->BSRR);
}
