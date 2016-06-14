#include "stm32f429xx.h"
#include "Gpio.h"

int main(void){
	configureOutput(GPIO_SPEED_V_HIGH, PIN_14, PORTG);
	configureOutput(GPIO_SPEED_V_HIGH, PIN_13, PORTG);

    while(1){
    	writeOne(PIN_13, PORTG);
    	writeZero(PIN_14, PORTG);
      delay(1000000);

    	writeZero(PIN_13, PORTG);
    	writeOne(PIN_14, PORTG);
      delay(1000000);
    }
}

void delay(int delay){
	while(delay != 0)
		delay--;
}
