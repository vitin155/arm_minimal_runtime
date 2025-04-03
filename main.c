#include "stm32l476/registers.h"

#define TIM7_IRQn (55)

#define LED_PIN (5)

void init_hw() {
    // First enable GPIOA peripheral
    RCC->AHB2ENR |= _BV(RCC_AHB2ENR_GPIOAEN);

    // Also TIM7 peripheral
    RCC->APB1ENR1 |= _BV(RCC_APB1ENR1_TIM7EN);

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

    // Set top value to 40000, so with 4MHz system clock it would results in 100Hz
    TIM7->ARR = 40000;

    // Set prescaler to 50 so it fires twice every second
    // fCK_PSC / (PSC[15:0] + 1)
    TIM7->PSC = 49;

    // Enable settings
    //TIM7->EGR |= _BV(TIMx_6_7_EGR_UG); // seems to not be needed? works without it

    // Enable interrupt in NVIC too
    NVIC_EnableIRQ(TIM7_IRQn);

    // Enable interrupt in peripheral
    TIM7->DIER |= _BV(TIMx_6_7_DIER_UIE);

    // Finally enable clock
    TIM7->CR1 |= _BV(TIMx_6_7_CR1_CEN);
}

// Interrupt handler for TIM6 overflow event
// https://gcc.gnu.org/onlinedocs/gcc/ARM-Function-Attributes.html for attribute
void TIM7_handler()  {
    // flip output of the LED
    GPIOA->ODR ^= (1 << LED_PIN);

    // Clear interrupt flag
    TIM7->SR &= ~(_BV(TIMx_6_7_SR_UIF));
}

int main(void) {
    init_hw();

    while (1) {
        // Do nothing, should perhaps even sleep
    }
}
