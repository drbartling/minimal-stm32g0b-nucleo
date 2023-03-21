#include "peripheral.h"

#include "memory.h"

volatile stm_rcc_t *STM_RCC = (void *)(0x40021000UL);

volatile stm_gpio_port_t *STM_gpio_a = (void *)(0x50000000UL);
volatile stm_gpio_port_t *STM_gpio_b = (void *)(0x50000400UL);
volatile stm_gpio_port_t *STM_gpio_c = (void *)(0x50000800UL);
volatile stm_gpio_port_t *STM_gpio_d = (void *)(0x50000C00UL);
volatile stm_gpio_port_t *STM_gpio_f = (void *)(0x50001400UL);
