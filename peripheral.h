#ifndef PERIPHERAL_H
#define PERIPHERAL_H

#include "stdint.h"

typedef union {
    struct {
        uint32_t gpioa_en : 1;
        uint32_t gpiob_en : 1;
        uint32_t gpioc_en : 1;
        uint32_t gpiod_en : 1;
        uint32_t gpioe_en : 1;
        uint32_t gpiof_en : 1;
    };
    uint32_t bits;
} stm_iopenr_t;

typedef struct {
    volatile uint32_t     CR; /*Clock Control Register */
    volatile uint32_t     ICSCR;
    volatile uint32_t     CFGR;
    volatile uint32_t     PLLCFGR;
    volatile uint32_t     RESERVED0;
    volatile uint32_t     CRRCR;
    volatile uint32_t     CIER;
    volatile uint32_t     CIFR;
    volatile uint32_t     CICR;
    volatile uint32_t     IOPRSTR;
    volatile uint32_t     AHBRSTR;
    volatile uint32_t     APBRSTR1;
    volatile uint32_t     APBRSTR2;
    volatile stm_iopenr_t IOPENR;
    volatile uint32_t     AHBENR;
    volatile uint32_t     APBENR1;
    volatile uint32_t     APBENR2;
    volatile uint32_t     IOPSMENR;
    volatile uint32_t     AHBSMENR;
    volatile uint32_t     APBSMENR1;
    volatile uint32_t     APBSMENR2;
    volatile uint32_t     CCIPR;
    volatile uint32_t     RESERVED2;
    volatile uint32_t     BDCR;
    volatile uint32_t     CSR;
} stm_rcc_t;

typedef enum {
    stm_gpio_mode_input,
    stm_gpio_mode_output,
    stm_gpio_mode_alternate_function,
    stm_gpio_mode_analog,
} stm_gpio_mode_t;

typedef union {
    struct {
        stm_gpio_mode_t pin_0 : 2;
        stm_gpio_mode_t pin_1 : 2;
        stm_gpio_mode_t pin_2 : 2;
        stm_gpio_mode_t pin_3 : 2;
        stm_gpio_mode_t pin_4 : 2;
        stm_gpio_mode_t pin_5 : 2;
        stm_gpio_mode_t pin_6 : 2;
        stm_gpio_mode_t pin_7 : 2;
        stm_gpio_mode_t pin_8 : 2;
        stm_gpio_mode_t pin_9 : 2;
        stm_gpio_mode_t pin_10 : 2;
        stm_gpio_mode_t pin_11 : 2;
        stm_gpio_mode_t pin_12 : 2;
        stm_gpio_mode_t pin_13 : 2;
        stm_gpio_mode_t pin_14 : 2;
        stm_gpio_mode_t pin_15 : 2;
    };
    uint32_t bits;
} stm_gpio_mode_reg_t;

typedef struct {
    volatile stm_gpio_mode_reg_t moder;
    volatile uint32_t            otyper;
    volatile uint32_t            ospeedr;
    volatile uint32_t            pupdr;
    volatile uint32_t            idr;
    volatile uint32_t            odr;
    volatile uint32_t            bsrr;
    volatile uint32_t            lckr;
    volatile uint32_t            afr;
    volatile uint32_t            brr;
} stm_gpio_port_t;

extern volatile stm_rcc_t *STM_RCC;

extern volatile stm_gpio_port_t *STM_gpio_a;
extern volatile stm_gpio_port_t *STM_gpio_b;
extern volatile stm_gpio_port_t *STM_gpio_c;
extern volatile stm_gpio_port_t *STM_gpio_d;
extern volatile stm_gpio_port_t *STM_gpio_f;

#endif
