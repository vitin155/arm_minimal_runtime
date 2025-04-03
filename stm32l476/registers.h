#ifndef _STM32L476_REGISTERS_H_
#define _STM32L476_REGISTERS_H_

#include <stdint.h>

// bit value macro
#define _BV(N) (1 << (N))

// ARM7m reference manual B3.4.3
struct _NVIC_t_ {
    uint32_t ISER[16];
    // dont care about other stuff, maybe priority register could be useful in the future
};

// ARM7m reference manual B3.2
#define NVIC ((volatile struct _NVIC_t_*) 0xE000E100)

// Copied directly from https://github.com/ARM-software/CMSIS_4/blob/f2cad4345783c948ed4a7f5cdb02cdc0856366f1/CMSIS/Include/core_cm4.h#L1626C17-L1629C2
// The arithmetic is easy but no reason to reinvent the wheel
void NVIC_EnableIRQ(int32_t IRQn) {
    NVIC->ISER[(((uint32_t)(int32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)(int32_t)IRQn) & 0x1FUL));
};

struct _RCC_t {
    uint8_t _dont_care[0x08];

    uint32_t CFGR; // clock configuration register - Reference manual 6.4.3 - offset 0x08, pins defined below
    #define RCC_CFGR_HPRE0      4 // AHB prescaler bit 0
    #define RCC_CFGR_HPRE1      5 // AHB prescaler bit 0
    #define RCC_CFGR_HPRE2      6 // AHB prescaler bit 0
    #define RCC_CFGR_HPRE3      7 // AHB prescaler bit 0

    uint8_t _dont_care_2[0x40];

    uint32_t AHB2ENR; // Reference manual 6.4.17 - offset 0x4C, pins defined below
    #define RCC_AHB2ENR_GPIOAEN 0

    uint8_t _dont_care_3[0x08];

    uint32_t APB1ENR1; // Reference manual 6.4.19 - offset 0x58, pins defined below
    #define RCC_APB1ENR1_TIM7EN 5
};

struct _GPIOx_t {
    uint32_t MODER; // mode of operation per pin - Reference manual 8.5.1 - offset 0x0, values for bit pairs defined below
    #define GPIOx_MODE_INPUT    0 // Input
    #define GPIOx_MODE_GPOUT    1 // General Purpose Output
    #define GPIOx_MODE_AF       2 // Alternate Function (GPIO off)
    #define GPIOx_MODE_ANALOG   3 // Analog (reset state, default for most pins)

    uint32_t OTYPER; // output type - Reference manual 8.5.2 - offset 0x4, values for bits defined below
    #define GPIOx_OTYPE_PP      0 // Push-pull (default for most)
    #define GPIOx_OTYPE_OD      1 // Open-drain

    uint32_t OSPEEDR; // output speed - Reference manual 8.5.3 - offset 0x8, values for bit pairs defined below
    #define GPIOx_OSPEED_LOW    0 // default for most pins
    #define GPIOx_OSPEED_MEDIUM 1
    #define GPIOx_OSPEED_HIGH   2
    #define GPIOx_OSPEED_VHIGH  3

    uint32_t PUPDR; // explicit pull - Reference manual 8.5.4 - offset 0xC, values for bit pairs defined below
    #define GPIOx_OPUPD_NONE    0 // no explicit pull up or pull down (default for most)
    #define GPIOx_OPUPD_PU      1 // explicit Pull up
    #define GPIOx_OPUPD_PD      2 // explicit Pull down

    uint32_t IDR; // input data register (readonly) - Reference manual 8.5.5 - offset 0x10
    uint32_t ODR; // output data register (read-write) - Reference manual 8.5.6 - offset 0x14
    // theres also BSRR and some other stuff i think but its not really needed for now?
};

// Structure only for TIM6 and TIM7! Reference manual 33.4
// some of these registers are displayed as 16-bit in their manual entries, but in
// 33.4.9 it is shown that they are indeed 32 bits, and their top half of bits just is not used
struct _TIMx_6_7_t_{
    uint32_t CR1; // control register 1 - Reference manual 33.4.1 - offset 0x0, bits defined below
    #define TIMx_6_7_CR1_CEN    0 // Counter enable, 1 for on 0 for off (default off)
    #define TIMx_6_7_CR1_UDIS   1 // Update disable, 1 for on (disabled update event) , 0 for off (event enabled)
    #define TIMx_6_7_CR1_URS    2 // Update requst source - decides what generates an udpate event (Ref manual)
    #define TIMx_6_7_CR1_OPM    3 // One pulse mode enable

    uint8_t _dont_care[0x08];

    uint32_t DIER; // DMA/interrupt enable register - Reference manual 33.4.3 - offset 0x0C, bits defined below
    #define TIMx_6_7_DIER_UIE   0 // Interrupt enable
    #define TIMx_6_7_DIER_UDE   8 // DMA request enable

    uint32_t SR; // Status register - Reference manual 33.4.4 - offset 0x10, bits defined below
    #define TIMx_6_7_SR_UIF     0 // Update interrupt flag - set to 1 by hardware on update event, has to be cleared in software

    uint32_t EGR; // Event generation register - Reference manual 33.4.5 - offset 0x14, bits defined below
    #define TIMx_6_7_EGR_UG     0 // Update generator - resets the timer and updates ARR and CNT values (?)

    uint8_t _dont_care_2[0x10];

    uint32_t PSC; // Prescaler register (16 bit) - Reference manual 33.4.7 - offset 0x28
    // From the manual, counter clock frequency is equal to: fCK_PSC / (PSC[15:0] + 1)
    // For example, with sysclk equal 4MHz, setting PSC to 39999 will result in frequency of
    // 4MHz / 40000 = 100 Hz

    uint32_t ARR; // Auto reload register (16 bit) - Reference manual 33.4.8 - offset 0x2C
    // The value in the register specifies the top value for the counter to triggeri nterrupt on
};

// Below addresses from Datasheet 5. - Memory Map, table 19.
#define RCC ((volatile struct _RCC_t*) 0x40021000)
#define GPIOA ((volatile struct _GPIOx_t*) 0x48000000)
#define TIM7 ((volatile struct _TIMx_6_7_t_*) 0x40001400)

#endif
