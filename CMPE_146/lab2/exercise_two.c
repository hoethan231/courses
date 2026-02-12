#include <stdio.h>
#include "ti_msp_dl_config.h"

int exercise_two(void)
{
    SYSCFG_DL_init();

    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_initDigitalOutput(IOMUX_PINCM1);
    DL_GPIO_initDigitalInput(IOMUX_PINCM1);
    DL_GPIO_enableOutput(GPIOA, DL_GPIO_PIN_0);
    DL_GPIO_clearPins(GPIOA, DL_GPIO_PIN_0);

    DL_GPIO_enablePower(GPIOB);
    DL_GPIO_initDigitalOutput(IOMUX_PINCM50);
    DL_GPIO_initDigitalInput(IOMUX_PINCM50);
    DL_GPIO_enableOutput(GPIOB, DL_GPIO_PIN_22);
    DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_22);
    
    volatile uint32_t *PINCM_ptr = (volatile uint32_t *) 0x40428004;
    *PINCM_ptr |= (1<<26);

    uintptr_t GPIOB_base = 0x400A2000u;
    uintptr_t blue_offset = 0x1214u;
    volatile uint8_t *blue_pin_ptr = (volatile uint8_t *)(GPIOB_base + blue_offset + 2u);
    
    uintptr_t GPIOA_base = 0x400A0000u;
    uintptr_t red_offset = 0x1200u;
    volatile uint8_t *red_pin_ptr = (volatile uint8_t *)(GPIOA_base + red_offset);

    printf("Blue Alias Address: 0x%08X\n", GPIOB_base + blue_offset);
    printf("Red Alias Address: 0x%08X", GPIOA_base + red_offset);

    uint8_t state = 0;
    while (1) {
        state ^= 1u;
        *blue_pin_ptr = state;
        *red_pin_ptr = state;
        delay_cycles(32000000);
    }
    
    return 0;
}
