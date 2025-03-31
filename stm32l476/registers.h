#ifndef _STM32L476_REGISTERS_H_
#define _STM32L476_REGISTERS_H_

#include <stdint.h>

// bit value macro
#define _BV(N) (1 << (N))

struct _RCC_t {
    uint8_t _dont_care[0x4C];
    uint32_t AHB2ENR; // Reference manual 6.4.17 - offset 0x4C, pins defined below
#define RCC_AHB2ENR_GPIOAEN 0
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

// Below addresses from Datasheet 5. - Memory Map, table 19.
#define RCC ((volatile struct _RCC_t*) 0x40021000)
#define GPIOA ((volatile struct _GPIOx_t*) 0x48000000)

#endif
