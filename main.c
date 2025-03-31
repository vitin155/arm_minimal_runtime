#include "stm32l476/registers.h"

#define LED_PIN (5)

void init_hw() {
    // First enable GPIOA peripheral
    RCC->AHB2ENR |= _BV(RCC_AHB2ENR_GPIOAEN);

    // Good information on GPIO setup is in Reference manual 8.4, especially table 39.
    // Many of those operations are not needed due to default values of those registers,
    // but for the sake of explicity

    // MODER has 2 bits per GPIO, hence LED_PIN * 2
    // First set both bits to 0, to make sure they are cleared
    GPIOA->MODER &= ~(0x3 << (LED_PIN * 2));

    // Then set them to general purpose output
    GPIOA->MODER |= (GPIOx_MODE_GPOUT << (LED_PIN * 2));

    // Set it to push-pull
    GPIOA->OTYPER &= ~((~GPIOx_OTYPE_PP) << LED_PIN);

    // Set speed to low, again clear bits first cause its 2 bits per pin
    GPIOA->OSPEEDR &= ~(0x3 << (LED_PIN * 2));
    GPIOA->OSPEEDR |= (GPIOx_OSPEED_LOW << (LED_PIN * 2));

    // Set pullups/pulldowns to no explicit choice
    GPIOA->OSPEEDR &= ~(0x3 << (LED_PIN * 2));
    GPIOA->OSPEEDR |= (GPIOx_OPUPD_NONE << (LED_PIN * 2));
}

int main(void) {
    init_hw();


    int val = 0;
    while (1) {
        if(val == 0) {
            // Output high/low repeatedly to blink the led
            // Due to clock speed, blinking is not visible, so it just pretty much lights it on
            // TODO: blink the led using a timer mayhaps?
            GPIOA->ODR ^= (1 << LED_PIN);
        }
        val += 1;
    }
}
