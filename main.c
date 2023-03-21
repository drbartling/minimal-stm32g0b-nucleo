#include "peripheral.h"
#include "memory.h"

#include "stdint.h"

static int  main(void);
static void delay(uint32_t count);
static void init_gpio(void);
static void reset_handler(void);
static void initialize_global_data(uint32_t *flash_begin, uint32_t *data_begin,
                                   uint32_t *data_end);

int
main(void)
{
    init_gpio();

    while (1) {

        STM_gpio_a->odr.pin_5 = 1;
        delay(200000);
        STM_gpio_a->odr.pin_5 = 0;
        delay(200000);
    }
    return 0;
}

void
init_gpio(void)
{
    STM_RCC->IOPENR.gpioa_en = 1;
    STM_gpio_a->moder.pin_5  = stm_gpio_mode_output;
}

static void
delay(uint32_t count)
{
    while (count--) {
    }
}

static void
reset_handler(void)
{
    extern uint32_t LINKER_load_data;
    extern uint32_t LINKER_start_data;
    extern uint32_t LINKER_end_data;
    initialize_global_data(&LINKER_load_data, &LINKER_start_data,
                           &LINKER_end_data);
    main();

    while (1) {
    }
}

static void
initialize_global_data(uint32_t *flash_begin, uint32_t *data_begin,
                       uint32_t *data_end)
{
    uint32_t *p = data_begin;
    while (p < data_end) {
        *p++ = *flash_begin++;
    }
}

uint32_t *vector_table[] __attribute__((section(".isr_vector"))) = {
    // End of ram is initial stack pointer
    (uint32_t *)SRAM_END,
    (uint32_t *)reset_handler,
};
